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

#ifndef CTRL_DATA_LIST_H
#define CTRL_DATA_LIST_H

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
// Class CtrlDataList
// *****************************************************************************

class CtrlDataList : public wxDataViewListCtrl
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlDataList(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~CtrlDataList();

		void addWindowEnable(wxWindow* Window, Enable_e eanble);
		wxMenuItem* addMenuItem(	wxWindowID id,
									wxString const& label=wxEmptyString,
									Enable_e eanble = ENABLE_ANYTIME);
		void addMenuItemSeparator();
		
		void updateEnableElements();

	private:
		void onItemContextMenu(wxDataViewEvent& event);
		void onSelectionChanger(wxDataViewEvent& event);
		
		wxMenu* _menu;
		
		std::vector<wxMenuItem*> _menuItemsEnableItems;
		std::vector<wxMenuItem*> _menuItemsEnableOneItem;
		
		std::vector<wxWindow*> _windowsEnableItems;
		std::vector<wxWindow*> _windowsEnableOneItem;
};

#endif //CTRL_DATA_LIST_H
