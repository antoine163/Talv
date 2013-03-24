//20.03.2013
//v 0.2

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
		
		//! \brief Ajout d'une action.
		//! \param shortcut c'est le raccourci a ajouter.
		//! \param act c'est l'action a rajouter est qui sera lier au raccourci \b shortcut.
		//! \return true si réussite, false si le raccourcie de l'action et déjà connue.
		bool add(ShortcutKey const &shortcut, Action const &act);
		
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
		std::map<ShortcutKey, Action*> const* getAction()const;
		
	private:
		//! \brief Créé une nouvelle instance d'une action à partir de son nom.
		//! \note il faudra prévoir de libérai la mémoire après utilisation de l'action.
		Action* newAction(Action const &act);
		
		//! \brief Méthode appeler lorsque un événement de raccourci clavier survient.
		void OnShortcut(ShortcutEvent& event);
	
		//! \brief Lites des raccourcis/actions.
		std::map<ShortcutKey, Action*> _actions;
		
		//! \brief Gestion des raccourcis.
		Shortcut _shortcut;
};

#endif //ACTION_MANAGER_H
