//20.03.2013
//v 0.1

#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "action.hpp"

#include <wx/event.h>
#include <wx/fileconf.h>

#include <map>

#include "shortcut.hpp"

//singleton ?
class ActionManager : public wxEvtHandler
{
	public:		
		//! \brief Constructeur.
		ActionManager();
		
		//! \brief destructeur.
		virtual ~ActionManager();
		
		//Ajout d'une action.
		//return true si réussite, false si le raccourcie de l'action et déjà connue.
		bool add(ShortcutKey const &shortcut, Action const &act);
		bool remove(ShortcutKey const &shortcut);
		void removeAll();
		
		//Charger les actions à partir du fichier de config.
		void load(wxFileConfig const& fileConfig);
		//Sauvegarde des action dans le fichier de config.
		void sove(wxFileConfig & fileConfig);

		void enable(bool val = true);
		
		std::map<ShortcutKey, Action*> const* getAction()const;
		
	private:
		//Créé une nouvelle instance d'une action à partir de son nom.
		// \note il faudra prévoir de libérai la mémoire après utilisation de l'action.
		Action* newAction(Action const &act);
		
		void OnShortcut(ShortcutEvent& event);
	
		std::map<ShortcutKey, Action*> _actions;
		Shortcut _shortcut;
};

#endif //ACTION_MANAGER_H
