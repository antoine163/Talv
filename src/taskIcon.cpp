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


// *****************************************************************************
// Class TaskIcon
// *****************************************************************************

TaskIcon::TaskIcon(wxTaskBarIconType iconType)
: wxTaskBarIcon(iconType)
{
	//Task Icon
	//! \todo implémenter avec managerGeneral
	wxIcon tmpIcon;
	#if defined(__WXMSW__)
	tmpIcon.LoadFile(FILE_NAME_APP_ICONS, wxBITMAP_TYPE_PNG);
	#else
	if(wxFileExists(FILE_NAME_APP_ICONS))
		tmpIcon.LoadFile(FILE_NAME_APP_ICONS, wxBITMAP_TYPE_PNG);
	else
		tmpIcon.LoadFile(wxStandardPaths::Get().GetDataDir()+
						'/'+FILE_NAME_APP_ICONS, wxBITMAP_TYPE_PNG);
	#endif
	
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
