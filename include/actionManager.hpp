//! \file **************************************************************
//! \brief Header Gestion des action/raccourcis
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

#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "action.hpp"
#include "singleton.hpp"
#include "shortcut.hpp"

#include <wx/event.h>
#include <wx/fileconf.h>
#include <map>

// *********************************************************************
// Class ActionManager
// *********************************************************************

//! \brief Interface utilisateur pour les gestions des actions avec leur raccourcis associer.
class ActionManager : public wxEvtHandler, public Singleton<ActionManager>
{
	friend class Singleton<ActionManager>;
	
	public:				
		//! \brief Ajout d'une action.
		//! Le paramètre \b act devra étre allouer dynamiquement au préalable, \ref ActionManager se charge de libérer la mémoire après utilisation.
		//! \param shortcut c'est le raccourci à ajouter.
		//! \param act c'est l'action à ajouter est qui sera lier au raccourci \b shortcut.
		//! \return true si réussite, false si le raccourcie de l'action et déjà connue.
		bool add(ShortcutKey const &shortcut, Action* act);
		
		//! \brief Supprimer d'un raccourci/action.
		//! \return true si réussite, false si le raccourcis/actions est déjà connue.
		bool remove(ShortcutKey const &shortcut);
		
		//! \brief Supprimer tout les raccourcis/actions.
		void removeAll();
		
		//! \brief Charger les raccourcis/actions à partir du fichier de config.
		//! \note Cette méthode appellera \ref removeAll() au préalable.
		void load(wxFileConfig & fileConfig);
		
		//! \brief Sauvegarde des action dans le fichier de config.
		//! Ne supprime pas les enceint raccourcis/actions qui pourrai déjà existé dans le wxFileConfig.
		void sove(wxFileConfig & fileConfig)const;

		//! \brief Active ou désactive les raccourcis
		void enable(bool val = true);
		
		//! \brief Obtenir la lites des raccourcis/actions.
		std::map<ShortcutKey, Action*> const* getActions()const;
		
		//! \brief Obtenir l'action d'un raccourcis.
		//! \param shortcutKey est le raccourcis à rechercher.
		//! \return nullptr si raccourci/action n'existe pas.
		Action const* getAction(ShortcutKey const& shortcutKey)const;
		
	private:
		//! \brief Constructeur.
		ActionManager();
		
		//! \brief destructeur.
		virtual ~ActionManager();
		
		//! \brief Méthode appeler lorsque un événement de raccourci clavier survient.
		void OnShortcut(ShortcutEvent& event);
	
		//! \brief Lites des raccourcis/actions.
		std::map<ShortcutKey, Action*> _actions;
		
		//! \brief Gestion des raccourcis.
		Shortcut _shortcut;
};

#endif //ACTION_MANAGER_H
