//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 26.09.2013
//!
//! ****************************************************************************

//App
#include "control/ctrlDataList.hpp"

// *****************************************************************************
// Class CtrlDataList
// *****************************************************************************

CtrlDataList::CtrlDataList(wxWindow* parent)
: 	wxDataViewListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
	wxDV_ROW_LINES|wxDV_MULTIPLE)
{
	//Construction du menu
	_menu = new wxMenu();
	
	//Bind
	Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &CtrlDataList::onItemContextMenu, this);
	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &CtrlDataList::onSelectionChanger, this);
}

CtrlDataList::~CtrlDataList()
{
	//Unbind
	Unbind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &CtrlDataList::onItemContextMenu, this);
	Unbind(wxEVT_DATAVIEW_SELECTION_CHANGED, &CtrlDataList::onSelectionChanger, this);
	
	//Destruction du menu.
	delete _menu;
}	

void CtrlDataList::addWindowEnable(wxWindow* Window, Enable_e eanble)
{
	switch(eanble)
	{
		case ENABLE_ANYTIME:
		break;
		case  ENABLE_SELECTING_ITEMS:
			_windowsEnableItems.push_back(Window);
		break;
		case ENABLE_SELECTING_ONE_ITEM:
			_windowsEnableOneItem.push_back(Window);
		break;
	}
	
	updateEnableElements();
}

wxMenuItem* CtrlDataList::addMenuItem(	wxWindowID id,
											wxString const& label,
											Enable_e eanble)
{
	wxMenuItem* menuItem = new wxMenuItem(_menu, id, label);
	_menu->Append(menuItem);
	
	switch(eanble)
	{
		case ENABLE_ANYTIME:
		break;
		case  ENABLE_SELECTING_ITEMS:
			_menuItemsEnableItems.push_back(menuItem);
		break;
		case ENABLE_SELECTING_ONE_ITEM:
			_menuItemsEnableOneItem.push_back(menuItem);
		break;
	}
	
	updateEnableElements();
	return menuItem;
}

void CtrlDataList::addMenuItemSeparator()
{
	_menu->AppendSeparator();
}

void CtrlDataList::onItemContextMenu(wxDataViewEvent&)
{
	PopupMenu(_menu);
}

void CtrlDataList::onSelectionChanger(wxDataViewEvent&)
{
	updateEnableElements();
}

void CtrlDataList::updateEnableElements()
{
	//On désactive tous les itères et windows
	for(auto it: _menuItemsEnableOneItem)
		it->Enable(false);
	for(auto it: _windowsEnableOneItem)
		it->Enable(false);
	for(auto it: _menuItemsEnableItems)
		it->Enable(false);
	for(auto it: _windowsEnableItems)
		it->Enable(false);
				
	switch(GetSelectedItemsCount())
	{
		//Rien n'est sélectionner.
		case 0:
		break;
		
		//Un seul item est sélectionner.
		case 1:
			for(auto it: _menuItemsEnableOneItem)
				it->Enable();
			for(auto it: _windowsEnableOneItem)
				it->Enable();
		
		//Plusieurs items son sélectionner.
		default:
			for(auto it: _menuItemsEnableItems)
				it->Enable();
			for(auto it: _windowsEnableItems)
				it->Enable();
		break;
	}
}
