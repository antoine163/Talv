//! \file **************************************************************
//! \brief Source panel widgets avec une liste des boutons et un menu.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 26.09.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "panelList.hpp"

#include <wx/msgdlg.h>

// *********************************************************************
// Class PanelList
// *********************************************************************

PanelList::PanelList(wxWindow* parent, wxString name)
: GuiPanelList(parent), _name(name)
{
	#if wxCHECK_VERSION(2, 9, 5)
		//_listCtrl->EnableAlternateRowColours();
	#endif
	
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
	
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickAdd, this, wxID_ADD);
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickPreferences, this, wxID_PREFERENCES);
	_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickDelete, this, wxID_DELETE);
}

PanelList::~PanelList()
{
	//Destruction du menu
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickAdd, this, wxID_ADD);
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickPreferences, this, wxID_PREFERENCES);
	_menu->Unbind(wxEVT_COMMAND_MENU_SELECTED, &PanelList::OnButtonClickDelete, this, wxID_DELETE);

	delete _menu;
}

void PanelList::addItem(wxArrayString const& item, bool select)
{
	//Vérifie si l'item est vide.
	if(item.GetCount() == 0)
		return;
		
	//Ajout l'item au débute.
	_listCtrl->InsertItem(0, item[0]);
	for(size_t i = 1; i < item.GetCount(); i++)
	{
		_listCtrl->SetItem(0, i, item[i]);
	}
	
	//Rend visible l'item.
	_listCtrl->EnsureVisible(0);
	
	//On sélectionne l'items au besoins.
	if(select)
		_listCtrl->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void PanelList::clear()
{
	_listCtrl->DeleteAllItems();
	_listItemSelected.clear();
	
	//On désactive les boutons
	_buttonDelete->Enable(false);
	_menuItemListDelete->Enable(false);
	_buttonPreferences->Enable(false);
	_menuItemListPreferences->Enable(false);
}

void PanelList::OnButtonClickDelete(wxCommandEvent&)
{
	wxMessageDialog *dlg = nullptr;
	
	//Création du dialog.
	if(_listItemSelected.size() > 1)
		dlg = new wxMessageDialog(this, wxString::Format(_("Do you want really delete this %ss ?"), _name), wxString::Format(_("Delete %ss"), _name), wxYES_NO|wxICON_QUESTION|wxCENTRE);
	else
		dlg = new wxMessageDialog(this, wxString::Format(_("Do you want really delete this %s ?"), _name), wxString::Format(_("Delete %s"), _name), wxYES_NO|wxICON_QUESTION|wxCENTRE);
    
    //Affichage du dialog
    if(dlg->ShowModal() == wxID_YES)
	{
		//Supprimer tous les items sélectionnés
		while(!_listItemSelected.empty())
		{	
			//L'item a supprimer.
			wxString tmpItem = _listItemSelected.back().GetText();
			
			//On cherche l'id de l'item.
			long idItem = _listCtrl->FindItem(-1, tmpItem);
			
			//On le supprime de la liste.
			_listCtrl->DeleteItem(idItem);
			_listItemSelected.pop_back();
			OnDeleteItem(tmpItem);
			
			//On désactive les boutons
			_buttonDelete->Enable(false);
			_menuItemListDelete->Enable(false);
			_buttonPreferences->Enable(false);
			_menuItemListPreferences->Enable(false);
		}
	}
	
    dlg->Destroy();
}

void PanelList::OnButtonClickPreferences(wxCommandEvent&)
{	
	//Préférence de l'item.
	wxArrayString tmpItem = OnPreferencesItem(_listItemSelected[0].GetText());
	
	//Mise à jour de l'item dans la liste.
	long idItem = _listItemSelected[0].GetId();
	for(size_t i = 0; i < tmpItem.GetCount(); i++)
	{
		_listCtrl->SetItem(idItem, i, tmpItem[i]);
	}
}

void PanelList::OnButtonClickAdd(wxCommandEvent&)
{
	//Ajout d'un nouveau item.
	wxArrayString newItem = OnAddItem();
	
	//tmpItem n'est pas vide ?
	if(newItem.GetCount() > 0)
	{
		//Désélectionne tout les items
		long tmpItem = -1;
		for(;;)
		{
			tmpItem = _listCtrl->GetNextItem(tmpItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if(tmpItem == -1)
				break;
				
			_listCtrl->SetItemState(tmpItem, 0, wxLIST_STATE_SELECTED);
		}
	
		//Ajout de l'item
		addItem(newItem);
	}
}

void PanelList::OnListItemRightClick(wxListEvent& event)
{
	//Propagation de l'événement.
	event.Skip();
	
	//Affichage du menu
	_listCtrl->PopupMenu(_menu);
}
		
void PanelList::OnListItemDeselected(wxListEvent& event)
{
	//Recherche et suppression de l'item désélectionner.
	for(size_t i = 0; i<_listItemSelected.size(); i++)
	{
		if(_listItemSelected[i] == event.GetItem())
		{
			_listItemSelected.erase(_listItemSelected.begin()+i);
			break;
		}
	}
	
	//Si rien n'est sélectionner on désactive les boutons delete.
	if(_listItemSelected.size() <= 0)
	{
		_buttonDelete->Enable(false);
		_menuItemListDelete->Enable(false);
	}
		
	//On désactive le bouton Préférence soft si il y a un seul item de sélectionner.
	if(_listItemSelected.size() != 1)
	{
		_buttonPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
	else
	{
		_buttonPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
}

void PanelList::OnListItemSelected(wxListEvent& event)
{
	_listItemSelected.push_back(event.GetItem());
	
	//Activation du bouton delete
	_buttonDelete->Enable();
	_menuItemListDelete->Enable();
	
	//On active le bouton préférence seulement si il y a qu'un item de sélectionner.
	if(_listItemSelected.size() == 1)
	{
		_buttonPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
	else
	{
		_buttonPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
}
