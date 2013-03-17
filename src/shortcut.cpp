//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 1.0.0
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2012-1013 - Antoine Maleyrie.
*/

#include "shortcut.hpp"

#if defined(__UNIX__)
#include <X11/XKBlib.h>
#endif

#include <iostream>

//! ****************************************************************************
//! Class ShortcutKey
//! ****************************************************************************

ShortcutKey::ShortcutKey(KeyModifier modifiers, char charKey)
: _modifiers(modifiers), _charKey(charKey)
{
}

bool ShortcutKey::operator<(ShortcutKey const& ins)const
{
	if(_charKey < ins._charKey)
		return true;
	else if(_charKey == ins._charKey)
	{
		if(_modifiers < ins._modifiers)
			return true;
	}
	
	return false;
}

bool ShortcutKey::operator==(ShortcutKey const& ins)const
{
	if((_modifiers == ins._modifiers) && (_charKey == ins._charKey))
		return true;
		
	return false;
}

bool ShortcutKey::operator!=(ShortcutKey const& ins)const
{
	if((_modifiers != ins._modifiers) || (_charKey != ins._charKey))
		return true;
		
	return false;
}

char ShortcutKey::getCharKey()const
{
	return _charKey;
}

KeyModifier ShortcutKey::getModifiers()const
{
	return _modifiers;
}

wxString ShortcutKey::shortcutKeyToString(ShortcutKey const& shortcut)
{
	wxString ret;
	
	// ShortcutKey valide ?
	if(!(shortcut._modifiers&KeyModifier::ALT ||
		shortcut._modifiers&KeyModifier::CONTROL ||
		#if defined(__UNIX__)
		shortcut._modifiers&KeyModifier::ALTGR ||
		#endif
		shortcut._modifiers&KeyModifier::SHIFT ||
		shortcut._modifiers&KeyModifier::SUPER) &&
		shortcut._charKey == '\0')
	{
		return wxEmptyString;
	}
	
	//Conversion du modificateur.
	KeyModifier statut = KeyModifier::CONTROL;
	for(unsigned int i = 0; i < NB_KEY_MODIFIER; i++)
	{
		switch(statut)
		{
			case KeyModifier::CONTROL:
			{
				if(shortcut._modifiers&KeyModifier::CONTROL)
					ret << "ctrl+";
				
				statut = KeyModifier::ALT;
			}break;
			
			case KeyModifier::ALT:
			{
				if(shortcut._modifiers&KeyModifier::ALT)
					ret << "alt+";
				
				#if defined(__UNIX__)
				statut = KeyModifier::ALTGR;
				#elif defined(__WXMSW__)
				statut = KeyModifier::SHIFT;
				#endif
			}break;
			
			#if defined(__UNIX__)
			case KeyModifier::ALTGR:
			{
				if(shortcut._modifiers&KeyModifier::ALTGR)
					ret << "altgr+";
				
				statut = KeyModifier::SHIFT;
			}break;
			#endif
			
			case KeyModifier::SHIFT:
			{
				if(shortcut._modifiers&KeyModifier::SHIFT)
					ret << "shift+";
				
				statut = KeyModifier::SUPER;
			}break;
			
			case KeyModifier::SUPER:
			{
				if(shortcut._modifiers&KeyModifier::SUPER)
					ret << "super+";
				
				statut = KeyModifier::NONE;
			}break;
			
			default:
			return wxEmptyString;
			break;
		}
	}
	
	//Ajout du charKey.
	ret << shortcut._charKey;
	
	//Minimalise
	ret.MakeLower();
	
	return ret;
}

ShortcutKey ShortcutKey::stringToShortcutKey(wxString const& shortcut)
{
	KeyModifier modifiers = KeyModifier::NONE;
	char charKey = '\0';
	
	//Avent ou après le premier '+'.
	wxString before;
	wxString after;
	
	//Minimalise
	wxString tmp = shortcut;
	tmp.MakeLower();
	
	
	//Obtenir avent ou après le premier '+'.
	before = tmp.BeforeFirst('+', &after);
	//Conversion du modificateur.
	while(!before.IsEmpty())
	{
		charKey = *before.fn_str();
		
		if(before == "ctrl")
			modifiers = (KeyModifier)(modifiers|KeyModifier::CONTROL);
		else if(before == "alt")
			modifiers = (KeyModifier)(modifiers|KeyModifier::ALT);
		#if defined(__UNIX__)
		else if(before == "altgr")
			modifiers = (KeyModifier)(modifiers|KeyModifier::ALTGR);
		#endif
		else if(before == "shift")
			modifiers = (KeyModifier)(modifiers|KeyModifier::SHIFT);
		else if(before == "super")
		modifiers = (KeyModifier)(modifiers|KeyModifier::SUPER);
		
		//Obtenir le nouveau avent ou après le premier '+'
		tmp = after;
		before = tmp.BeforeFirst('+', &after);
	}
	
	return ShortcutKey(modifiers, charKey);
}

