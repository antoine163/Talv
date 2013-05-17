//! \file **************************************************************
//! \brief Header MenuIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 10.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#ifndef MENU_ICON_H
#define MENU_ICON_H

#include <wx/menu.h>
#include <wx/taskbar.h>

// *********************************************************************
// Class MenuIcon
// *********************************************************************

//! \brief Menu dans la zone de notification.
class MenuIcon
{
	public:
		MenuIcon();
		~MenuIcon();
		
		int getIdMenuItemPreferences();
		int getIdMenuItemEnableShortcuts();
		int getIdMenuItemEnableActions();
		int getIdMenuItemAbout();
		int getIdMenuItemExit();

	private:
		void OnShow(wxTaskBarIconEvent&);
	
		wxTaskBarIcon* _taskBarIcon;
		wxMenu* _menuTaskBarIcon;
		wxMenuItem* _menuItemPreferences;
		wxMenuItem* _menuItemEnableShortcuts;
		wxMenuItem* _menuItemEnableActions;
		wxMenuItem* _menuItemAbout;
		wxMenuItem* _menuItemExit;
};

#endif //MENU_ICON_H
