//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "managerAction.hpp"
#include <dialogActionPreferences.hpp>
#include <wx/msgdlg.h>

//TEST
#include <iostream>

// *********************************************************************
// Class PanelEditActions
// *********************************************************************

PanelEditActions::PanelEditActions(wxWindow* parent, ManagerAction* manager)
: PanelDataList(parent, _("action")), _managerAction(manager)
{	
	//Pansage en mode édite de ManagerAction
	_managerAction->edit(true);
	_managerAction->enableShortcuts(false);
	
	_listCtrl->AppendTextColumn(_("Shortcut"), wxDATAVIEW_CELL_INERT, 100, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_listCtrl->AppendTextColumn(_("Action"), wxDATAVIEW_CELL_INERT, 120, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_listCtrl->AppendTextColumn(_("Preferences"), wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
}

PanelEditActions::~PanelEditActions()
{
	//Pansage en mode normal de ManagerAction
	_managerAction->edit(false);
	_managerAction->enableShortcuts(true);
}

void PanelEditActions::Update()
{
	//Vide la liste
	clear();
	
	//Rempli la liste.
	for(auto it: _managerAction->getData())
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
	}
}

//! \todo finir d'implémenter avec les listes.
bool PanelEditActions::OnDeleteItem(wxString const& item)
{	
	//Récupération l'action à supprimer.
	Action* action = _managerAction->getValue(ShortcutKey::stringToShortcutKey(item));
	
	//Récupération du nom de la liste utiliser par cette action.
	wxString listUsed = action->getListNameUsed();
	
	//Suppression de l'action.
	_managerAction->remove(ShortcutKey::stringToShortcutKey(item));
	
	//Si une liste est utiliser par cette Action ?
	if(!listUsed.IsEmpty())
	{		
		//Aucune actions utilise cette liste ?
		if(!_managerAction->actionUseList(listUsed))
		{
			//Poser la question si on dois supprimés la liste.
			wxMessageDialog dlg(this, wxString::Format(_("The list %s isn't used. You want delete the list?"), listUsed), _("Delete list"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
			if(dlg.ShowModal() == wxID_YES)
			{
				//Suppression de la liste.
				//ListManager::getInstance()->getValue(listUsed)->removeFile();
				//ListManager::getInstance()->remove(listUsed);
			}
		}
	}
	
	return true;
}

wxArrayString PanelEditActions::OnPreferencesItem(wxString const& item)
{
	//wxArrayString de retours.
	wxArrayString newItem;
	
	//Récupération du vieux raccourci.
	ShortcutKey oldShortcutKey = ShortcutKey::stringToShortcutKey(item);
	
	//Récupération de l'action.
	Action* oldAct = _managerAction->getValue(oldShortcutKey);
	
	DialogActionPreferences dlg(this, item, oldAct);
	while(1)
	{
		//Montre le dialogue.
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le nouveau raccourci sélectionner.
			ShortcutKey newShortcutKey = ShortcutKey::stringToShortcutKey(dlg.getShortcut());
			
			//Si le raccourci a été modifier.
			if(oldShortcutKey != newShortcutKey)
			{				
				//Vérifie si le raccourci n'est pas déjà existent.
				if(_managerAction->exist(newShortcutKey))
				{
					wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
					dlg.ShowModal();
					
					continue;
				}
			}
			
			//On récupère la nouvelle action.
			Action* newAct = Action::newAction(dlg.getAction());
			
			//Libère la mémoire de l'ancienne action.
			_managerAction->remove(oldShortcutKey);
			
			//Nouvelle action.
			_managerAction->add(newShortcutKey, newAct);
			
			//Mise à jour de l'item.
			newItem.Add(ShortcutKey::shortcutKeyToString(newShortcutKey));
			newItem.Add(newAct->getName());
			newItem.Add(newAct->getStringPreferences());
		}
		break;
	}
	
	return newItem;
}

wxArrayString PanelEditActions::OnAddItem()
{
	//wxArrayString de return.
	wxArrayString newItem;
	
	DialogActionPreferences dlg(this);
	while(1)
	{
		//Montre le dialogue
		if(dlg.ShowModal() == wxID_OK)
		{
			//Récupère le nouveau raccourci sélectionner.
			ShortcutKey shortcutKey = ShortcutKey::stringToShortcutKey(dlg.getShortcut());
			
			//Vérifie si le raccourci n'est pas déjà existent.
			if(_managerAction->exist(shortcutKey))
			{
				wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				dlg.ShowModal();
				
				continue;
			}
			
			//Nouvelle action
			Action* newAct = Action::newAction(dlg.getAction());
			_managerAction->add(shortcutKey, newAct);
			
			//Un nouveau item
			newItem.Add(ShortcutKey::shortcutKeyToString(shortcutKey));
			newItem.Add(newAct->getName());
			newItem.Add(newAct->getStringPreferences());
		}
		break;
	}
	
	return newItem;
}

// *********************************************************************
// Class ManagerAction
// *********************************************************************

ManagerAction::ManagerAction()
: EditableByPanel(_("Actions")), _shortcut(this)
{
}

ManagerAction::~ManagerAction()
{
	removeAll();
}

bool ManagerAction::add(ShortcutKey const &shortcut, Action* act)
{
	//Ajout à la liste des actions.
	if(!ManagerMap<ShortcutKey, Action>::add(shortcut, act))
		return false;
	
	//Et on l'ajouter à la liste des raccourcis si on n'est pas en mode édite.
	if(!isEdit())
	{
		int id = _shortcut.creat(shortcut);
		Bind(EVT_SHORTCUT, &ManagerAction::OnShortcut, this, id);
	}
	
	return true;
}

bool ManagerAction::remove(ShortcutKey const& shortcut)
{
	if(ManagerMap<ShortcutKey, Action>::remove(shortcut))
	{
		//Suppression du accourcie si on n'est pas en mode édite.
		if(!isEdit())
			_shortcut.remove(shortcut);
			
		return true;
	}
	
	return false;
}

void ManagerAction::removeAll()
{
	//Désinstalle les raccourcis si on n'est pas en mode édite.
	if(!isEdit())
		_shortcut.removeAll();
		
	//Suppression des actions.
	ManagerMap<ShortcutKey, Action>::removeAll();
}

void ManagerAction::load(wxFileConfig& fileConfig)
{
	wxString stringShortcut;
	long lIndex;
	
	//Avent de charger quoi que se soi on supprime tout les raccourcis/actions
	removeAll();
	
	//On positionne le path
	fileConfig.SetPath("/ManagerAction");
	
	//On récupère le premier raccourci
	if(!fileConfig.GetFirstGroup(stringShortcut, lIndex))
	{
		//On positionne le path a la racine.
		fileConfig.SetPath("/");
		return;
	}
		
	do
	{
		//On positionne le path
		fileConfig.SetPath(stringShortcut);
		
		//Récupérer le type de l'action.
		wxString actTypeName;
		fileConfig.Read("ActTypeName", &actTypeName);
		
		//Création d'une action a parte de son nom.
		Action* tmpAct = Action::newAction(actTypeName);
		
		//Si la création de l'action a réussie, alor on l'ajoute.
		if(tmpAct)
		{
			//Chargement des préférence de l'action à partir du fichier de configuration.
			tmpAct->load(fileConfig);
			//Ajout de l'action.
			add(ShortcutKey::stringToShortcutKey(stringShortcut), tmpAct);
		}
		
		//On positionne le path
		fileConfig.SetPath("../");
		
	}//Puis tous les autres
	while(fileConfig.GetNextGroup(stringShortcut, lIndex));
	
	//On positionne le path a la racine.
	fileConfig.SetPath("/");
}

void ManagerAction::save(wxFileConfig& fileConfig)const
{
	for(auto &it: getData())
	{
		//Obtenir la version string du raccourci.
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		//Crée un groupe pour ce raccourci.
		fileConfig.SetPath("/ManagerAction/"+stringShortcut);
		
		//Sauvegarde de l'action
		it.second->save(fileConfig);
	}
}

void ManagerAction::enableShortcuts(bool val)
{
	_shortcut.enable(val);
}

bool ManagerAction::actionUseList(wxString const& listName)
{
	for(auto it: getData())
	{
		if(it.second->getListNameUsed() == listName)
			return true;
	}
	
	return false;
}

void ManagerAction::apply()
{
	ManagerMap<ShortcutKey, Action>::apply();

	//Suppression de tout les raccourcis.
	_shortcut.removeAll();

	//Active les raccourcis auprès de l'os.
	for(auto it : getData())
	{
		int id = _shortcut.creat(it.first);
		Bind(EVT_SHORTCUT, &ManagerAction::OnShortcut, this, id);
	}
}

wxPanel* ManagerAction::newEditPanel(wxWindow *parent)
{
	return new PanelEditActions(parent, this);
}

bool ManagerAction::panelCheck()const
{
	return true;
}

bool ManagerAction::panelApply()
{
	apply();
	return true;
}

bool ManagerAction::panelSave(wxFileConfig &fileConfig)const
{
	save(fileConfig);
	return true;
}

Action* ManagerAction::copyNewDatas(Action const* inc)
{
	return Action::newAction(inc);
}

void ManagerAction::OnShortcut(ShortcutEvent& event)
{
	getData().at(event.getShortcutKey())->execute();
}