//! ****************************************************************************
//! Class ShortcutEvent
//! ****************************************************************************
		
ShortcutEvent::ShortcutEvent(int id, wxEventType eventType, KeyModifier modifiers, char charKey)
    : wxEvent(id, eventType), _shortcutKey(modifiers, charKey)
{
}

ShortcutEvent::ShortcutEvent(int id, wxEventType eventType, ShortcutKey const& shortcutKey)
	: wxEvent(id, eventType), _shortcutKey(shortcutKey)
{
}

wxEvent* ShortcutEvent::Clone()const
{
    return new ShortcutEvent(*this);
}

char ShortcutEvent::getCharKey()const
{
    return _shortcutKey.getCharKey();
}

KeyModifier ShortcutEvent::getModifiers()const
{
    return _shortcutKey.getModifiers();
}

ShortcutKey const& ShortcutEvent::getShortcutKey()const
{
	return _shortcutKey;
}

wxDEFINE_EVENT(EVT_SHORTCUT, ShortcutEvent);

//! ****************************************************************************
//! Class ShortcutThread
//! ****************************************************************************

ShortcutThread::ShortcutThread(wxEvtHandler *owner, std::map<ShortcutKey, int> & bind)
: wxThread(wxTHREAD_JOINABLE), _owner(owner), _bind(bind), _mutexCommunicationThread(false), _shortcutKeyCommunicationThread(nullptr), _communicationThread(NONE)
{
    #if defined(__UNIX__)
    static bool isXInitThreads = false;
    if(!isXInitThreads)
    {
		XInitThreads();
		isXInitThreads = true;
	}
    
    _display = XOpenDisplay(0);
    _root = XDefaultRootWindow(_display);
	_interCommunication = XCreateSimpleWindow(_display, _root, 0, 0, 1, 1, 0, 0, 0);
	XSelectInput(_display, _interCommunication, StructureNotifyMask);
    #endif
}

ShortcutThread::~ShortcutThread()
{
	if(IsAlive())
		halt();
		
    #if defined(__UNIX__)
    XCloseDisplay(_display);
    #endif
}

void ShortcutThread::registerShortcut(ShortcutKey const& shortcutKey)
{
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=REGISTER;
	_shortcutKeyCommunicationThread=&shortcutKey;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	#endif
}

void ShortcutThread::unregisterShortcut(ShortcutKey const& shortcutKey)
{
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=UNREGISTER;
	_shortcutKeyCommunicationThread=&shortcutKey;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	#endif
}

void ShortcutThread::unregisterAllShortcut()
{
	for(auto &it: _bind)
		unregisterShortcut(it.first);
}

void ShortcutThread::halt()
{
	//Désactive touts les raccourcis.
	unregisterAllShortcut();
	
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=QUIT;
	_shortcutKeyCommunicationThread=nullptr;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	#endif
	
	//Attend la fin du thread.
	while(IsAlive());
}

