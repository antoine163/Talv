//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.1
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "actionManager.hpp"

// *********************************************************************
// Class ActionManagerBase
// *********************************************************************

ActionManagerBase::ActionManagerBase()
{
}

ActionManagerBase::~ActionManagerBase()
{
	removeAll();
}

bool ActionManagerBase::add(ShortcutKey const &shortcut, Action* act)
{
	//Si le raccourci existe déjà.
	if(_actions.count(shortcut) > 0)
		return false;
		
	//Sinon on l'ajoute.
	_actions[shortcut] = act;
	
	return true;
}

bool ActionManagerBase::remove(ShortcutKey const &shortcut)
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

void ActionManagerBase::removeAll()
{
	//Suppression des actions.	
	_actions.clear();
}

bool ActionManagerBase::exist(ShortcutKey const &shortcut)
{
	//Si le raccourci existe.
	if(_actions.count(shortcut) > 0)
		return true;
	
	return false;
}

std::map<ShortcutKey, Action*> const* ActionManagerBase::getActions()const
{
	return &_actions;
}

Action const* ActionManagerBase::getAction(ShortcutKey const& shortcutKey)const
{
	std::map<ShortcutKey, Action*>::const_iterator it = _actions.find(shortcutKey);
	
	if(it == _actions.end())
		return nullptr;
	
	return it->second;
}

// *********************************************************************
// Class ActionManager
// *********************************************************************

ActionManager::ActionManager() : _shortcut(this)
{
}

ActionManager::~ActionManager()
{
}

bool ActionManager::add(ShortcutKey const &shortcut, Action* act)
{
	//Ajout à la liste des actions.
	if(!ActionManagerBase::add(shortcut, act))
		return false;
	
	//Et on l'ajouter à la liste des raccourcis.
	int id = _shortcut.creat(shortcut);
	Bind(EVT_SHORTCUT, &ActionManager::OnShortcut, this, id);
	
	return true;
}

bool ActionManager::remove(ShortcutKey const &shortcut)
{
	if(ActionManagerBase::remove(shortcut))
	{
		//Suppression du accourcie.
		_shortcut.remove(shortcut);
		return true;
	}
	
	return false;
}

void ActionManager::removeAll()
{
	//Suppression des actions.
	for(auto &it: _actions)
	{
		delete it.second;
		_shortcut.remove(it.first);
	}
		
	ActionManagerBase::removeAll();
}

void ActionManager::load(wxFileConfig & fileConfig)
{
	wxString stringShortcut;
	long lIndex;
	
	//Avent de charger quoi que se soi on supprime tout les raccourcis/actions
	removeAll();
	
	//On positionne le path
	fileConfig.SetPath("/ActionManager");
	
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
	
	//On positionne le path a la racine.
	fileConfig.SetPath("/");
}

void ActionManager::save(wxFileConfig & fileConfig)const
{
	for(auto &it: _actions)
	{
		//Obtenir la version string du raccourci.
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		//Crée un groupe pour ce raccourci.
		fileConfig.SetPath("/ActionManager/"+stringShortcut);
		
		//Sauvegarde de l'action
		it.second->save(fileConfig);
	}
}

void ActionManager::enable(bool val)
{
	_shortcut.enable(val);
}

void ActionManager::OnShortcut(ShortcutEvent& event)
{
	_actions[event.getShortcutKey()]->execute();
}

// *********************************************************************
// Class TmpActionManager
// *********************************************************************

TmpActionManager::TmpActionManager()
{
}

TmpActionManager::~TmpActionManager()
{
}

void TmpActionManager::init()
{
	auto act = ActionManager::getInstance()->getActions();
	
	for(auto it : *act)
		add(it.first,it.second);
}
	
void TmpActionManager::apply()
{
	ActionManager* actionManager = ActionManager::getInstance();
	
	//On supprime tout
	actionManager->removeAll();
	
	//Et on remplie
	for(auto it : _actions)
		actionManager->add(it.first,it.second);
}
