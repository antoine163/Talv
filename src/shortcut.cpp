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

ShortcutThread::ShortcutThread(wxApp *owner, std::map<ShortcutKey, int> & bind)
: _owner(owner), _bind(bind)
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

	//_owner->Unbind(wxEVT_IDLE, &Shortcut::OnIdle, this);
	
	//removeAll();
}

void ShortcutThread::halt()
{
	if(IsRunning())
	{
		PostThreadMessage(GetId(), WM_QUIT, 0, 0);
		while(IsRunning());
	}
}

//void ShortcutThread::registerShortcut(ShortcutKey const& shortcutKey)
//{
	//char charKey[2] = {shortcutKey.getCharKey(), '\0'};
	
	//#if defined(__UNIX__)
	////Convertie charKey vers KeyCode
	//KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
	////grab le raccourci
	//XGrabKey(_display, key, (unsigned int)shortcutKey.getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
	//#elif defined(__WXMSW__)
	////Capitalise le charKey
	////wxString charKeyCapital(charKey);
	////charKeyCapital.MakeCapitalized();
	//////Enregistre le raccourci
	////RegisterHotKey(nullptr, getId(shortcutKey), (UINT)shortcutKey.getModifiers(), *charKeyCapital.fn_str());
	//#endif
//}

//void ShortcutThread::unRegisterShortcut(ShortcutKey const& shortcutKey)
//{	
	//#if defined(__UNIX__)
	////Convertie charKey vers KeyCode
	//char charKey[2] = {shortcutKey.getCharKey(), '\0'};
	//KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
	////ungrab le raccourci
	//XUngrabKey(_display, key, (unsigned int)shortcutKey.getModifiers(), _root);
	//#elif defined(__WXMSW__)
	////Supprimer le raccourci
	////UnregisterHotKey(nullptr, getId(shortcutKey));
	
	//#endif
//}

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
	
	bool run = true;
	while(run)
	{std::cout << "run" << std::endl;
		#if defined(__UNIX__)	
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
		#elif defined(__WXMSW__)
		//Si un événement est présent
		if(GetMessage(&_msgEvent, nullptr, 0, 0) != 0)
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
			else if (_msgEvent.message == WM_QUIT)
			{
				std::cout << "WM_QUIT" << std::endl;
				
				//Supprimer des raccourcis
				for(auto &it: _bind)	
					UnregisterHotKey(nullptr, getId(it.first));
	
				run = false;
			}
		}
		#endif
	}
	return (wxThread::ExitCode)0;
}

int ShortcutThread::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
}

//! ****************************************************************************
//! Class Shortcut
//! ****************************************************************************

Shortcut::Shortcut(wxApp *owner)
: _enable(false)
{
	_thread = new ShortcutThread(owner, _bind);
	_thread->Create();
}

Shortcut::~Shortcut()
{
	removeAll();
	_thread->halt();
	delete _thread;
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
    
    //if(_enable)
		//registerShortcut(shortcutKey);
    
    return id;
}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
	remove(ShortcutKey(modifiers, charKey));
}

void Shortcut::remove(ShortcutKey const& shortcutKey)
{
	//if(_enable)
		//unRegisterShortcut(shortcutKey);
    
    //supprime le lien
    _bind.erase(shortcutKey); 
}

void Shortcut::removeAll()
{
	if(_enable)
	{
		//supprimer les raccourci coter système
		//for(auto &it: _bind)
			//unRegisterShortcut(it.first);
	}
	
	//supprime les liens
	_bind.clear();
}

int Shortcut::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
}

void Shortcut::enable(bool vale)
{		
	//si on doit désactiver
	if(_enable == true && vale == false)
	{
		_thread->halt();
	}
	//si on doit activer
	else if(_enable == false && vale == true)
	{		
		_thread->Run();
	}
	
	_enable = vale;
}
