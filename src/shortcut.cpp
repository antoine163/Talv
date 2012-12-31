//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
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

#include <iostream>

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
	wxString charKeyCapital(charKey);
	charKeyCapital.MakeCapitalized();
	RegisterHotKey(nullptr, id, (UINT)modifiers, *charKeyCapital.fn_str());
	#endif
    
    return id;
}

void Shortcut::OnIdle(wxIdleEvent& event)
{
	if(GetMessage(&_msgEvent, NULL, 0, 0) != 0)
    {
        if (_msgEvent.message == WM_HOTKEY)
        {
			for(auto &it: _bind)
			{
				if(it.second == (int)_msgEvent.wParam)
				{
					//Envoi de l'événement
					ShortcutEvent *event = new ShortcutEvent(it.second, EVT_SHORTCUT,
															(KeyModifier)it.first,
															(char)(it.first>>(sizeof(long long int)*7)));
					wxQueueEvent(_owner, event);
					
					break;
				}
			}

		}
	}
	
	// render continuously, not only once on idle
	event.RequestMore(); 
}

//wxThread::ExitCode Shortcut::Entry()
//{
	//#if defined(__UNIX__)
    //while(1)
    //{
		//XNextEvent(_display, &_event);
		//if(_event.type == KeyPress)
		//{ 
			////Convertie le KeyCode en char
			//const char charKey = *(XKeysymToString(XkbKeycodeToKeysym(_display, _event.xkey.keycode, 0, 0)));
			////Recherche de l'id
			//int id = getId((KeyModifier)_event.xkey.state, charKey);
			////Envoi de l'événement
			//ShortcutEvent *event = new ShortcutEvent(id, EVT_SHORTCUT, (KeyModifier)_event.xkey.state, charKey);
			//wxQueueEvent(_owner, event);
		//}
    //}
	//#elif defined(__WXMSW__)
	
	//for(auto &it: _bind)
	//{
		//std::cout << ((char)(it.first>>(sizeof(long long int)*7))) << std::endl;
		//RegisterHotKey(NULL, it.second, (UINT)it.first, ((char)(it.first>>(sizeof(long long int)*7))));
	//}

    //MSG msg;
    //while (GetMessage(&msg, NULL, 0, 0) != 0)
    //{
		//std::cout << "GetMessage" << std::endl;
        //if (msg.message == WM_HOTKEY)
        //{
			//std::cout << "WM_HOTKEY received : " << std::endl;
			//std::cout << "msg.hwnd : " << msg.hwnd << std::endl;
			//std::cout << "msg.message : " << msg.message << std::endl;
			//std::cout << "msg.wParam : " << msg.wParam << std::endl;
			//std::cout << "msg.lParam : " << msg.lParam << std::endl;
			//std::cout << "msg.time : " << msg.time << std::endl;
			//std::cout << "msg.pt.x : " << msg.pt.x << std::endl;
			//std::cout << "msg.pt.y : " << msg.pt.y << std::endl;
			
			////wxCommandEvent *event = new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, 12);
			////wxQueueEvent(_owner, event);
        //}
    //}
	//#endif
    
    //return (wxThread::ExitCode)0;
//}

void Shortcut::remove(KeyModifier modifiers, char charKey)
{
    #if defined(__UNIX__)
    //Convertie charKey vers KeyCode
    KeyCode key = XKeysymToKeycode(_display, XStringToKeysym(&charKey));
    //ungrab le raccourci
    XUngrabKey(_display, key, (unsigned int)modifiers, _root);
    #elif defined(__WXMSW__)
    wxString charKeyCapital(charKey);
	charKeyCapital.MakeCapitalized();
    UnregisterHotKey(nullptr, getId(modifiers, *charKeyCapital.fn_str()));
    #endif
    
    //supprime le lien
    _bind.erase(((long long int)charKey<<(sizeof(long long int)*7))|(long long int)modifiers); 
}

int Shortcut::getId(KeyModifier modifiers, char charKey)
{
    return _bind[((long long int)charKey<<(sizeof(long long int)*7))|(long long int)modifiers];
}
