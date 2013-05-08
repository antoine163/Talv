//! \file **************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include "guiDialogPreferences.h"
#include "actionManager.hpp"
#include "shortcut.hpp"

#include <wx/listctrl.h>
#include <vector>

// *********************************************************************
// Class PanelList
// *********************************************************************

class PanelList : public GuiPanelList 
{
	public:
		
		PanelList(wxWindow* parent);
		virtual ~PanelList();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		virtual void applayAndSave(wxFileConfig & fileConfig)=0;
		
	protected:
		//! \brief Liste des Item qui sont sélectionner.
		std::vector<wxListItem> _listItemSelected;
			
		//! \brief Supprimer un item.
		virtual void OnButtonClickDelete(wxCommandEvent& event){event.Skip();}
		//! \brief Préférence d'un item.
		virtual void OnButtonClickPreferences(wxCommandEvent& event){event.Skip();}
		//! \brief Ajouter un item
		virtual void OnButtonClickAdd(wxCommandEvent& event){event.Skip();}
		
	private:
		//! \brief Un item a été désélectionner.
		void OnListItemDeselected(wxListEvent& event);
		//! \brief Un item a été sélectionner.
		void OnListItemSelected(wxListEvent& event);
};

// *********************************************************************
// Class PanelListActions
// *********************************************************************

class PanelListActions : public PanelList 
{
	public:
		
		PanelListActions(wxWindow* parent);
		virtual ~PanelListActions();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		void applayAndSave(wxFileConfig & fileConfig);
		
	private:	
		//! \brief Supprimer un item.
		void OnButtonClickDelete(wxCommandEvent&);
		
		//! \brief Préférence d'un item.
		void OnButtonClickPreferences(wxCommandEvent&);
		
		//! \brief Ajouter un item.
		void OnButtonClickAdd(wxCommandEvent&);
		
		//! \brief Ajout un raccourci/action.
		//! \return true si le raccourci a bien été ajouter. false si le raccourci existe déjà.
		//! \param shortcut le raccourci à ajouter (en version wxString).
		//! \param act l'action a ajouter.
		//! \param item pour préciser ça position dans la liste. 
		//! -1 pour l'ajouter au début de la liste
		bool addListShortcutAction(wxString const& shortcut, Action const* act, long item = -1);
		
		//! \brief Supprime un raccourci/action.
		//! \param shortcut le raccourci à supprimer (en version wxString).
		//! \return le numéro de l'item supprimer. -1 si le raccourci n'existe pas.
		long deleteListShortcutAction(wxString const& shortcut);
		
		//! \brief Pour savoir si un raccourci existe.
		//! \param shortcut le raccourci à vérifier (en version wxString).
		//! \return true si le raccourci existe, false sinon.
		bool existListShortcutAction(wxString const& shortcut);

		//! \brief Liste des raccourcis/actions dans l'êta du dialogue (raccourci en version wxString).
		std::map<wxString, Action*> _listShortcutAction;
};

// *********************************************************************
// Class PanelListLists
// *********************************************************************

class PanelListLists : public PanelList 
{
	public:
		
		PanelListLists(wxWindow* parent);
		virtual ~PanelListLists();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		void applayAndSave(wxFileConfig & fileConfig);
		
	private:		
		//! \brief Supprimer un item.
		void OnButtonClickDelete(wxCommandEvent&);
		//! \brief Préférence d'un item.
		void OnButtonClickPreferences(wxCommandEvent&);
		//! \brief Ajouter un item
		void OnButtonClickAdd(wxCommandEvent&);
};

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

//! \brief Dialogue générale des préférence.
class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		DialogPreferences();
		~DialogPreferences();
		
		//! \brief Pour savoir si le bouton shutdown et actionner.
		bool shutdownIsToggle()const;
		
	private:
		//! \brief Applique les modification et les sauvegarder dans le fichier de config.
		void applyAndSave();
		
		//! \brief Applique les modifications et quitte le dialog.
		void OnButtonClickOK(wxCommandEvent& event);
		//! \brief Applique les modifications.
		void OnButtonClickApply(wxCommandEvent& event);
		//! \brief applique les modification et les sauvegarde dans le fichier de configuration.
		void applayAndSave();
		
		PanelListActions* _PanelListActions;
		PanelListLists* _PanelListLists;
};

#endif //DIALOG_PREFERENCES_H
