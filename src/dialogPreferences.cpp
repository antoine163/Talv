//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.2
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogPreferences.hpp"
#include "dialogActionPreferences.hpp"
#include "shortcut.hpp"

#include <wx/msgdlg.h>
#include <wx/menu.h>

//TEST
#include <iostream>

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

DialogPreferences::DialogPreferences(ActionManager *actionManager)
: GuiDialogPreferences(nullptr), _actionManager(actionManager)
{	
    //Magnifier 
    _staticTextSetting->SetLabelMarkup("<b>"+_("Setting")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");
	
	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrlAction->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 170);
	
	//Rempli la list.
	for(auto it: *_actionManager->getAction())
	{
		_listCtrlAction->InsertItem(0, ShortcutKey::shortcutKeyToString(it.first));
		_listCtrlAction->SetItem(0, 1, it.second->getName());
		_listCtrlAction->SetItem(0, 2, it.second->getStringPreferences());
	}
}

DialogPreferences::~DialogPreferences()
{
}

bool DialogPreferences::shutdownIsToggle()const
{
	return _toggleBtnTurnOff->GetValue();
}

bool DialogPreferences::showIcon()const
{
	return _checkBoxShowMenu->GetValue();
}

void DialogPreferences::OnButtonClickActDelete(wxCommandEvent&)
{
	wxMessageDialog *dlg = nullptr;
	
	//Création du dialog.
	if(_listItemSelected.size() > 1)
		dlg = new wxMessageDialog(this, _("Do you want really delete this actions ?"), _("Delete actions"), wxYES_NO|wxCENTRE);
	else
		dlg = new wxMessageDialog(this, _("Do you want really delete this action ?"), _("Delete action"), wxYES_NO|wxCENTRE);
    
    //Affichage du dialog
    if(dlg->ShowModal() == wxID_YES)
	{
		//Supprimer tous les items sélectionnés
		for(size_t i = 0; i<_listItemSelected.size(); i++)
		{
			//On l'ajoute à la liste des raccourcis/actions a supprimer.
			_shortcutKeyActDelete.push_back(ShortcutKey::stringToShortcutKey(_listItemSelected[i].GetText()));
			//On cherche l'id de l'item.
			long idItem = _listCtrlAction->FindItem(-1, _listItemSelected[i].GetText());
			//Et on le supprime.
			_listCtrlAction->DeleteItem(idItem);
		}
		_listItemSelected.clear();
		
		//On désactive les boutons Prefernce et delete
		_buttonActPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
		_buttonActDelete->Enable(false);
		_menuItemListDelete->Enable(false);
	}
	
    dlg->Destroy();
    delete dlg;
}

void DialogPreferences::OnButtonClickActPreferences(wxCommandEvent&)
{
	//Récupération du raccourci.
	ShortcutKey tmpShortcut = ShortcutKey::stringToShortcutKey(_listItemSelected[0].GetText());
	//Récupération de l'action.
	Action const* tmpAct = _actionManager->getAction(tmpShortcut);
	
	DialogActionPreferences *dlg = new DialogActionPreferences(this, tmpShortcut, *tmpAct);
	
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	
	dlg->Destroy();
	delete dlg;
}

void DialogPreferences::OnButtonClickActAdd(wxCommandEvent&)
{
	DialogActionPreferences *dlg = new DialogActionPreferences(this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	
	dlg->Destroy();
	delete dlg;
}

void DialogPreferences::OnButtonClickOK(wxCommandEvent& event)
{	
	event.Skip();
}

void DialogPreferences::OnButtonClickApply(wxCommandEvent& event)
{	
	event.Skip();
}

void DialogPreferences::OnListItemDeselectedAction(wxListEvent& event)
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
		_buttonActDelete->Enable(false);
		_menuItemListDelete->Enable(false);
	}
		
	//On désactive le bouton Préférence soft si il y a un seul item de sélectionner.
	if(_listItemSelected.size() != 1)
	{
		_buttonActPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
	else
	{
		_buttonActPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
}

void DialogPreferences::OnListItemSelectedAction(wxListEvent& event)
{
	_listItemSelected.push_back(event.GetItem());
	
	//activation du bouton delete
	_buttonActDelete->Enable();
	_menuItemListDelete->Enable();
	
	//on active le bouton préférence seulement si il y a qu'un item de sélectionner.
	if(_listItemSelected.size() == 1)
	{
		_buttonActPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
	else
	{
		_buttonActPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
}
		
