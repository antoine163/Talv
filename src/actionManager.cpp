//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.5
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "actionManager.hpp"

ActionManager::ActionManager() : _shortcut(this)
{
}

ActionManager::~ActionManager()
{
	removeAll();
}

bool ActionManager::add(ShortcutKey const &shortcut, Action* act)
{
	//Si le raccourci existe déjà.
	if(_actions.count(shortcut) > 0)
		return false;
		
	//Sinon on l'ajoute.
	_actions[shortcut] = act;
	
	//Et on l'ajouter à la liste des raccourcis.
	int id = _shortcut.creat(shortcut);
	Bind(EVT_SHORTCUT, &ActionManager::OnShortcut, this, id);
	
	return false;
}

bool ActionManager::remove(ShortcutKey const &shortcut)
{
	//Si le raccourci existe.
	if(_actions.count(shortcut) > 0)
	{
		//On le supprime
		delete _actions[shortcut];
		_actions.erase(shortcut);
		return true;
	}
	
	return false;
}

void ActionManager::removeAll()
{
	//Suppression des actions.
	for(auto &it: _actions)
		delete it.second;
		
	_actions.clear();
}

void ActionManager::load(wxFileConfig & fileConfig)
{
	wxString stringShortcut;
	long lIndex;
	
	//Avent de charger quoi que se soi on supprime tout les raccourcis/actions
	removeAll();
	
	//On récupère le premier raccourci
	if(!fileConfig.GetFirstGroup(stringShortcut, lIndex))
		return;
		
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
}

void ActionManager::sove(wxFileConfig & fileConfig)const
{
	for(auto &it: _actions)
	{
		//Obtenir la version string du raccourci.
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		//Crée un groupe pour ce raccourci.
		fileConfig.SetPath("/"+stringShortcut);
		
		//Sauvegarde de l'action
		it.second->sove(fileConfig);
	}
}

void ActionManager::enable(bool val)
{
	_shortcut.enable(val);
}

std::map<ShortcutKey, Action*> const* ActionManager::getActions()const
{
	return &_actions;
}

Action const* ActionManager::getAction(ShortcutKey const& shortcutKey)const
{
	std::map<ShortcutKey, Action*>::const_iterator it = _actions.find(shortcutKey);
	
	if(it == _actions.end())
		return nullptr;
	
	return it->second;
}

void ActionManager::OnShortcut(ShortcutEvent& event)
{
	_actions[event.getShortcutKey()]->execute();
}
