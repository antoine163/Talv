//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.15
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "actionManager.hpp"

#include <wx/msgdlg.h>

//TEST
#include <iostream>

// *********************************************************************
// Class PanelListActions
// *********************************************************************

PanelListActions::PanelListActions(wxWindow* parent)
: PanelList(parent, _("action"))
{
	_listCtrl->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrl->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 120);
	_listCtrl->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 255);
}

PanelListActions::~PanelListActions()
{
}

void PanelListActions::Update()
{
	std::cout << "PanelListActions::Update" << std::endl;
	////Vide la liste
	//clear();
	
	////Rempli la liste.
	//auto actions = EditActionManager::getInstance()->getData();
	//for(auto it: actions)
	//{
		////Récupération du raccourci
		//wxString shortcut = ShortcutKey::shortcutKeyToString(it.first);
		
		////Préparation d'un wxArrayString pour l'ajout d'un item
		//wxArrayString tmpItem;
		//tmpItem.Add(shortcut);
		//tmpItem.Add(it.second->getName());
		//tmpItem.Add(it.second->getStringPreferences());
		
		////Ajout de l'item dans la liste
		//addItem(tmpItem, false);
	//}
}

bool PanelListActions::OnDeleteItem(wxString const& item)
{
	////Récupération de EditActionManager
	//EditActionManager* editActionManager = EditActionManager::getInstance();
	
	////Récupération l'action à supprimer.
	//Action* action = editActionManager->getValue(ShortcutKey::stringToShortcutKey(item));
	
	////Récupération du nom de la liste utiliser par cette action.
	//wxString listUsed = action->getListNameUsed();
	
	////Suppression de l'action.
	//editActionManager->remove(ShortcutKey::stringToShortcutKey(item));
	
	////Si une liste est utiliser par cette liste.
	//if(!listUsed.IsEmpty())
	//{
		////Récupération des raccourcis/actions utilisent la même liste que l'action à supprimer.
		//std::vector<ShortcutKey> shortcuts = editActionManager->getShortcutUsedList(listUsed);
		
		////Si il n'y a pas d'autre raccourcis.
		//if(shortcuts.size() == 0)
		//{
			////Poser la question si on dois les supprimés la liste.
			//wxMessageDialog dlg(this, wxString::Format(_("The list %s isn't used. You want delete the list?"), listUsed), _("Delete list"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
			//if(dlg.ShowModal() == wxID_YES)
			//{
				////Suppression de la liste.
				//EditListManager::getInstance()->getValue(listUsed)->removeFile();
				//EditListManager::getInstance()->remove(listUsed);
			//}
		//}
	//}
	
	return true;
}

wxArrayString PanelListActions::OnPreferencesItem(wxString const& item)
{
	//wxArrayString de retours.
	wxArrayString newItem;
	
	////Récupération du vieux raccourci.
	//ShortcutKey oldShortcutKey = ShortcutKey::stringToShortcutKey(item);
	
	////Récupération de l'action.
	//Action* oldAct = EditActionManager::getInstance()->getValue(oldShortcutKey);
	
	//DialogActionPreferences dlg(this, item, oldAct);
	//while(1)
	//{
		////Montre le dialogue.
		//if(dlg.ShowModal() == wxID_OK)
		//{
			////Récupère le nouveau raccourci sélectionner.
			//ShortcutKey newShortcutKey = ShortcutKey::stringToShortcutKey(dlg.getShortcut());
			
			////Si le raccourci a été modifier.
			//if(oldShortcutKey != newShortcutKey)
			//{				
				////Vérifie si le raccourci n'est pas déjà existent.
				//if(EditActionManager::getInstance()->exist(newShortcutKey))
				//{
					//wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
					//dlg.ShowModal();
					
					//continue;
				//}
			//}
			
			////On récupère la nouvelle action.
			//Action* newAct = Action::newAction(dlg.getAction());
			
			////Libère la mémoire de l'ancienne action.
			//EditActionManager::getInstance()->remove(oldShortcutKey);
			
			////Nouvelle action.
			//EditActionManager::getInstance()->add(newShortcutKey, newAct);
			
			////Mise à jour de l'item.
			//newItem.Add(ShortcutKey::shortcutKeyToString(newShortcutKey));
			//newItem.Add(newAct->getName());
			//newItem.Add(newAct->getStringPreferences());
		//}
		//break;
	//}
	
	return newItem;
}

