//! \file **************************************************************
//! \brief Source Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.9
//! \date 12.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#include "main.hpp"
#include "resource.hpp"
#include "actionManager.hpp"
#include "listManager.hpp"
#include "dialogPreferences.hpp"

#include <wx/aboutdlg.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <unistd.h>

//TEST
#include <iostream>

// *********************************************************************
// Class App
// *********************************************************************

IMPLEMENT_APP(App);

bool App::OnInit()
{  	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	_menuIcon = nullptr;
	
	//Changement du Préfixe seulement sous unix
	#if defined(__UNIX__)
	wxStandardPaths::Get().SetInstallPrefix("/usr");
	#endif
	
	//On charge le langage par défaut de l'os.
	_locale = new wxLocale(wxLANGUAGE_DEFAULT);
	_locale->AddCatalog(PROJECT_NAME);
	
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
	
	//Chargement des ressource se trouvent dans le fichier de config.
	Resource::getInstance()->load(fileConfig);
	
	//Chargement des listes se trouvent dans le fichier de config.
	ListManager::getInstance()->load(fileConfig);
		
	//Crée de l'instance de ActionManager et Installation des raccourcis/actions
	ActionManager::getInstance()->load(fileConfig);
	
	//Création du menu ou pas.
	if(Resource::getInstance()->getShowMenu())
		creatMenuItem();
	else
		deleteMenuItem();
	
	return true;
}

int App::OnExit()
{	
	//Suppression du menu.
	deleteMenuItem();
	
	//Suppression du mangeur d'action.
	ActionManager::kill();
	
	//Suppression des ressources.
	Resource::kill();
	
	//Suppression des liste.
	ListManager::kill();
	
	//Suppression du module de la traduction de l'application.
	delete _locale;
	
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

//! \bug Segmentation fault quand appelle de deleteMenuItem
//! \todo Désactiver le menu
void App::OnPreferences(wxCommandEvent&)
{
	static DialogPreferences *dlg = nullptr;
	
	//On lance le dialog si il n'est pas déjà lancer.
	if(dlg == nullptr)
	{
		//Récupération de l'instance de ActionManager;
		ActionManager* actionManager = ActionManager::getInstance();
	
		//Désactivation des raccourcis.
		actionManager->enableShortcut(false);
		
		//Création du dialog.
		dlg = new DialogPreferences();
		
		//Affichage du dialog.
		if(dlg->ShowModal() == wxID_OK)
		{	
			//On vérifie si on doit quitter l'application ou pas.
			if(dlg->shutdownIsToggle())
				ExitMainLoop();
				
			//Vérification si on doit afficher ou pas l'icône dans la zone de notification.
			if(Resource::getInstance()->getShowMenu())
				creatMenuItem();
			else
				deleteMenuItem();
		}
		
		//On réactive les raccourcis
		actionManager->enableShortcut(true);
		
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
	ActionManager::getInstance()->enableShortcut(event.IsChecked());
}

//! \todo Désactiver le menu
void App::OnAbout(wxCommandEvent&)
{
		wxAboutDialogInfo info;

		info.SetName(PROJECT_NAME);
		info.SetVersion(PROJECT_VERSION);
		
		wxString msg;
		msg << _("This software is help for Internationalization.") << "\n\n";
		msg << _("Build on") << " ";
		#if defined(__UNIX__)
		msg << "Unix";
		#elif defined(__WXMSW__)
		msg << "Windows";
		#endif
		#ifdef __i386
		msg << " " << _("in") << " " << " i386\n";
		#elif __amd64
		msg << " " << _("in") << " " << " x86_64\n";
		#endif
		msg << _("Date") <<  " : " << __DATE__;
		
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
