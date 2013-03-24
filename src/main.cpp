//30/11/12
//version : 1.x

#include "main.hpp"

#include <unistd.h>

#include <wx/aboutdlg.h>
//#include <wx/utils.h> 
//#include <wx/process.h>
#include <wx/fileconf.h>

//Dialog
#include "dialogPreferences.hpp"

//Test
#include <iostream>
#include "action/actTranslation.hpp"
#include "shortcut.hpp"

IMPLEMENT_APP(App);

bool App::OnInit()
{  	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	_menuIcon = nullptr;
	
	_actionManager = new ActionManager();
	
	
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	bool showMenu = true;
	fileConfig.Read("show_menu", &showMenu);
	
	//Création du menu ou pas.
	if(showMenu)
		creatMenuItem();
	else
		deleteMenuItem();
		
	//Installation des raccourcis et actions
	_actionManager->load(fileConfig);
	
	//_actionManager->sove(fileConfig);

	return true;
}

int App::OnExit()
{	
	//Suppression du menu.
	deleteMenuItem();
	
	//Suppression du mangeur d'action.
	delete _actionManager;

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
	static DialogPreferences *dlg = nullptr;
	
	//On lance le dialog si il n'est pas déjà lancer.
	if(dlg == nullptr)
	{
		//Création du dialog.
		dlg = new DialogPreferences();
		
		//Désactivation des raccourcis.
		_actionManager->enable(false);
		
		//Affichage du dialog.
		if(dlg->ShowModal() == wxID_OK)
		{
			//On vérifie si on doit quitter l'application ou pas.
			if(dlg->shutdownIsToggle())
				ExitMainLoop();
		}
		
		//On réactive les raccourcis
		_actionManager->enable(true);
		
		//Supprime le dialog
		delete dlg;
		dlg = nullptr;
	}	
	//Sinon on l'affiche au premier plan.
	else
		dlg->Raise();
}

void App::OnEnable(wxCommandEvent& event)
{
	_actionManager->enable(event.IsChecked());
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
