//30/11/12

#include "main.hpp"

#include <wx/aboutdlg.h>

#if defined(__USE_TTS__)
#include <gst/gst.h>
#endif

#if defined(__UNIX__)
#include <libnotify/notify.h>
#endif

#include "dialogPreferences.hpp"

#include <iostream>
#include <wx/utils.h> 

IMPLEMENT_APP(App);

bool App::OnInit()
{
	//Init des bibliothèques.
	#if defined(__UNIX__)
	notify_init(PROJECT_NAME);
	#endif
	#if defined(__USE_TTS__)
	gst_init(NULL, NULL);
	#endif
	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	bool showMenu = true;
	fileConfig.Read("show_menu", &showMenu);
	
	//Création du menu ou pas.
	if(showMenu)
		creatMenuItem();

	//Création est chargement des raccourci clavier
	_shortcut = new Shortcut(this);	
	loadShortcut(fileConfig);

	//_shif_alt_f = new ShortcutKey((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'f');
	//int id = _shortcut->creat(*_shif_alt_f);
	//Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
	
	//#if defined(__USE_TTS__)
	//_shif_alt_d = new ShortcutKey((KeyModifier)(KeyModifier::SHIFT|KeyModifier::ALT), 'd');
	//id = _shortcut->creat(*_shif_alt_d);
	//Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
	//#endif
	

	return true;
}

int App::OnExit()
{
	#if defined(__UNIX__)
	notify_uninit();
	#endif
	
	deleteMenuItem();
	
	delete _shortcut;
	
	//delete _shif_alt_f;
	//delete _shif_alt_d;
	
	return 0;
}

void App::creatMenuItem()
{
	if(!_menuIcon)
	{
		_menuIcon = new MenuIcon();
		
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, _menuIcon->getIdMenuItemAbout());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
	}
}

void App::deleteMenuItem()
{
	if(_menuIcon)
	{
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, _menuIcon->getIdMenuItemAbout());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
		
		delete _menuIcon;
		_menuIcon = nullptr;
	}
}

void App::OnPreferences(wxCommandEvent&)
{	
	DialogPreferences *dlg = new DialogPreferences();
    dlg->ShowModal();
    dlg->Destroy();
}

void App::OnEnable(wxCommandEvent& event)
{
	_shortcut->enable(event.IsChecked());
}

void App::OnAbout(wxCommandEvent&)
{
	wxAboutDialogInfo info;

	info.SetName(PROJECT_NAME);
	info.SetVersion(PROJECT_VERSION);
	
	wxString msg;
	msg << _("This software using google translate for translate a word or sentence from your clipboard.");
	msg << _("\n\nBuild on ");
	#if defined(__UNIX__)
	msg << _("Unix ");
	#elif defined(__WXMSW__)
	msg << _("Windows ");
	#endif
	#ifdef __i386
	msg << _("in i386\n");
	#elif __amd64
	msg << _("in x86_64\n");
	#endif
	msg << _("Date : ") << __DATE__;
	
	info.SetDescription(msg);
	info.SetCopyright("(C) 2012");
	info.SetWebSite("http://antoine163.github.com/flydocs/");
	info.AddDeveloper("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	info.AddDocWriter("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	wxAboutBox(info);
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}

void App::OnShortcut(ShortcutEvent& event)
{
	//translateClipBoard();
	
	//if(event.getShortcutKey() == *_shif_alt_f)
	//{
		//_word.showNotify();
	//}
	//#if defined(__USE_TTS__)
	//else if(event.getShortcutKey() == *_shif_alt_d)
	//{
		//_word.say();
	//}
	//#endif
}

void App::loadShortcut(wxFileConfig const& fileConfig)
{
	wxString stringShortcutConfig;
	
	unsigned int i = 1;
	
	while(fileConfig.Read(wxString("shortcut")<<i, &stringShortcutConfig))
	{		
		wxString stringAct;
		wxString stringShortcut = stringShortcutConfig.BeforeFirst(' ', &stringAct);
		
		std::cout << stringShortcut << std::endl;
		std::cout << stringAct << std::endl;
		
		i++;
	}
}
