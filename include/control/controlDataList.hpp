//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 26.09.2013
//!
//! ****************************************************************************

#ifndef CONTROL_DATA_LIST_H
#define CONTROL_DATA_LIST_H

//Stl
#include <vector>

//WxWidgets
#include <wx/dataview.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/window.h>

// *****************************************************************************
// Enum Enable_e
// *****************************************************************************
enum Enable_e
{
	ENABLE_ANYTIME,
	ENABLE_SELECTING_ITEMS,
	ENABLE_SELECTING_ONE_ITEM
};

// *****************************************************************************
// Class ControlDataList
// *****************************************************************************

class ControlDataList : public wxDataViewListCtrl
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		ControlDataList(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~ControlDataList();

		void addWindowEnable(	wxWindow* Window,
								Enable_e eanble);
		wxMenuItem* addMenuItem(	wxWindowID id,
									wxString const& label=wxEmptyString,
									Enable_e eanble = ENABLE_ANYTIME);
		void addMenuItemSeparator();

	private:
		void onItemContextMenu(wxDataViewEvent& event);
		void onSelectionChanger(wxDataViewEvent& event);
		void updateEnableElements();
		
		wxMenu* _menu;
		
		std::vector<wxMenuItem*> _menuItemsEnableItems;
		std::vector<wxMenuItem*> _menuItemsEnableOneItem;
		
		std::vector<wxWindow*> _windowsEnableItems;
		std::vector<wxWindow*> _windowsEnableOneItem;
};

#endif //CONTROL_DATA_LIST_H
