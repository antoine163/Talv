//10/12/12

#include "menuIcon.hpp"

#include <wx/event.h>
#include <wx/icon.h>

MenuIcon::MenuIcon()
{
	//Menu
	_menuTaskBarIcon = new wxMenu();
	
	//Menu Item
	_menuItemPreferences = new wxMenuItem(_menuTaskBarIcon, wxID_ANY, wxString(_("Preferences")), wxEmptyString, wxITEM_NORMAL);
	_menuTaskBarIcon->Append(_menuItemPreferences);
	
	_menuItemEnable = new wxMenuItem(_menuTaskBarIcon, wxID_ANY, wxString(_("Enable")), wxEmptyString, wxITEM_CHECK);
	_menuTaskBarIcon->Append(_menuItemEnable);
	
	_menuItemExit = new wxMenuItem(_menuTaskBarIcon, wxID_ANY, wxString(_("Exit")), wxEmptyString, wxITEM_NORMAL);
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
	delete _menuTaskBarIcon;
	//delete _menuItemPreferences;
	//delete _menuItemEnable;
	//delete _menuItemExit;
}

int MenuIcon::getIdMenuItemPreferences()
{
	return _menuItemPreferences->GetId();
}

int MenuIcon::getIdMenuItemEnable()
{
	return _menuItemEnable->GetId();
}

int MenuIcon::getIdMenuItemExit()
{
	return _menuItemExit->GetId();
}

void MenuIcon::OnShow(wxTaskBarIconEvent&)
{
	_taskBarIcon->PopupMenu(_menuTaskBarIcon);
}
