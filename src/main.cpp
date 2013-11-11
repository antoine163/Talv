//! \file **************************************************************
//! \brief Source Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.15
//! \date 12.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#include "main.hpp"
#include "resource.hpp"
#include "notification.hpp"
#include "managerAction.hpp"
//#include "managerList.hpp"
#include "dialogPreferences.hpp"

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
	_taskIcon = nullptr;
	
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
	
	//Chargement de la configuration des notifications.
	Notification::getInstance()->load(fileConfig);
	
	//Crée de l'instance de ActionManager et Installation des raccourcis/actions
	ManagerAction::getInstance()->load(fileConfig);

	//Chargement des listes se trouvent dans le fichier de config.
	//ManagerList::getInstance()->load(fileConfig);

	//Création du menu ou pas.
	if(Resource::getInstance()->getShowMenu())
		_taskIcon = new TaskIcon();
		
	//Bind pour attraper l'évènement pour quitter qui peut venir de n'importe où dans le code.
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, wxID_EXIT);
		
	return true;
}

int App::OnExit()
{	
	//Unbind l'évènement pour quitter.
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, wxID_EXIT);
	
	//Suppression du menu.
	delete _taskIcon;
	
	//Suppression du mangeur d'action.
	ManagerAction::kill();
	
	//Suppression des ressources.
	Resource::kill();
	
	//Suppression des notifications.
	Notification::kill();
	
	//Suppression des liste.
	//ManagerList::kill();
	
	//Suppression du module de la traduction de l'application.
	delete _locale;
	
	return 0;
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}
