//10/12/12

#ifndef MENU_ICON_H
#define MENU_ICON_H

#include <wx/menu.h>
#include <wx/taskbar.h>

class MenuIcon
{
	public:
		MenuIcon();
		~MenuIcon();
		
		int getIdMenuItemPreferences();
		int getIdMenuItemEnable();
		int getIdMenuItemExit();

	private:
		void OnShow(wxTaskBarIconEvent&);
	
		wxTaskBarIcon* _taskBarIcon;
		wxMenu* _menuTaskBarIcon;
		wxMenuItem* _menuItemPreferences;
		wxMenuItem* _menuItemEnable;
		wxMenuItem* _menuItemExit;
};

#endif //MENU_ICON_H
