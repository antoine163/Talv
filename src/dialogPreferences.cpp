//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
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

PanelList::PanelList(wxWindow* parent)
: GuiPanelList(parent)
{
}

PanelList::~PanelList()
{
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
: PanelList(parent)
{
	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrl->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrl->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 120);
	_listCtrl->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 255);
	
	//Rempli la liste.
	auto actions = ActionManager::getInstance()->getActions();
	for(auto it: *actions)
		addListShortcutAction(ShortcutKey::shortcutKeyToString(it.first), it.second, -1);
}

PanelListActions::~PanelListActions()
{
	//Suppression des actions
	for(auto it: _listShortcutAction)
		delete it.second;
}

void PanelListActions::applayAndSave(wxFileConfig & fileConfig)
{
}

void PanelListActions::OnButtonClickDelete(wxCommandEvent&)
{
	wxMessageDialog *dlg = nullptr;
	
	//Création du dialog.
	if(_listItemSelected.size() > 1)
		dlg = new wxMessageDialog(this, _("Do you want really delete this actions ?"), _("Delete actions"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
	else
		dlg = new wxMessageDialog(this, _("Do you want really delete this action ?"), _("Delete action"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
    
    //Affichage du dialog
    if(dlg->ShowModal() == wxID_YES)
	{
		//Supprimer tous les items sélectionnés
		while(!_listItemSelected.empty())
		{	
			//On le supprime de la liste.
			deleteListShortcutAction(_listItemSelected.back().GetText());
			_listItemSelected.pop_back();
		}
	}
	
    dlg->Destroy();
}

void PanelListActions::OnButtonClickPreferences(wxCommandEvent&)
{
	//Récupération du raccourci.
	wxString tmpShortcut = _listItemSelected[0].GetText();
	//Récupération de l'action.
	Action const* tmpAct = _listShortcutAction[tmpShortcut];
	
	DialogActionPreferences dlg(this, tmpShortcut, tmpAct);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			wxString tmpNewShortcut = dlg.getShortcut();
			
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

void PanelListActions::OnButtonClickAdd(wxCommandEvent&)
{
	DialogActionPreferences dlg(this);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le raccourci sélectionner.
			wxString tmpNewShortcut = dlg.getShortcut();
			
			//vérifie si le raccourci n'est pas déjà existent.
			if(existListShortcutAction(tmpNewShortcut))
			{
				wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				dlg.ShowModal();
				
				continue;
			}
			
			//On ajoute le nouveau raccourci
			addListShortcutAction(tmpNewShortcut, dlg.getAction(), _listCtrl->GetItemCount());
		}
		break;
	}
}

bool PanelListActions::addListShortcutAction(wxString const& shortcut, Action const* act, long item)
{
	//Si le raccourci existe déjà.
	if(_listShortcutAction.count(shortcut) > 0)
		return false;
		
	//Sinon on l'ajoute.
	long tmpItem = -1;
	
	//Désélectionne tout les items
	for(;;)
	{
		tmpItem = _listCtrl->GetNextItem(tmpItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(tmpItem == -1)
			break;
			
		_listCtrl->SetItemState(tmpItem, 0, wxLIST_STATE_SELECTED);
	}
	
	//L'item doit être ajouter au début de la liste ?
	if(item == -1)
		tmpItem = 0;
	else
		tmpItem = item;
		
	//Ajout du texte de l'item
	_listCtrl->InsertItem(tmpItem, shortcut);
	_listCtrl->SetItem(tmpItem, 1, act->getName());
	_listCtrl->SetItem(tmpItem, 2, act->getStringPreferences());
	_listCtrl->EnsureVisible(tmpItem);
	
	//On sélectionne l'items si on ne la pas ajouter au début de la liste
	if(item != -1)
		_listCtrl->SetItemState(tmpItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	
	//On ajout la nouvelle action au _listShortcutAction (une copie de act)
	_listShortcutAction[shortcut] = Action::newAction(act);
		
	return true;
}

long PanelListActions::deleteListShortcutAction(wxString const& shortcut)
{		
	//Si le raccourci existe.
	if(existListShortcutAction(shortcut))
	{
		//On cherche l'id de l'item.
		long idItem = _listCtrl->FindItem(-1, shortcut);
		//On le désélectionne
		//_listCtrl->SetItemState(idItem, 0, wxLIST_STATE_SELECTED);
		//Et on le supprime.
		_listCtrl->DeleteItem(idItem);

		//On le supprime
		delete _listShortcutAction[shortcut];
		_listShortcutAction.erase(shortcut);
		
		return idItem;
	}
	
	return -1;
}

bool PanelListActions::existListShortcutAction(wxString const& shortcut)
{
	//Si le raccourci existe.
	if(_listShortcutAction.count(shortcut) > 0)
		return true;
	
	return false;
}

// *********************************************************************
// Class PanelListLists
// *********************************************************************

PanelListLists::PanelListLists(wxWindow* parent)
: PanelList(parent)
{
	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrl->AppendColumn(_("Name"), wxLIST_FORMAT_LEFT, 158);
	_listCtrl->AppendColumn(_("Language source"), wxLIST_FORMAT_LEFT, 158);
	_listCtrl->AppendColumn(_("Language of translation"), wxLIST_FORMAT_LEFT, 158);
}

PanelListLists::~PanelListLists()
{
}

void PanelListLists::applayAndSave(wxFileConfig & fileConfig)
{
}

void PanelListLists::OnButtonClickDelete(wxCommandEvent&)
{
}

void PanelListLists::OnButtonClickPreferences(wxCommandEvent&)
{
}

void PanelListLists::OnButtonClickAdd(wxCommandEvent&)
{
}

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
	_PanelListLists = new PanelListLists(_notebook);
	_notebook->AddPage(_PanelListLists, _("Lists"), false);
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
	////Récupération de l'instance de ActionManager
	//ActionManager* actionManager = ActionManager::getInstance();
	
	////On commence par supprimer tout les raccourcis
	//actionManager->removeAll();
	////Et on ajoute les raccourcis.
	//for(auto &it: _listShortcutAction)
		//actionManager->add(it.first, Action::newAction(it.second));
	
	////Affectation des valeurs dans les ressources.
	//Resource::getInstance()->setShowMenu(_checkBoxShowMenu->GetValue());
	//Resource::getInstance()->setPowerOn(_checkBoxPowerOn->GetValue());
	//Resource::getInstance()->setTtsVolume(_sliderTts->GetValue()/100.);
	
	////On ouvre le fichier de config.
	//wxFileConfig fileConfig(	PROJECT_NAME,
								//wxEmptyString,
								//wxGetUserHome()+"/."+PROJECT_NAME);
	//fileConfig.DeleteAll();
	
	////On sauvegarde les ressources.
	//Resource::getInstance()->save(fileConfig);
	
	////Sauvegarde des actions.
	//ActionManager::getInstance()->save(fileConfig);
}
		
