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
#include "managerAction.hpp"
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
	
	wxIcon tmpIcon;
	tmpIcon.LoadFile("../icons/32x32/" PROJECT_NAME ".png", wxBITMAP_TYPE_PNG);
	info.SetIcon(tmpIcon);
	
	wxString msg;
	msg << _("Traduction A La Volées \n Translation on the fly in English") << "\n\n";
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
	info.SetWebSite("http://antoine163.github.com/talv/");
	
	info.AddDeveloper("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	info.AddDocWriter("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	//info.AddTranslator("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	
	info.SetLicence(
	"The MIT License (MIT)\n\n"\
	
	"Copyright © 2012-2013 - Antoine Maleyrie.\n\n"\

	"Permission is hereby granted, free of charge, to any person obtaining a copy\n"\
	"of this software and associated documentation files (the \"Software\"), to deal\n" \
	"in the Software without restriction, including without limitation the rights\n" \
	"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n" \
	"copies of the Software, and to permit persons to whom the Software is\n"\
	"furnished to do so, subject to the following conditions:\n\n"\

	"The above copyright notice and this permission notice shall be included in all\n"\
	"copies or substantial portions of the Software.\n\n"\

	"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"\
	"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"\
	"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"\
	"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"\
	"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"\
	"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"\
	"SOFTWARE.");
	
	wxAboutBox(info);
}

void TaskIcon::OnPreferences(wxCommandEvent&)
{
	//Création du dialog.
	DialogPreferences dlg;
	
	//Affichage du dialog.
	if(dlg.ShowModal() == wxID_OK)
	{		
		//Vérification si on doit afficher ou pas l'icône dans la zone de notification.
		if(!Resource::getInstance()->getShowMenu())
			Destroy();
	}
}

void TaskIcon::OnEnableShortcuts(wxCommandEvent& event)
{
	_enableShortcuts = event.IsChecked();
	ManagerAction::getInstance()->enableShortcuts(_enableShortcuts);
}
