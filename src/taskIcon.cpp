//! \file **********************************************************************
//! \brief Source TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.9
//! \date 10.12.12
//!
//! ****************************************************************************

//App
#include "taskIcon.hpp"
#include "defs.hpp"
#include "manager/manGeneral.hpp"
#include "manager/manAction.hpp"

//WxWidgets
#include <wx/menu.h>
#include <wx/icon.h>
#include <wx/artprov.h>
#include <wx/stdpaths.h>

// *****************************************************************************
// Class TaskIcon
// *****************************************************************************

TaskIcon::TaskIcon(wxTaskBarIconType iconType)
: wxTaskBarIcon(iconType), _enableMenu(true)
{
	//Task Icon
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16), PROJECT_NAME);
}

TaskIcon::~TaskIcon()
{
}

void TaskIcon::enable(bool enable)
{
	_enableMenu = enable;
}
		
wxMenu* TaskIcon::CreatePopupMenu()
{

		
	//Menu
	wxMenu* menu = new wxMenu();
	
	//Item Preferences
	wxMenuItem* itemPreferences = new wxMenuItem(	menu,
													ID_PREFERENCES,
													_("Preferences"),
													_("Open Preferences"),
													wxITEM_NORMAL);
	menu->Append(itemPreferences);
	itemPreferences->Enable(_enableMenu);
	
	//Item EnableShortcuts
	wxMenuItem* itemEnableShortcuts = new wxMenuItem(menu,
													ID_ENABLE_SHORTKUT,
													_("Enable Shortcuts"),
													_("Activate Shortcuts"),
													wxITEM_CHECK);
	menu->Append(itemEnableShortcuts);
	itemEnableShortcuts->Check(ManAction::get().shortcutsIsEnable());
	itemEnableShortcuts->Enable(_enableMenu);
	
	//Item About
	wxMenuItem* itemAbout = new wxMenuItem(	menu, 
											ID_ABOUT,
											_("About"),
											_("About")+" "+PROJECT_NAME,
											wxITEM_NORMAL);
	menu->Append(itemAbout);
	itemAbout->Enable(_enableMenu);
	
	//Item Exit
	wxMenuItem* itemExit = new wxMenuItem(	menu, 
											ID_QUIT,
											_("Quit"),
											_("Quit")+" "+PROJECT_NAME,
											wxITEM_NORMAL);			
	itemExit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU));		
	menu->Append(itemExit);
	itemExit->Enable(_enableMenu);
	
	return menu;
}
