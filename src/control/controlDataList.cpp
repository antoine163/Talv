//! \file **************************************************************
//! \brief Source panel widgets avec une liste des boutons et un menu.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 26.09.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "panelDataList.hpp"

#include <wx/msgdlg.h>

// *********************************************************************
// Class PanelDataList
// *********************************************************************

PanelDataList::PanelDataList(wxWindow* parent, wxString name)
: GuiPanelDataList(parent), _name(name)
{	
	//Construction du menu
	_menu = new wxMenu();
		
	_menuItemListAdd = new wxMenuItem(_menu,  wxID_ADD);
	_menu->Append(_menuItemListAdd);
	_menuItemListPreferences = new wxMenuItem(_menu, wxID_PREFERENCES);
	_menu->Append(_menuItemListPreferences);
	_menuItemListDelete = new wxMenuItem(_menu, wxID_DELETE);
	_menu->Append(_menuItemListDelete);
	
	_menuItemListPreferences->Enable(false);
	_menuItemListDelete->Enable(false);
	
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickAdd, this, wxID_ADD);
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickPreferences, this, wxID_PREFERENCES);
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickDelete, this, wxID_DELETE);
	
	_listCtrl->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &PanelDataList::OnListSelectionChanged, this);
	_listCtrl->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &PanelDataList::OnListItemContextMenu, this);
}

PanelDataList::~PanelDataList()
{
	//Destruction du menu
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickAdd, this, wxID_ADD);
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickPreferences, this, wxID_PREFERENCES);
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelDataList::OnButtonClickDelete, this, wxID_DELETE);
	
	_listCtrl->Unbind(wxEVT_DATAVIEW_SELECTION_CHANGED, &PanelDataList::OnListSelectionChanged, this);
	_listCtrl->Unbind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &PanelDataList::OnListItemContextMenu, this);
	
	delete _menu;
}

void PanelDataList::addItem(wxArrayString const& item, bool select)
{
	//Vérifie si l'item est vide.
	if(item.GetCount() == 0)
		return;
		
	//Ajout l'item.
	wxVector<wxVariant> data;
	for(size_t i = 0; i < item.GetCount(); i++)
		data.push_back(wxVariant(item[i]));
		
	_listCtrl->AppendItem(data);
	
	//Désélectionne tout les items
	_listCtrl->UnselectAll();
	
	//On sélectionne l'items au besoins.
	if(select)
	{	
		//Recherche de l'item fraîchement sélectionner.
		for(int i = 0; i < _listCtrl->GetItemCount(); i++)
		{
			//On la trouver ?
			if(_listCtrl->GetTextValue(i, 0) == item[0])
			{
				//On le sélectionne
				_listCtrl->SelectRow(i);
				_listCtrl->EnsureVisible(_listCtrl->RowToItem(i));
				break;
			}
		}
	}
}

void PanelDataList::clear()
{
	_listCtrl->DeleteAllItems();
}

void PanelDataList::OnButtonClickDelete(wxCommandEvent&)
{
	wxMessageDialog *dlg = nullptr;
	
	//Création du dialog.
	if(_listCtrl->GetSelectedItemsCount() > 1)
		dlg = new wxMessageDialog(this, wxString::Format(_("Do you want really delete this %ss ?"), _name), wxString::Format(_("Delete %ss"), _name), wxYES_NO|wxICON_QUESTION|wxCENTRE);
	else
		dlg = new wxMessageDialog(this, wxString::Format(_("Do you want really delete this %s ?"), _name), wxString::Format(_("Delete %s"), _name), wxYES_NO|wxICON_QUESTION|wxCENTRE);
    
    //Affichage du dialog
    if(dlg->ShowModal() == wxID_YES)
	{
		//Supprimer tous les items sélectionnés
		wxDataViewItemArray data;
		_listCtrl->GetSelections(data);
		
		int itemRow = -1;
		for(auto it : data)
		{
			//On récupère la ligne de l'item.
			itemRow = _listCtrl->ItemToRow(it);
			
			//On récupère le texte de la premier colonne de l'item.
			wxString item = _listCtrl->GetTextValue(itemRow, 0);
	
			//On le supprime de la liste.
			_listCtrl->DeleteItem(itemRow);
			OnDeleteItem(item);
		}
	}
	
    dlg->Destroy();
}

void PanelDataList::OnButtonClickPreferences(wxCommandEvent&)
{	
	//On récupère le texte de la premier colonne de l'item sélectionner.
	wxDataViewItem data = _listCtrl->GetSelection();
	int itemRow = _listCtrl->ItemToRow(data);
	wxString item = _listCtrl->GetTextValue(itemRow, 0);
	
	//Préférence de l'item.
	wxArrayString tmpItem = OnPreferencesItem(item);
	
	//Mise à jour de l'item dans la liste.
	for(size_t i = 0; i < tmpItem.GetCount(); i++)
	{
		//_listCtrl->SetItem(idItem, i, tmpItem[i]);
		_listCtrl->SetTextValue(tmpItem[i], itemRow, i);
	}
}

void PanelDataList::OnButtonClickAdd(wxCommandEvent&)
{
	//Ajout d'un nouveau item.
	wxArrayString newItem = OnAddItem();
	
	//newItem n'est pas vide ?
	if(newItem.GetCount() > 0)
	{
		//Désélectionne tout les items
		_listCtrl->UnselectAll();
	
		//Ajout de l'item
		addItem(newItem);
	}
}

void PanelDataList::OnListSelectionChanged(wxDataViewEvent&)
{
	switch(_listCtrl->GetSelectedItemsCount())
	{
		//Rien n'est sélectionner.
		case 0:
			//On désactive les boutons delete.
			_buttonDelete->Enable(false);
			_menuItemListDelete->Enable(false);
			
			//On désactive les boutons Preferences.
			_buttonPreferences->Enable(false);
			_menuItemListPreferences->Enable(false);
		break;
		
		//Un seul item est sélectionner.
		case 1:
			//On active les boutons delete.
			_buttonDelete->Enable();
			_menuItemListDelete->Enable();
			
			//On active les boutons Preferences.
			_buttonPreferences->Enable();
			_menuItemListPreferences->Enable();
		break;
		
		//Plusieurs items son sélectionner.
		default:
			//On active les boutons delete.
			_buttonDelete->Enable();
			_menuItemListDelete->Enable();
			
			//On désactive les boutons Preferences.
			_buttonPreferences->Enable(false);
			_menuItemListPreferences->Enable(false);
		break;
	}
}

void PanelDataList::OnListItemContextMenu(wxDataViewEvent&)
{	
	//Affichage du menu
	_listCtrl->PopupMenu(_menu);
}
		
