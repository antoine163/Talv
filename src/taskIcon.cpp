//! \file **********************************************************************
//! \brief Source TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
//! \date 10.12.12
//!
//! ****************************************************************************

//App
#include "taskIcon.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/menu.h>
#include <wx/icon.h>
#include <wx/artprov.h>
#include <wx/stdpaths.h>

//Test
#include <iostream>


// *****************************************************************************
// Class TaskIcon
// *****************************************************************************

TaskIcon::TaskIcon(wxTaskBarIconType iconType)
: wxTaskBarIcon(iconType)
{
	std::cout << wxStandardPaths::Get().GetUserDataDir() << std::endl;
	std::cout << wxStandardPaths::Get().GetDataDir() << std::endl;
	std::cout << wxStandardPaths::Get().GetLocalDataDir() << std::endl;
	
	
	//! \todo maitre le bon chemin vais l'iconne
	//Task Icon
	wxIcon tmpIcon;
	tmpIcon.LoadFile("../icons/16x16/" PROJECT_NAME ".png", wxBITMAP_TYPE_PNG);
	SetIcon(tmpIcon, PROJECT_NAME);
}

TaskIcon::~TaskIcon()
{
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
	
	//Item EnableShortcuts
	wxMenuItem* itemEnableShortcuts = new wxMenuItem(menu,
													ID_ENABLE_SHORTKUT,
													_("Enable Shortcuts"),
													_("Activate Shortcuts"),
													wxITEM_CHECK);
	menu->Append(itemEnableShortcuts);
	//!\todo a modifier avec le manager d'action
	itemEnableShortcuts->Check(true);
	
	//Item About
	wxMenuItem* itemAbout = new wxMenuItem(	menu, 
											ID_ABOUT,
											_("About"),
											_("About")+" "+PROJECT_NAME,
											wxITEM_NORMAL);
	menu->Append(itemAbout);
	
	//Item Exit
	wxMenuItem* itemExit = new wxMenuItem(	menu, 
											ID_QUIT,
											_("Quit"),
											_("Quit")+" "+PROJECT_NAME,
											wxITEM_NORMAL);			
	itemExit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU));		
	menu->Append(itemExit);
	
	return menu;
}
