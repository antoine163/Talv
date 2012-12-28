//! \file **********************************************************************
//! - Compilateur : GCC
//!
//! \author Maleyrie Antoine
//! \version 0.1
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2011 - Antoine Maleyrie.
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


Shortcut::Shortcut(wxEvtHandler *owner) : _owner(owner)
{
    #if defined(__UNIX__)
    _display = XOpenDisplay(0);
    _root = XDefaultRootWindow(_display);
    #endif
}

Shortcut::~Shortcut()
{
    #if defined(__UNIX__)
    XCloseDisplay(_display);
    #endif
}

int Shortcut::creat(KeyModifier modifiers, char charKey)
{
    #if defined(__UNIX__)
    //Convertie charKey vers KeyCode
    KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(&charKey));
    
    //grab le raccourci
    XGrabKey(_display, key, (unsigned int)modifiers, _root, True, GrabModeAsync, GrabModeAsync);
    #endif
    
    //création d'un nouveau id
    int id = wxNewId();
    
    //Création d'un lien et ajout de l'id
    _bind[((long int)charKey<<(sizeof(long int)*7))|(long int)modifiers] = id;
    
    return id;
}

wxThread::ExitCode Shortcut::Entry()
{
    while(1)
    {
	#if defined(__UNIX__)
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
	#endif
    }
    
    return (wxThread::ExitCode)0;
}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
}

int Shortcut::getId(KeyModifier modifiers, char charKey)
{
    return _bind[((long int)charKey<<(sizeof(long int)*7))|(long int)modifiers];
}
