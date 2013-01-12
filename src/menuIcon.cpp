//10/12/12

#include "menuIcon.hpp"

#include <wx/event.h>
#include <wx/icon.h>
#include <wx/artprov.h>

MenuIcon::MenuIcon()
{
	//Menu
	_menuTaskBarIcon = new wxMenu();
	
	//Menu Item
	_menuItemPreferences = new wxMenuItem(_menuTaskBarIcon, wxID_PREFERENCES, _("Preferences"), _("Open Preferences"), wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemPreferences);
	
	_menuItemEnable = new wxMenuItem(_menuTaskBarIcon, wxID_ANY, _("Enable"), _("Activate shortcut"), wxITEM_CHECK);
	_menuTaskBarIcon->Append(_menuItemEnable);
	_menuItemEnable->Check(true);
	
	_menuItemAbout = new wxMenuItem(_menuTaskBarIcon, wxID_ABOUT, _("About"), _("About Flydocs"), wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemAbout);
	
	_menuItemExit = new wxMenuItem(_menuTaskBarIcon, wxID_EXIT, _("Exit"), _("Exit Flydocs"), wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemExit);
	
	//Task Icon
	_taskBarIcon = new wxTaskBarIcon;
	_taskBarIcon->SetIcon(wxIcon("ft.png", wxBITMAP_TYPE_PNG), "flying translation");
	
	//bind les événement
	_taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DCLICK, &MenuIcon::OnShow, this);
}

MenuIcon::~MenuIcon()
{
	_taskBarIcon->Unbind(wxEVT_TASKBAR_LEFT_DCLICK, &MenuIcon::OnShow, this);
	
	delete _taskBarIcon;
	//! \todo Libérais la mémoire sans Segmentation fault
	delete _menuTaskBarIcon;
}

int MenuIcon::getIdMenuItemPreferences()
{
	return _menuItemPreferences->GetId();
}

int MenuIcon::getIdMenuItemEnable()
{
	return _menuItemEnable->GetId();
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
	_taskBarIcon->PopupMenu(_menuTaskBarIcon);
}
