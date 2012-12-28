//30/11/12

#include "main.hpp"

#include <wx/clipbrd.h>
#include <gst/gst.h>

#include <iostream>

#if defined(__UNIX__)
#include <libnotify/notify.h>
#endif

IMPLEMENT_APP(App);

bool App::OnInit()
{
	//Init des bibliothèques.
	#if defined(__UNIX__)
	notify_init("flydocs");
	#endif
	gst_init(NULL, NULL);
	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	
	creatMenuItem();
	
	
	_shortcut = new Shortcut(this);	
	_shortcut->Create();
	_shortcut->Run();
	
	int id = _shortcut->creat((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'f');
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
	
	id = _shortcut->creat((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'd');
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);

	return true;
}

int App::OnExit()
{
	#if defined(__UNIX__)
	notify_uninit();
	#endif
	
	deleteMenuItem();
	//Unbind(EVT_SHORTCUT, &App::OnPreferences, this, _shortcut->_id);
	
	_shortcut->Kill();
	
	return 0;
}

void App::creatMenuItem()
{
	if(!_menuIcon)
	{
		_menuIcon = new MenuIcon();
		
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
	}
}

void App::deleteMenuItem()
{
	if(_menuIcon)
	{
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
		
		delete _menuIcon;
		_menuIcon = 0;
	}
}

void App::OnPreferences(wxCommandEvent&)
{	
}

void App::OnEnable(wxCommandEvent&)
{
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}

void App::OnShortcut(ShortcutEvent& event)
{
	translateClipBoard();
	
	if(event.getCharKey() == 'f')
	{
		_word.showNotify();
	}
	else if(event.getCharKey() == 'd')
	{
		_word.say();
	}
		
}

wxString App::getClipboard()const
{
	wxString word;
	
	//Lire le text ce trouvent dans la presse papier
	if (wxTheClipboard->Open())
	{
		#if defined(__UNIX__)
		wxTheClipboard->UsePrimarySelection(true);
		#endif
		if(wxTheClipboard->IsSupported(wxDF_TEXT))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData(data);
			word = data.GetText();
		}
		wxTheClipboard->Close();
	}
	
	return word;
}

void App::translateClipBoard()
{
	wxString lgsrc = "en";
	wxString lgto = "fr";
	
	wxString word = getClipboard();
	
	//Suppression des '\n'
	word.Replace("\n", " ");
	
	_word.setWord(word, lgsrc, lgto);
}

void App::soveTranslateClipBoard()
{
}

