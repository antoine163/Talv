//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.8
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogPreferences.hpp"
#include "dialogActionPreferences.hpp"
#include "shortcut.hpp"

#include <wx/fileconf.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>

//TEST
#include <iostream>

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

DialogPreferences::DialogPreferences()
: GuiDialogPreferences(nullptr)
{	
    //Magnifier 
    _staticTextSetting->SetLabelMarkup("<b>"+_("Setting")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");
	
	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrlAction->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 170);
	
	
	//Rempli les lists.
	auto actions = ActionManager::getInstance()->getActions();
	for(auto it: *actions)
		addListShortcutAction(it.first, it.second, -1);
}

DialogPreferences::~DialogPreferences()
{
	//Suppression des actions
	for(auto it: _listShortcutAction)
		delete it.second;
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
		while(!_listItemSelected.empty())
		{	
			//On le supprime de la liste des raccourcis/actions.
			deleteListShortcutAction(ShortcutKey::stringToShortcutKey(_listItemSelected.back().GetText()));
		}
	}
	
    dlg->Destroy();
}

void DialogPreferences::OnButtonClickActPreferences(wxCommandEvent&)
{
	//Récupération du raccourci.
	ShortcutKey tmpShortcut = ShortcutKey::stringToShortcutKey(_listItemSelected[0].GetText());
	//Récupération de l'action.
	Action const* tmpAct = _listShortcutAction[tmpShortcut];
	
	DialogActionPreferences dlg(this, tmpShortcut, tmpAct);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			ShortcutKey tmpNewShortcut = dlg.getShortcutKey();
			
			//Si le raccourci a été modifier.
			if(tmpShortcut != tmpNewShortcut)
			{
				//vérifie si le raccourci n'est pas déjà existent.
				if(existListShortcutAction(tmpNewShortcut))
				{
					wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
					dlg.ShowModal();
					
					continue;
				}
			}
			
			//On supprime l'ancien raccourci.
			long n = deleteListShortcutAction(tmpShortcut);
			//Et on ajoute le nouveau
			addListShortcutAction(tmpNewShortcut, dlg.getAction(), n);
		}
		break;
	}
}

void DialogPreferences::OnButtonClickActAdd(wxCommandEvent&)
{
	DialogActionPreferences dlg(this);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			ShortcutKey tmpNewShortcut = dlg.getShortcutKey();
			
			//vérifie si le raccourci n'est pas déjà existent.
			if(existListShortcutAction(tmpNewShortcut))
			{
				wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				dlg.ShowModal();
				
				continue;
			}
			
			//On ajoute le nouveau raccourci
			addListShortcutAction(tmpNewShortcut, dlg.getAction(), _listCtrlAction->GetItemCount());
		}
		break;
	}
}

void DialogPreferences::OnButtonClickOK(wxCommandEvent& event)
{	
	applayAndSave();
	event.Skip();
}

void DialogPreferences::OnButtonClickApply(wxCommandEvent& event)
{
	applayAndSave();
	event.Skip();
}

void DialogPreferences::applayAndSave()
{
	//Récupération de l'instance de ActionManager
	ActionManager* actionManager = ActionManager::getInstance();
	
	//On commence par supprimer tout les raccourcis
	actionManager->removeAll();
	//Et on ajoute les raccourcis.
	for(auto &it: _listShortcutAction)
		actionManager->add(it.first, Action::newAction(it.second));	
	
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	fileConfig.DeleteAll();
	
	//Ajout du menu dans le fichier de config
	fileConfig.Write("show_menu", _checkBoxShowMenu->GetValue());
	
	//sauvegarde des action
	ActionManager::getInstance()->save(fileConfig);
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

bool DialogPreferences::addListShortcutAction(ShortcutKey const& shortcut, Action const* act, long item)
{
	//Si le raccourci existe déjà.
	if(_listShortcutAction.count(shortcut) > 0)
		return false;
		
	//Sinon on l'ajoute.
	long tmpItem = -1;
	
	//Désélectionne tout les items
	for(;;)
	{
		tmpItem = _listCtrlAction->GetNextItem(tmpItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(tmpItem == -1)
			break;
			
		_listCtrlAction->SetItemState(tmpItem, 0, wxLIST_STATE_SELECTED);
	}
	
	
	//listCtrl
	tmpItem = 0;
	if(item != -1)
		tmpItem = item;
		
	_listCtrlAction->InsertItem(tmpItem, ShortcutKey::shortcutKeyToString(shortcut));
	_listCtrlAction->SetItem(tmpItem, 1, act->getName());
	_listCtrlAction->SetItem(tmpItem, 2, act->getStringPreferences());
	_listCtrlAction->EnsureVisible(tmpItem);
	if(item != -1)
		_listCtrlAction->SetItemState(tmpItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	
	//listShortcutAction
	_listShortcutAction[shortcut] = Action::newAction(act);
	
	return false;
}

long DialogPreferences::deleteListShortcutAction(ShortcutKey const& shortcut)
{
	//Si le raccourci existe.
	if(_listShortcutAction.count(shortcut) > 0)
	{
		//On cherche l'id de l'item.
		long idItem = _listCtrlAction->FindItem(-1, ShortcutKey::shortcutKeyToString(shortcut));
		//On le désélectionne
		_listCtrlAction->SetItemState(idItem, 0, wxLIST_STATE_SELECTED);
		//Et on le supprime.
		_listCtrlAction->DeleteItem(idItem);

		//On le supprime
		delete _listShortcutAction[shortcut];
		_listShortcutAction.erase(shortcut);
		
		return idItem;
	}
	
	return -1;
}

bool DialogPreferences::existListShortcutAction(ShortcutKey const& shortcut)
{
	//Si le raccourci existe.
	if(_listShortcutAction.count(shortcut) > 0)
		return true;
	
	return false;
}
		
