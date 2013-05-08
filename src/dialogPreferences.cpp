//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.2
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogPreferences.hpp"
#include "dialogActionPreferences.hpp"
#include "shortcut.hpp"
#include "resource.hpp"

#include <wx/fileconf.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>

//TEST
#include <iostream>

// *********************************************************************
// Class PanelList
// *********************************************************************

PanelList::PanelList(wxWindow* parent, wxString name)
: GuiPanelList(parent), _name(name)
{
}

PanelList::~PanelList()
{
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

// *********************************************************************
// Class PanelListActions
// *********************************************************************

PanelListActions::PanelListActions(wxWindow* parent)
: PanelList(parent, _("action"))
{
	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrl->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrl->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 120);
	_listCtrl->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 255);
	
	//Rempli la liste.
	auto actions = ActionManager::getInstance()->getActions();
	for(auto it: *actions)
	{
		//Récupération du raccourci
		wxString shortcut = ShortcutKey::shortcutKeyToString(it.first);
		
		//Préparation d'un wxArrayString pour l'ajout d'un item
		wxArrayString tmpItem;
		tmpItem.Add(shortcut);
		tmpItem.Add(it.second->getName());
		tmpItem.Add(it.second->getStringPreferences());
		
		//Ajout de l'item dans la liste
		addItem(tmpItem, false);
		
		//On ajout la nouvelle action au _listShortcutAction.
		_listShortcutAction[shortcut] = Action::newAction(it.second);
	}
}

PanelListActions::~PanelListActions()
{
	//Suppression des actions
	for(auto it: _listShortcutAction)
		delete it.second;
}

void PanelListActions::applayAndSave(wxFileConfig & fileConfig)
{
	//Récupération de l'instance de ActionManager
	ActionManager* actionManager = ActionManager::getInstance();
	
	//On commence par supprimer tout les raccourcis
	actionManager->removeAll();
	//Et on ajoute les raccourcis.
	for(auto &it: _listShortcutAction)
		actionManager->add(ShortcutKey::stringToShortcutKey(it.first), Action::newAction(it.second));
		
	//Sauvegarde des actions.
	ActionManager::getInstance()->save(fileConfig);
}

void PanelListActions::OnDeleteItem(wxString const& item)
{
	//Suppression de l'action.
	delete _listShortcutAction[item];
	_listShortcutAction.erase(item);
}

wxArrayString PanelListActions::OnPreferencesItem(wxString const& item)
{
	//wxArrayString de retours.
	wxArrayString newItem;
	
	//Récupération de l'action.
	Action const* tmpAct = _listShortcutAction[item];
	
	DialogActionPreferences dlg(this, item, tmpAct);
	while(1)
	{
		//Montre le dialogue.
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			wxString tmpNewShortcut = dlg.getShortcut();
			
			//Si le raccourci a été modifier.
			if(item != tmpNewShortcut)
			{
				//Vérifie si le raccourci n'est pas déjà existent.
				if(_listShortcutAction.count(tmpNewShortcut) > 0)
				{
					wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
					dlg.ShowModal();
					
					continue;
				}
			}
			
			//Libère la mémoire de l'ancienne action.
			delete _listShortcutAction[item];
			_listShortcutAction.erase(item);
			
			//Nouvelle action.
			Action* tmpAct = Action::newAction(dlg.getAction());
			_listShortcutAction[tmpNewShortcut] = tmpAct;
			
			//Mise à jour de l'item.
			newItem.Add(tmpNewShortcut);
			newItem.Add(tmpAct->getName());
			newItem.Add(tmpAct->getStringPreferences());
		}
		break;
	}
	
	return newItem;
}

wxArrayString PanelListActions::OnAddItem()
{
	//wxArrayString de retours.
	wxArrayString newItem;
	
	DialogActionPreferences dlg(this);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			wxString tmpNewShortcut = dlg.getShortcut();
			
			//vérifie si le raccourci n'est pas déjà existent.
			if(_listShortcutAction.count(tmpNewShortcut) > 0)
			{
				wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				dlg.ShowModal();
				
				continue;
			}
			
			//Nouvelle action
			Action* tmpAct = Action::newAction(dlg.getAction());
			_listShortcutAction[tmpNewShortcut] = tmpAct;
			
			//Un nouveau item
			newItem.Add(tmpNewShortcut);
			newItem.Add(tmpAct->getName());
			newItem.Add(tmpAct->getStringPreferences());
		}
		break;
	}
	
	return newItem;
}

// *********************************************************************
// Class PanelListLists
// *********************************************************************

//PanelListLists::PanelListLists(wxWindow* parent)
//: PanelList(parent)
//{
	////_listCtrlAction->EnableAlternateRowColours();
	//_listCtrl->AppendColumn(_("Name"), wxLIST_FORMAT_LEFT, 158);
	//_listCtrl->AppendColumn(_("Language source"), wxLIST_FORMAT_LEFT, 158);
	//_listCtrl->AppendColumn(_("Language of translation"), wxLIST_FORMAT_LEFT, 158);
	
	////Rempli la liste.
	////auto actions = listManager::getInstance()->getActions();
	////for(auto it: *actions)
	////{
	////}
//}

//PanelListLists::~PanelListLists()
//{
//}

//void PanelListLists::applayAndSave(wxFileConfig & fileConfig)
//{
//}

//void PanelListLists::OnButtonClickDelete(wxCommandEvent&)
//{
//}

//void PanelListLists::OnButtonClickPreferences(wxCommandEvent&)
//{
//}

//void PanelListLists::OnButtonClickAdd(wxCommandEvent&)
//{
//}

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

DialogPreferences::DialogPreferences()
: GuiDialogPreferences(nullptr)
{	
    //Magnifier 
    _staticTextGeneral->SetLabelMarkup("<b>"+_("General :")+"</b>");
    _staticTextVolumeTts->SetLabelMarkup("<b>"+_("Volume for text to speech (Say a text) :")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application :")+"</b>");
	
	//Initialise les valeurs
	_checkBoxShowMenu->SetValue(Resource::getInstance()->getShowMenu());
	_checkBoxPowerOn->SetValue(Resource::getInstance()->getPowerOn());
	_sliderTts->SetValue(Resource::getInstance()->getTtsVolume()*100);
	
	//Ajout du panel Action
	_PanelListActions = new PanelListActions(_notebook);
	_notebook->AddPage(_PanelListActions, _("Actions"), false);
	
	//Ajout du panel List
	//_PanelListLists = new PanelListLists(_notebook);
	//_notebook->AddPage(_PanelListLists, _("Lists"), false);
}

DialogPreferences::~DialogPreferences()
{
}

bool DialogPreferences::shutdownIsToggle()const
{
	return _toggleBtnTurnOff->GetValue();
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
	//On ouvre le fichier de config.
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	fileConfig.DeleteAll();
	
	//Affectation des valeurs dans les ressources.
	Resource::getInstance()->setShowMenu(_checkBoxShowMenu->GetValue());
	Resource::getInstance()->setPowerOn(_checkBoxPowerOn->GetValue());
	Resource::getInstance()->setTtsVolume(_sliderTts->GetValue()/100.);
	
	//On sauvegarde les ressources.
	Resource::getInstance()->save(fileConfig);
	
	//On sauvegarde EN PREMIER les listes
	_PanelListActions->applayAndSave(fileConfig);
	
	//On sauvegarde les EN DEUXIÈME actions
	//_PanelListActions->applayAndSave(fileConfig);
}
		
