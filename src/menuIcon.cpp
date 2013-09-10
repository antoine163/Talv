//! \file **************************************************************
//! \brief Source MenuIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.6
//! \date 10.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#include "menuIcon.hpp"

#include <wx/event.h>
#include <wx/icon.h>
#include <wx/artprov.h>

// *********************************************************************
// Class MenuIcon
// *********************************************************************

MenuIcon::MenuIcon()
: _enable(true)
{
	//Menu
	_menuTaskBarIcon = new wxMenu();
	
	//Menu Item
	_menuItemPreferences = new wxMenuItem(_menuTaskBarIcon, wxID_PREFERENCES, _("Preferences"), _("Open Preferences"), wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemPreferences);
	
	_menuItemEnableShortcuts = new wxMenuItem(_menuTaskBarIcon, wxID_ANY, _("Enable Shortcuts"), _("Activate Shortcuts"), wxITEM_CHECK);
	_menuTaskBarIcon->Append(_menuItemEnableShortcuts);
	_menuItemEnableShortcuts->Check(true);
	
	_menuItemAbout = new wxMenuItem(_menuTaskBarIcon, wxID_ABOUT, _("About"), _("About")+" "+PROJECT_NAME, wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemAbout);
	
	_menuItemExit = new wxMenuItem(_menuTaskBarIcon, wxID_EXIT, _("Exit"), _("Exit")+" "+PROJECT_NAME, wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemExit);
	
	//Task Icon
	_taskBarIcon = new wxTaskBarIcon;
	wxIcon tmpIcon;
	tmpIcon.LoadFile("../icons/16x16/" PROJECT_NAME ".png", wxBITMAP_TYPE_PNG);
	_taskBarIcon->SetIcon(tmpIcon, PROJECT_NAME);
	
	//bind l'événement
	_taskBarIcon->Bind(wxEVT_TASKBAR_CLICK, &MenuIcon::OnShow, this);
}

MenuIcon::~MenuIcon()
{
	_taskBarIcon->Unbind(wxEVT_TASKBAR_CLICK, &MenuIcon::OnShow, this);
	
	delete _taskBarIcon;
	delete _menuTaskBarIcon;
}

void MenuIcon::enable(bool val)
{
	_enable = val;
}

int MenuIcon::getIdMenuItemPreferences()
{
	return _menuItemPreferences->GetId();
}

int MenuIcon::getIdMenuItemEnableShortcuts()
{
	return _menuItemEnableShortcuts->GetId();
}

int MenuIcon::getIdMenuItemAbout()
{
	return _menuItemAbout->GetId();
}

int MenuIcon::getIdMenuItemExit()
{
	return _menuItemExit->GetId();
}

void MenuIcon::OnShow(wxTaskBarIconEvent&)
{
	if(_enable)
		_taskBarIcon->PopupMenu(_menuTaskBarIcon);
}
