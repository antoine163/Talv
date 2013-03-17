//30/11/12
//version : 1.0

#include "main.hpp"

#include <unistd.h>

#include <wx/aboutdlg.h>
#include <wx/utils.h> 
#include <wx/process.h>

#include <iostream>

IMPLEMENT_APP(App);

bool App::OnInit()
{  	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	_menuIcon = nullptr;
	
	//Création du gestionnaire de raccourci clavier
	_shortcut = new Shortcut(this);	
	
	ShortcutKey shortcutKey1(ShortcutKey::stringToShortcutKey("alt+shift+f"));
	int id1 = _shortcut->creat(shortcutKey1);
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id1);
	
	ShortcutKey shortcutKey2(ShortcutKey::stringToShortcutKey("shift+super+a"));
	int id2 = _shortcut->creat(shortcutKey2);
	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id2);
	
	creatMenuItem();

	return true;
}

int App::OnExit()
{	
	//Suppression du menu
	deleteMenuItem();
	
	delete _shortcut;

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
		msg << _("This software using google translate to translate a word or sentence from your clipboard.");
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
		info.SetCopyright("(C) 2012-1013");
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
	std::cout << ShortcutKey::shortcutKeyToString(event.getShortcutKey()) << std::endl;
}
