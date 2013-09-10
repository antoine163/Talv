//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.13
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "actionManager.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class ActionManager
// *********************************************************************

ActionManager::ActionManager() : _shortcut(this)
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
		//Chargement des préférence de l'action à partir du fichier de configuration.
		tmpAct->load(fileConfig);
		//Ajout de l'action.
		add(ShortcutKey::stringToShortcutKey(stringShortcut), tmpAct);
		
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
