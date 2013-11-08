//! \file **************************************************************
//! \brief Header Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.17
//! \date 20.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "editableByPanel.hpp"
#include "action.hpp"
#include "singleton.hpp"
#include "managerBase.hpp"
#include "shortcut.hpp"
#include "panelList.hpp"

#include <wx/event.h>
#include <wx/fileconf.h>
#include <vector>

// *********************************************************************
// Class PanelEditActions
// *********************************************************************

class ActionManager;

//! \brief Panel d'édition des actions.
class PanelEditActions : public PanelList 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		PanelEditActions(wxWindow* parent, ActionManager* manager);
		//! \brief Destructeur.
		virtual ~PanelEditActions();
		
		//! \brief Mise à jour de l'affichage de la liste avec \ref EditActionManager
		virtual void Update();
		
	private:	
		//! \brief Suppression de l'action.
		bool OnDeleteItem(wxString const& item);
		//! \brief Préférence de l'action.
		wxArrayString OnPreferencesItem(wxString const& item);
		//! \brief Ajouter d'une action.
		wxArrayString OnAddItem();
		
		//! \brief le manager à éditer.
		ActionManager* _actionManager;
};

// *********************************************************************
// Class ActionManager
// *********************************************************************

//! \brief Interface utilisateur pour les gestions des actions avec leur raccourcis associer.
class ActionManager : 	public wxEvtHandler,
						public ManagerBase<ShortcutKey, Action>,
						public Singleton<ActionManager>,
						public EditableByPanel
{	
	friend class Singleton<ActionManager>;
	
	public:			
		//! \brief Ajout d'une action.
		//! Le paramètre \b act devra étre allouer dynamiquement au préalable, \ref ActionManagerBase se charge de libérer la mémoire après utilisation.
		//! \param shortcut c'est le raccourci à ajouter.
		//! \param act c'est l'action à ajouter est qui sera lier au raccourci \b shortcut.
		//! \return true si réussite, false si le raccourcie de l'action et déjà connue.
		bool add(ShortcutKey const &shortcut, Action* act);
		
		//! \brief Supprimer d'un raccourci/action.
		//! \return true si réussite, false si le raccourcis/actions n'est pas connue.
		bool remove(ShortcutKey const& shortcut);
		
		//! \brief Supprimer tout les raccourcis/actions.
		void removeAll();
		
		//! \brief Charger les raccourcis/actions à partir du fichier de config.
		//! \note Cette méthode appellera \ref removeAll() au préalable.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde des action dans le fichier de config.
		//! Ne supprime pas les enceint raccourcis/actions qui pourrai déjà existé dans le wxFileConfig.
		void save(wxFileConfig& fileConfig)const;
		
		//! \brief Active ou désactive les raccourcis. 
		void enableShortcuts(bool val=true);
		
		//! \brief Permet de savoir si une liste est utiliser par une ou des actions.
		bool actionUseList(wxString const& listName);
		
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual wxPanel* newEditPanel(wxWindow *parent);
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelCheck()const;
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelApply();
		
	private:
		//! \brief Constructeur.
		ActionManager();
		
		//! \brief destructeur.
		virtual ~ActionManager();
		
		//! \brief Méthode appeler lorsque un événement de raccourci clavier survient.
		void OnShortcut(ShortcutEvent& event);
		
		//! \brief Gestion des raccourcis.
		Shortcut _shortcut;
};

// *********************************************************************
// Class EditActionManager
// *********************************************************************

////! \brief Gestions des actions avec leur raccourcis associer de façon temporaire aven de modifier ActionManager.
//class EditActionManager : public ManagerBase<ShortcutKey, Action>, public Singleton<EditActionManager>
//{	
	//friend class Singleton<EditActionManager>;
	
	//public:
		////! \brief Initialisation à partir de ActionManager
		//void init();
		
		////! \brief Applique à ActionManager
		//void apply();
		
		////! \brief Obtenir la liste des raccourcis utiliser une liste.
		//std::vector<ShortcutKey> getShortcutUsedList(wxString const& listName);
		
	//private:
		////! \brief Constructeur.
		//EditActionManager();
		
		////! \brief destructeur.
		//virtual ~EditActionManager();
//};

#endif //ACTION_MANAGER_H
