//! \file **********************************************************************
//! \brief Header Gestion des actions/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.0
//! \date 20.03.2013
//!
//! ****************************************************************************

#ifndef MAN_ACTION_H
#define MAN_ACTION_H

//App
#include "manager.hpp"
#include "action.hpp"
#include "shortcut.hpp"
#include "control/ctrlDataList.hpp"

//Stl
#include <map>

// *****************************************************************************
// Class ManAction
// *****************************************************************************

//! \ingroup manager
//! \brief ManAction
class ManAction : public Manager, public wxEvtHandler
{
	DECLARE_MANAGER(ManAction);
	
	public:

		virtual WinManager* newEditWindow(wxWindow* parent);
		
		//! \brief Ajout d'une action.
		//! Le paramètre \b act devra étre allouer dynamiquement au préalable, \ref ManagerAction se charge de libérer la mémoire après utilisation.
		//! \param shortcut c'est le raccourci associer à l'action.
		//! \param act c'est l'action à ajouter.
		//! \return true si réussite, false si le raccourcie de l'action et déjà connue.
		bool add(ShortcutKey const &shortcut, Action* act);
		
		//! \brief Obtenir l'action associer a un raccourci.
		//! \param shortcut c'est le raccourci associer à l'action.
		//! \return nullptr si le raccourci n'a pas été trouver.
		Action const* getAction(ShortcutKey const &shortcut)const;
		
		//! \brief Pour savoir si une action existe.
		//! \return true si le raccourcis de l'action existe.
		bool exist(ShortcutKey const& shortcut);
		
		//! \brief Supprimer d'une action.
		//! \return true si réussite, false si le raccourcis de l'action n'a pas été trouver.
		bool remove(ShortcutKey const& shortcut);
		
		//! \brief Supprimer tout les actions.
		void removeAll();
		
		//! \brief Active ou désactive les raccourcis.
		//! \param val si false auqu'une action sera exécuter.
		void shortcutsEnable(bool val=true);
		
		//! \brief Pour savoir si les raccourcis sont activer.
		bool shortcutsIsEnable();
		
		//! \brief Obtenir la liste des raccourcis actions.
		std::map<ShortcutKey, Action*>const& getShortcutKeysActions()const;
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		void onShortcut(ShortcutEvent& event);
		
		//! \brief Les action qui on été ajouter.
		//! Ceci permet aussi de faire un lien entre les raccourcis et les actions.
		//! \see add()
		std::map<ShortcutKey, Action*> _shortcutKeysActions;
		
		//! \brief Gestion des raccourcis.
		Shortcut _shortcut;
};

// *****************************************************************************
// Class WinManAction
// *****************************************************************************

//! \brief WinManAction
class WinManAction : public WinManager
{
	public:
		WinManAction(wxWindow* parent);
		~WinManAction();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onAdd(wxCommandEvent& event);
		void onPreferences(wxCommandEvent& event);
		void onFind(wxCommandEvent& event);
		void onDelete(wxCommandEvent& event);
		void onChangeShortcut(wxCommandEvent& event);
		
		void onItemEditingStarted(wxDataViewEvent& event);
		void onItemEditingDone(wxDataViewEvent& event);
		
		
		void changeSelectedShortcut(ShortcutKey newShortcut);
		//Cette méthode pose la question a l'utilisateur pour supprimer les
		//raccourcis équivalent si il existe.
		bool checkAndDeleteShortcut(ShortcutKey shortcut, int ignoreRow = wxNOT_FOUND);
		
		bool ensureVisible(ShortcutKey shortcut);
		
		//Élément du gui.
		CtrlDataList* _ctrlDataList;
		
		wxString _itemOldShortcutEditing;
};


#endif //MAN_ACTION_H
