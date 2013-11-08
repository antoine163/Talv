//! \file **************************************************************
//! \brief Source TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.7
//! \date 10.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#include "taskIcon.hpp"

#include "resource.hpp"
#include "actionManager.hpp"
#include "dialogPreferences.hpp"

#include <wx/event.h>
#include <wx/icon.h>
#include <wx/artprov.h>
#include <wx/aboutdlg.h>
#include <wx/app.h>

//TEST
#include <iostream>

// *********************************************************************
// Class TaskIcon
// *********************************************************************

TaskIcon::TaskIcon(wxTaskBarIconType iconType)
: wxTaskBarIcon(iconType), _enableShortcuts(true)
{
	//Task Icon
	wxIcon tmpIcon;
	tmpIcon.LoadFile("../icons/16x16/" PROJECT_NAME ".png", wxBITMAP_TYPE_PNG);
	SetIcon(tmpIcon, PROJECT_NAME);
	
	//Init id
	_idEnableShortcuts = wxNewId();
	
	//Bind des évènement des itère du menue
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnPreferences, this, wxID_PREFERENCES);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnEnableShortcuts, this, _idEnableShortcuts);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnAbout, this, wxID_ABOUT);
}

TaskIcon::~TaskIcon()
{
	//Bind des évènement des itère du menue
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnPreferences, this, wxID_PREFERENCES);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnEnableShortcuts, this, _idEnableShortcuts);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskIcon::OnAbout, this, wxID_ABOUT);
}
		
wxMenu* TaskIcon::CreatePopupMenu()
{
	//Menu
	wxMenu* menu = new wxMenu();
	
	//Item Preferences
	wxMenuItem* itemPreferences = new wxMenuItem(menu, wxID_PREFERENCES, _("Preferences"), _("Open Preferences"), wxITEM_NORMAL);
	menu->Append(itemPreferences);
	
	//Item EnableShortcuts
	wxMenuItem* itemEnableShortcuts = new wxMenuItem(menu, _idEnableShortcuts, _("Enable Shortcuts"), _("Activate Shortcuts"), wxITEM_CHECK);
	menu->Append(itemEnableShortcuts);
	itemEnableShortcuts->Check(_enableShortcuts);
	
	//Item About
	wxMenuItem* itemAbout = new wxMenuItem(menu, wxID_ABOUT, _("About"), _("About")+" "+PROJECT_NAME, wxITEM_NORMAL);
	menu->Append(itemAbout);
	
	//Item Exit
	wxMenuItem* itemExit = new wxMenuItem(menu, wxID_EXIT, _("Exit"), _("Exit")+" "+PROJECT_NAME, wxITEM_NORMAL);
	menu->Append(itemExit);
	
	return menu;
}

void TaskIcon::OnAbout(wxCommandEvent&)
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
	info.SetWebSite("http://antoine163.github.com/Talv/");
	info.AddDeveloper("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	info.AddDocWriter("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	wxAboutBox(info);
}

void TaskIcon::OnPreferences(wxCommandEvent&)
{
	//Récupération de l'instance de ActionManager;
	ActionManager* actionManager = ActionManager::getInstance();
	
	//Désactivation des raccourcis.
	actionManager->enableShortcuts(false);
	
	//Création du dialog.
	DialogPreferences dlg;
	
	//Affichage du dialog.
	if(dlg.ShowModal() == wxID_OK)
	{		
		//Vérification si on doit afficher ou pas l'icône dans la zone de notification.
		if(!Resource::getInstance()->getShowMenu())
			Destroy();
	}
	
	//On réactive les raccourcis.
	actionManager->enableShortcuts(_enableShortcuts);
}

void TaskIcon::OnEnableShortcuts(wxCommandEvent& event)
{
	_enableShortcuts = event.IsChecked();
	ActionManager::getInstance()->enableShortcuts(_enableShortcuts);
}
