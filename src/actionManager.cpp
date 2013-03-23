//20.03.2013
//v 0.1

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

void ActionManager::load(wxFileConfig const& fileConfig)
{
}

void ActionManager::sove(wxFileConfig & fileConfig)
{
}

void ActionManager::enable(bool val)
{
	_shortcut.enable(val);
}

std::map<ShortcutKey, Action*> const* ActionManager::getAction()const
{
	return &_actions;
}

Action* ActionManager::newAction(Action const &act)
{	
	#ifdef USE_ACT_TRANSLATION
	if(typeid(act).hash_code() == typeid(ActTranslation).hash_code())
		return new ActTranslation(static_cast<ActTranslation const &>(act));
	#endif
		
	#ifdef USE_ACT_SAVE_TRANSLATION
	if(typeid(act).hash_code() == typeid(ActSaveTranslation).hash_code())
		return new ActTranslation(static_cast<ActSaveTranslation const &>(act));
	#endif
		
	#ifdef USE_ACT_SAY
	if(typeid(act).hash_code() == typeid(ActSay).hash_code())
		return new ActTranslation(static_cast<ActSay const &>(act));
	#endif

	return 0;
}

void ActionManager::OnShortcut(ShortcutEvent& event)
{
	_actions[event.getShortcutKey()]->execute();
}
