//! \file **************************************************************
//! \brief Header MenuIcon.
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
		
		void enable(bool val=true);
		
		int getIdMenuItemPreferences();
		int getIdMenuItemEnableShortcuts();
		int getIdMenuItemAbout();
		int getIdMenuItemExit();

	private:
		void OnShow(wxTaskBarIconEvent&);
		
		bool _enable;
	
		wxTaskBarIcon* _taskBarIcon;
		wxMenu* _menuTaskBarIcon;
		wxMenuItem* _menuItemPreferences;
		wxMenuItem* _menuItemEnableShortcuts;
		wxMenuItem* _menuItemAbout;
		wxMenuItem* _menuItemExit;
};

#endif //MENU_ICON_H
