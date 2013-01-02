//30/11/12

#include "main.hpp"

#include <wx/clipbrd.h>

#if defined(__USE_TTS__)
#include <gst/gst.h>
#endif

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
	#if defined(__USE_TTS__)
	gst_init(NULL, NULL);
	#endif
	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	
	creatMenuItem();

	_shortcut = new Shortcut(this);	
	
	_shif_alt_f = new ShortcutKey((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'f');
	int id = _shortcut->creat(*_shif_alt_f);
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
	
	#if defined(__USE_TTS__)
	_shif_alt_d = new ShortcutKey((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'd');
	id = _shortcut->creat(*_shif_alt_d);
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
	#endif

	return true;
}

int App::OnExit()
{
	#if defined(__UNIX__)
	notify_uninit();
	#endif
	
	deleteMenuItem();
	
	delete _shortcut;
	
	delete _shif_alt_f;
	delete _shif_alt_d;
	
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

void App::OnEnable(wxCommandEvent& event)
{
	_shortcut->enable(event.IsChecked());
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}

void App::OnShortcut(ShortcutEvent& event)
{
	translateClipBoard();
	
	if(event.getShortcutKey() == *_shif_alt_f)
	{
		_word.showNotify();
	}
	#if defined(__USE_TTS__)
	else if(event.getShortcutKey() == *_shif_alt_d)
	{
		_word.say();
	}
	#endif
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

