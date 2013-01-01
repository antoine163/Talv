//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 0.2
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

ShortcutEvent::ShortcutEvent(int id, wxEventType eventType, KeyModifier modifiers, char charKey)
    : wxEvent(id, eventType), _modifiers(modifiers), _charKey(charKey)
{
}

wxEvent* ShortcutEvent::Clone()const
{
    return new ShortcutEvent(*this);
}

char ShortcutEvent::getCharKey()const
{
    return _charKey;
}

KeyModifier ShortcutEvent::getModifiers()const
{
    return _modifiers;
}

wxDEFINE_EVENT(EVT_SHORTCUT, ShortcutEvent);


Shortcut::Shortcut(wxApp *owner) : _owner(owner)
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
	//création d'un nouveau id
    int id = wxNewId();
    
    //Création d'un lien et ajout de l'id
    _bind[((long long int)charKey<<(sizeof(long long int)*7))|(long long int)modifiers] = id;
    
    #if defined(__UNIX__)
    //Convertie charKey vers KeyCode
    KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(&charKey));
    //grab le raccourci
    XGrabKey(_display, key, (unsigned int)modifiers, _root, True, GrabModeAsync, GrabModeAsync);
	#elif defined(__WXMSW__)
	//Capitalise le charKey
	wxString charKeyCapital(charKey);
	charKeyCapital.MakeCapitalized();
	//Enregistre le raccourci
	RegisterHotKey(nullptr, id, (UINT)modifiers, *charKeyCapital.fn_str());
	#endif
    
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
			//Recherche de l'id
			int id = getId((KeyModifier)_event.xkey.state, charKey);
			//Envoi de l'événement
			ShortcutEvent *event = new ShortcutEvent(id, EVT_SHORTCUT, (KeyModifier)_event.xkey.state, charKey);
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
				if(it.second == (int)_msgEvent.wParam)
				{
					//Envoi de l'événement
					ShortcutEvent *event = new ShortcutEvent	(it.second, EVT_SHORTCUT,
																(KeyModifier)it.first,
																(char)(it.first>>(sizeof(long long int)*7)));
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

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
    #if defined(__UNIX__)
    //Convertie charKey vers KeyCode
    KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(&charKey));
    //ungrab le raccourci
    XUngrabKey(_display, key, (unsigned int)modifiers, _root);
    #elif defined(__WXMSW__)
    //Capitalise le charKey
    wxString charKeyCapital(charKey);
	charKeyCapital.MakeCapitalized();
	//Supprimer le raccourci
    UnregisterHotKey(nullptr, getId(modifiers, *charKeyCapital.fn_str()));
    #endif
    
    //supprime le lien
    _bind.erase(((long long int)charKey<<(sizeof(long long int)*7))|(long long int)modifiers); 
}

int Shortcut::getId(KeyModifier modifiers, char charKey)
{
    return _bind[((long long int)charKey<<(sizeof(long long int)*7))|(long long int)modifiers];
}
