//! \file **************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "actionManager.hpp"

#ifdef USE_ACT_TRANSLATION
#include "action/actTranslation.hpp"
#endif
#ifdef USE_ACT_SAVE_TRANSLATION
#include "action/actSaveTranslation.hpp"
#endif
#ifdef USE_ACT_SAY
#include "action/actSay.hpp"
#endif


ActionManager::ActionManager() : _shortcut(this)
{
}

ActionManager::~ActionManager()
{
	removeAll();
}

bool ActionManager::add(ShortcutKey const &shortcut, Action const &act)
{
	//Si le raccourci existe déjà.
	if(_actions.count(shortcut) > 0)
		return false;
		
	//Sinon on l'ajoute.
	_actions[shortcut] = newAction(act);
	
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
				
		//Crée et charge les préférences de l'action.
		#ifdef USE_ACT_TRANSLATION
		if(actTypeName == "ActTranslation")
		{
			add(ShortcutKey::stringToShortcutKey(stringShortcut), ActTranslation::load(fileConfig));
		}
		#endif
			
		#ifdef USE_ACT_SAVE_TRANSLATION
		if(actTypeName == "ActSaveTranslation")
		{
			add(ShortcutKey::stringToShortcutKey(stringShortcut), ActSaveTranslation::load(fileConfig));
		}
		#endif
			
		#ifdef USE_ACT_SAY
		if(actTypeName == "ActSay")
		{
			add(ShortcutKey::stringToShortcutKey(stringShortcut), ActSay::load(fileConfig));
		}
		#endif
		
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
			
		//Sauvegarder le type d'action et ces préférences.
		#ifdef USE_ACT_TRANSLATION
		if(typeid(*it.second).hash_code() == typeid(ActTranslation).hash_code())
		{
			fileConfig.Write("ActTypeName", "ActTranslation");
			it.second->sove(fileConfig);
			continue;
		}
		#endif
			
		#ifdef USE_ACT_SAVE_TRANSLATION
		if(typeid(*it.second).hash_code() == typeid(ActSaveTranslation).hash_code())
		{
			fileConfig.Write("ActTypeName", "ActSaveTranslation");
			it.second->sove(fileConfig);
			continue;
		}
		#endif
			
		#ifdef USE_ACT_SAY
		if(typeid(*it.second).hash_code() == typeid(ActSay).hash_code())
		{
			fileConfig.Write("ActTypeName", "ActSay");
			it.second->sove(fileConfig);
			continue;
		}
		#endif
	}
}

void ActionManager::enable(bool val)
{
	_shortcut.enable(val);
}

std::map<ShortcutKey, Action*> const* ActionManager::getAction()const
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

Action* ActionManager::newAction(Action const &act)
{	
	#ifdef USE_ACT_TRANSLATION
	if(typeid(act).hash_code() == typeid(ActTranslation).hash_code())
		return new ActTranslation(static_cast<ActTranslation const &>(act));
	#endif
		
	#ifdef USE_ACT_SAVE_TRANSLATION
	if(typeid(act).hash_code() == typeid(ActSaveTranslation).hash_code())
		return new ActSaveTranslation(static_cast<ActSaveTranslation const &>(act));
	#endif
		
	#ifdef USE_ACT_SAY
	if(typeid(act).hash_code() == typeid(ActSay).hash_code())
		return new ActSay(static_cast<ActSay const &>(act));
	#endif

	return nullptr;
}

void ActionManager::OnShortcut(ShortcutEvent& event)
{
	_actions[event.getShortcutKey()]->execute();
}
