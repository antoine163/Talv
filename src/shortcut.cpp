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
*	Copyright © 2012 - Antoine Maleyrie.
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
		shortcut._modifiers&KeyModifier::WIN) &&
		shortcut._charKey == '\0')
	{
		return wxEmptyString;
	}
	
	//Conversion du modificateur
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
				
				statut = KeyModifier::WIN;
			}break;
			
			case KeyModifier::WIN:
			{
				if(shortcut._modifiers&KeyModifier::WIN)
					ret << "win+";
				
				statut = KeyModifier::NONE;
			}break;
			
			default:
			return wxEmptyString;
			break;
		}
	}
	
	//Ajout du charKey
	ret << shortcut._charKey;
	
	//Minimalise
	ret.MakeLower();
	
	return ret;
}

ShortcutKey ShortcutKey::stringToShortcutKey(wxString const& shortcut)
{
	KeyModifier modifiers = KeyModifier::NONE;
	char charKey = '\0';
	
	//Avent ou rapper le premier '+'
	wxString before;
	wxString after;
	
	//Minimalise
	wxString tmp = shortcut;
	tmp.MakeLower();
	
	
	//Obtenir avent ou après le premier '+'
	before = tmp.BeforeFirst('+', &after);
	//Conversion du modificateur
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
		else if(before == "win")
		modifiers = (KeyModifier)(modifiers|KeyModifier::WIN);
		
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
: wxThread(wxTHREAD_JOINABLE), _owner(owner), _bind(bind)
{
    #if defined(__UNIX__)
    _display = XOpenDisplay(0);
    _root = XDefaultRootWindow(_display);
    #endif
}

ShortcutThread::~ShortcutThread()
{
    #if defined(__UNIX__)
    XCloseDisplay(_display);
    #endif
}

void ShortcutThread::halt()
{
	if(IsAlive())
	{
		#if defined(__UNIX__)
		//Supprimer des raccourcis
		for(auto &it: _bind)	
		{
			//Convertie charKey vers KeyCode
			char charKey[2] = {it.first.getCharKey(), '\0'};
			KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
			//ungrab le raccourci
			XUngrabKey(_display, key, (unsigned int)it.first.getModifiers(), _root);
		}
		XEvent exit;
		exit.type = 0;
		XPutBackEvent(_display, &exit);
		#elif defined(__WXMSW__)
		PostThreadMessage(GetId(), WM_QUIT, 0, 0);
		#endif
		while(IsAlive());
	}
}

wxThread::ExitCode ShortcutThread::Entry()
{
	for(auto &it: _bind)	
	{		
		char charKey[2] = {it.first.getCharKey(), '\0'};
		
		#if defined(__UNIX__)
		//Convertie charKey vers KeyCode
		KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
		//grab le raccourci
		XGrabKey(_display, key, (unsigned int)it.first.getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
		#elif defined(__WXMSW__)
		//Capitalise le charKey
		wxString charKeyCapital(charKey);
		charKeyCapital.MakeCapitalized();
		//Enregistre le raccourci
		RegisterHotKey(nullptr, getId(it.first), (UINT)it.first.getModifiers(), *charKeyCapital.fn_str());
		#endif
	}
	
	#if defined(__UNIX__)
	while(1)
	{
		//Si un événement est présent on le récupère
		XNextEvent(_display, &_event);
		if(_event.type == KeyPress)
		{ 
			//Convertie le KeyCode en char
			const char charKey = *(XKeysymToString(XkbKeycodeToKeysym(_display, _event.xkey.keycode, 0, 0)));
			//mise en forme du raccourci
			ShortcutKey shortcutKey((KeyModifier)_event.xkey.state, charKey);
			//Recherche de l'id
			int id = getId(shortcutKey);
			//Envoi de l'événement
			ShortcutEvent *event = new ShortcutEvent(id, EVT_SHORTCUT, shortcutKey);
			wxQueueEvent(_owner, event);
		}
		else if(_event.type == 0)
			return (wxThread::ExitCode)0;
	}
	#elif defined(__WXMSW__)
	//Si un événement est présent
	while(GetMessage(&_msgEvent, nullptr, 0, 0) != 0)
	{
		//On le récupère
		if (_msgEvent.message == WM_HOTKEY)
		{
			//Recherche du modifiers et du charKey
			for(auto &it: _bind)
			{
				//Compare des id
				if(it.second == (int)_msgEvent.wParam)
				{
					//Envoi de l'événement
					ShortcutEvent *event = new ShortcutEvent(it.second, EVT_SHORTCUT, it.first);
					wxQueueEvent(_owner, event);
					break;
				}
			}
		}
	}
	#endif
	
		
	#if defined(__WXMSW__)
	//Supprimer des raccourcis
	for(auto &it: _bind)	
		UnregisterHotKey(nullptr, getId(it.first));
	#endif

	return (wxThread::ExitCode)0;
}

int ShortcutThread::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
}

//! ****************************************************************************
//! Class Shortcut
//! ****************************************************************************

Shortcut::Shortcut(wxEvtHandler *owner)
: _thread(nullptr), _owner(owner), _enable(false)
{
}

Shortcut::~Shortcut()
{
	removeAll();
	if(_thread != nullptr)
	{
		_thread->halt();
		delete _thread;
	}
}

int Shortcut::creat(KeyModifier modifiers, char charKey)
{
    return creat(ShortcutKey(modifiers, charKey));
}

int Shortcut::creat(ShortcutKey const& shortcutKey)
{
	//création d'un nouveau id
    int id = wxNewId();
    
    //Création d'un lien et ajout de l'id
    _bind[shortcutKey] = id;
    
    return id;
}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
	remove(ShortcutKey(modifiers, charKey));
}

void Shortcut::remove(ShortcutKey const& shortcutKey)
{
    //Supprime le lien
    _bind.erase(shortcutKey); 
}

void Shortcut::removeAll()
{
	//Supprime les liens
	_bind.clear();
}

int Shortcut::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
}

void Shortcut::enable(bool val)
{		
	//si on doit désactiver
	if(_enable == true && val == false)
	{
		_thread->halt();
		delete _thread;
		_thread = nullptr;
	}
	//si on doit activer
	else if(_enable == false && val == true)
	{	
		_thread = new ShortcutThread(_owner, _bind);
		_thread->Create();
		_thread->Run();
	}
	
	_enable = val;
}