wxArrayString PanelListActions::OnAddItem()
{
	//wxArrayString de retour.
	wxArrayString newItem;
	
	//DialogActionPreferences dlg(this);
	//while(1)
	//{
		////Montre le dialogue
		//if(dlg.ShowModal() == wxID_OK)
		//{
			////Récupère le nouveau raccourci sélectionner.
			//ShortcutKey shortcutKey = ShortcutKey::stringToShortcutKey(dlg.getShortcut());
			
			////Vérifie si le raccourci n'est pas déjà existent.
			//if(EditActionManager::getInstance()->exist(shortcutKey))
			//{
				//wxMessageDialog dlg(this, _("The shortcut already exist!"), _("Shortcut exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				//dlg.ShowModal();
				
				//continue;
			//}
			
			////Nouvelle action
			//Action* newAct = Action::newAction(dlg.getAction());
			//EditActionManager::getInstance()->add(shortcutKey, newAct);
			
			////Un nouveau item
			//newItem.Add(ShortcutKey::shortcutKeyToString(shortcutKey));
			//newItem.Add(newAct->getName());
			//newItem.Add(newAct->getStringPreferences());
		//}
		//break;
	//}
	
	return newItem;
}

// *********************************************************************
// Class ActionManager
// *********************************************************************

ActionManager::ActionManager() :
EditableByPanel(_("Actions")), _shortcut(this)
{
}

ActionManager::~ActionManager()
{
	removeAll();
}

bool ActionManager::add(ShortcutKey const &shortcut, Action* act)
{
	//Ajout à la liste des actions.
	if(!ManagerBase<ShortcutKey, Action>::add(shortcut, act))
		return false;
	
	//Et on l'ajouter à la liste des raccourcis.
	int id = _shortcut.creat(shortcut);
	Bind(EVT_SHORTCUT, &ActionManager::OnShortcut, this, id);
	
	return true;
}

bool ActionManager::remove(ShortcutKey const& shortcut)
{
	if(ManagerBase<ShortcutKey, Action>::remove(shortcut))
	{
		//Suppression du accourcie.
		_shortcut.remove(shortcut);
		return true;
	}
	
	return false;
}

void ActionManager::removeAll()
{
	//Désinstalle les raccourcis.
		_shortcut.removeAll();
		
	//Suppression des actions.
	ManagerBase<ShortcutKey, Action>::removeAll();
}

void ActionManager::load(wxFileConfig& fileConfig)
{
	wxString stringShortcut;
	long lIndex;
	
	//Avent de charger quoi que se soi on supprime tout les raccourcis/actions
	removeAll();
	
	//On positionne le path
	fileConfig.SetPath("/ActionManager");
	
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

void ActionManager::save(wxFileConfig& fileConfig)const
{
	for(auto &it: _data)
	{
		//Obtenir la version string du raccourci.
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		//Crée un groupe pour ce raccourci.
		fileConfig.SetPath("/ActionManager/"+stringShortcut);
		
		//Sauvegarde de l'action
		it.second->save(fileConfig);
	}
}

void ActionManager::enableShortcuts(bool val)
{
	_shortcut.enable(val);
}

wxPanel* ActionManager::newEditPanel(wxWindow *parent)
{
	return new PanelListActions(parent);
}

bool ActionManager::check()const
{
	return true;
}

bool ActionManager::apply()
{
	return true;
}

void ActionManager::OnShortcut(ShortcutEvent& event)
{
	_data[event.getShortcutKey()]->execute();
}

// *********************************************************************
// Class EditActionManager
// *********************************************************************

EditActionManager::EditActionManager()
{
}

EditActionManager::~EditActionManager()
{
}

void EditActionManager::init()
{
	auto act = ActionManager::getInstance()->getData();
	
	//Copie de tout les actions.
	for(auto it : act)
		add(it.first, Action::newAction(it.second));
}
	
void EditActionManager::apply()
{
	ActionManager* actionManager = ActionManager::getInstance();
	
	//On supprime tout
	actionManager->removeAll();
	
	//Et on remplie en copient tout les actions.
	for(auto it : _data)
		actionManager->add(it.first, Action::newAction(it.second));
}

std::vector<ShortcutKey> EditActionManager::getShortcutUsedList(wxString const& listName)
{
	std::vector<ShortcutKey> shortcuts;
	
	//Parcoure de tout les raccourcis/actions
	for(auto it: _data)
	{
		if(it.second->getListNameUsed() == listName)
			shortcuts.push_back(it.first);
	}
	
	return shortcuts;
}
