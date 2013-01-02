//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 0.3
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
//! Class Shortcut
//! ****************************************************************************

Shortcut::Shortcut(wxApp *owner) : _owner(owner), _enable(true)
{
    #if defined(__UNIX__)
    _display = XOpenDisplay(0);
    _root = XDefaultRootWindow(_display);
    #endif
    
    _owner->Bind(wxEVT_IDLE, &Shortcut::OnIdle, this);
}

Shortcut::~Shortcut()
{
    #if defined(__UNIX__)
    XCloseDisplay(_display);
    #endif

	_owner->Unbind(wxEVT_IDLE, &Shortcut::OnIdle, this);
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
    
    if(_enable)
		registerShortcut(shortcutKey);
    
    return id;
}

void Shortcut::OnIdle(wxIdleEvent& event)
{
	#if defined(__UNIX__)	
	//Si un événement est présent
	if(XPending(_display) > 0)
	{
		//On le récupère
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
	}
	//Sinon on attend un peur pour éviter de prends trop de temps cpu.
	else
		usleep(10);
	#elif defined(__WXMSW__)
	//Si un événement est présent
	if(GetMessage(&_msgEvent, NULL, 0, 0) != 0)
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
	
	//Appeler en continue.
	event.RequestMore(); 
}

void Shortcut::registerShortcut(ShortcutKey const& shortcutKey)
{
	char charKey[2] = {shortcutKey.getCharKey(), '\0'};
	
	#if defined(__UNIX__)
	//Convertie charKey vers KeyCode
	KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
	//grab le raccourci
	XGrabKey(_display, key, (unsigned int)shortcutKey.getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
	#elif defined(__WXMSW__)
	//Capitalise le charKey
	wxString charKeyCapital(charKey);
	charKeyCapital.MakeCapitalized();
	//Enregistre le raccourci
	RegisterHotKey(nullptr, id, (UINT)shortcutKey.getModifiers(), *charKeyCapital.fn_str());
	#endif
}

void Shortcut::unRegisterShortcut(ShortcutKey const& shortcutKey)
{	
	#if defined(__UNIX__)
	//Convertie charKey vers KeyCode
	char charKey[2] = {shortcutKey.getCharKey(), '\0'};
	KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
	//ungrab le raccourci
	XUngrabKey(_display, key, (unsigned int)shortcutKey.getModifiers(), _root);
	#elif defined(__WXMSW__)
	//Supprimer le raccourci
	UnregisterHotKey(nullptr, getId(shortcutKey));
	#endif
}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
	remove(ShortcutKey(modifiers, charKey));
}

void Shortcut::remove(ShortcutKey const& shortcutKey)
{
	if(_enable)
		unRegisterShortcut(shortcutKey);
    
    //supprime le lien
    _bind.erase(shortcutKey); 
}

int Shortcut::getId(ShortcutKey const& shortcutKey)
{
    return _bind[shortcutKey];
    return 0;
}

void Shortcut::enable(bool vale)
{		
	//si on doit désactiver
	if(_enable == true && vale == false)
	{
		for(auto &it: _bind)
			unRegisterShortcut(it.first);
	}
	//si on doit activer
	else if(_enable == false && vale == true)
	{		
		for(auto &it: _bind)
			registerShortcut(it.first);
	}
	
	_enable = vale;
}