wxThread::ExitCode ShortcutThread::Entry()
{
	bool run = true;
	#if defined(__UNIX__)
	while(run)
	{
		//Si un événement est présent on le récupère.
		XNextEvent(_display, &_event);
		if(_event.type == KeyPress)
		{ 
			//Convertie le KeyCode en char.
			const char charKey = *(XKeysymToString(XkbKeycodeToKeysym(_display, _event.xkey.keycode, 0, 0)));
			//Mise en forme du raccourci.
			ShortcutKey shortcutKey((KeyModifier)_event.xkey.state, charKey);
			//Recherche de l'id.
			int id = _bind[shortcutKey];
			//Envoi de l'événement.
			ShortcutEvent *event = new ShortcutEvent(id, EVT_SHORTCUT, shortcutKey);
			wxQueueEvent(_owner, event);
		}
		else if(_event.type == ClientMessage)
		{
			char charKey[2] = {'\0', '\0'};
			KeyCode key;
			switch(_communicationThread)
			{
				//Enregistre le raccourci.
				case CommunicationThread::REGISTER:
					charKey[0]=_shortcutKeyCommunicationThread->getCharKey();
					key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
					XGrabKey(_display, key, (unsigned int)_shortcutKeyCommunicationThread->getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
				break;
				
				//Désenregistrer le raccourci.
				case CommunicationThread::UNREGISTER:
					charKey[0]=_shortcutKeyCommunicationThread->getCharKey();
					key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
					XUngrabKey(_display, key, (unsigned int)_shortcutKeyCommunicationThread->getModifiers(), _root);
				break;
				
				//Quit le thread.
				case CommunicationThread::QUIT:
					run = false;
				break;
				
				case CommunicationThread::NONE:
				default:
				break;
			}

			//Fin d'utilisation des données de communication.
			_shortcutKeyCommunicationThread = nullptr;
			_mutexCommunicationThread = false;
		}
	}
	#elif defined(__WXMSW__)
	//Si un événement est présent.
	while(GetMessage(&_msgEvent, nullptr, 0, 0) != 0)
	{
		//On le récupère.
		if(_msgEvent.message == WM_HOTKEY)
		{
			//Recherche du modifiers et du charKey.
			for(auto &it: _bind)
			{
				//Compare des id.
				if(it.second == (int)_msgEvent.wParam)
				{
					//Envoi de l'événement.
					ShortcutEvent *event = new ShortcutEvent(it.second, EVT_SHORTCUT, it.first);
					wxQueueEvent(_owner, event);
					break;
				}
			}
		}
	}

	//Supprimer des raccourcis.
	for(auto &it: _bind)	
		UnregisterHotKey(nullptr, _bind[it.first]));
	#endif

	return (wxThread::ExitCode)0;
}

//! ****************************************************************************
//! Class Shortcut
//! ****************************************************************************

Shortcut::Shortcut(wxEvtHandler *owner)
: _thread(nullptr), _owner(owner), _enable(true)
{
	_thread = new ShortcutThread(_owner, _bind);
	_thread->Create();
	_thread->Run();
}

Shortcut::~Shortcut()
{
	if(_thread != nullptr)
		delete _thread;
}

int Shortcut::creat(KeyModifier modifiers, char charKey)
{
    return creat(ShortcutKey(modifiers, charKey));
}

int Shortcut::creat(ShortcutKey const& shortcutKey)
{
	//Création d'un nouveau id.
    int id = wxNewId();
    
    //Création d'un lien et ajout de l'id.
    _bind[shortcutKey] = id;
    
    //Si les raccourcis sont activés, on active le raccourci au prés du thread.
    if(_enable)
		_thread->registerShortcut(shortcutKey);
		
    return id;
}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
	remove(ShortcutKey(modifiers, charKey));
}

void Shortcut::remove(ShortcutKey const& shortcutKey)
{
	//Si les raccourcis sont activés, on désactive le raccourci au prés du thread.
    if(_enable)
		_thread->unregisterShortcut(shortcutKey);
		
    //Supprime le lien
    _bind.erase(shortcutKey); 
}

void Shortcut::removeAll()
{
	//Si les raccourcis sont activés, on désactive tout les raccourcis au prés du thread.
    if(_enable)
		_thread->unregisterAllShortcut();
		
	//Supprime les liens.
	_bind.clear();
}

int Shortcut::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
}

void Shortcut::enable(bool val)
{		
	//Si on doit désactiver.
	if(_enable == true && val == false)
	{
		//Désactive tout les raccourcis au prés du thread.
		delete _thread;
		_thread = nullptr;
	}
	//Si on doit activer.
	else if(_enable == false && val == true)
	{	
		//On relance le thread.
		_thread = new ShortcutThread(_owner, _bind);
		_thread->Create();
		_thread->Run();
		
		//Active les raccourcis au prés du thread.
		for(auto &it: _bind)			
			_thread->registerShortcut(it.first);
	}
	
	_enable = val;
}
