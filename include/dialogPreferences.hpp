//! \file **************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.3
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
#include "listManager.hpp"
#include "shortcut.hpp"

#include <wx/listctrl.h>
#include <wx/menu.h>
#include <vector>

// *********************************************************************
// Class PanelList
// *********************************************************************

//! \brief Panel de base pour les listes.
class PanelList : public GuiPanelList 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		//! \param name non de la liste
		PanelList(wxWindow* parent, wxString name);
		//! \brief Destructeur.
		virtual ~PanelList();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		virtual void applayAndSave(wxFileConfig & fileConfig)=0;
		
	protected:
		//! \brief Ajout un item a la liste.
		//! \param item a ajouter. Si il est vide il ne sera pas jouter.
		//! Chaque wxString correspond à une colonne.
		//! \param select true pour sélectionner l'item ajouter.
		void addItem(wxArrayString const& item, bool select = true);
		
		//! \brief Suppression d'item.
		//!
		//! Quand l'utilisateur clique sue le bouton "delete" cette méthode est appeler.
		//! \param l'item à supprimer.
		virtual void OnDeleteItem(wxString const& item)=0;
		
		//! \brief Préférence d'un item.
		//!
		//! Quand l'utilisateur clique sue le bouton "preference" cette méthode est appeler.
		//! \param l'item à modifier.
		//! \return l'item modifier. Chaque wxString correspond à une colonne.
		virtual wxArrayString OnPreferencesItem(wxString const& item)=0;
		
		//! \brief ajouter d'un item.
		//!
		//! Quand l'utilisateur clique sue le bouton "add" cette méthode est appeler.
		//! \return le nouveau item. Si le wxArrayString est vide l'item ne sera pas ajouter.
		//! Chaque wxString correspond à une colonne.
		virtual wxArrayString OnAddItem()=0;
		
		//! \brief Liste des Item qui sont sélectionner.
		std::vector<wxListItem> _listItemSelected;
		
	private:
		//! \brief Supprimer un item.
		void OnButtonClickDelete(wxCommandEvent&);
		//! \brief Préférence d'un item.
		void OnButtonClickPreferences(wxCommandEvent&);
		//! \brief Ajouter un item
		void OnButtonClickAdd(wxCommandEvent&);
		
		void OnListItemRightClick(wxListEvent& event);
		
		//! \brief Un item a été désélectionner.
		void OnListItemDeselected(wxListEvent& event);
		//! \brief Un item a été sélectionner.
		void OnListItemSelected(wxListEvent& event);
		
		//! \brief Nom de la liste
		wxString _name;
		
		//menu
		wxMenu* _menu;
		
		wxMenuItem* _menuItemListAdd;
		wxMenuItem* _menuItemListPreferences;
		wxMenuItem* _menuItemListDelete;
};

// *********************************************************************
// Class PanelListActions
// *********************************************************************

//! \brief Panel la liste de actions.
class PanelListActions : public PanelList 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		PanelListActions(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~PanelListActions();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		void applayAndSave(wxFileConfig & fileConfig);
		
	private:	
		//! \brief Suppression de l'action.
		void OnDeleteItem(wxString const& item);
		//! \brief Préférence de l'action.
		wxArrayString OnPreferencesItem(wxString const& item);
		//! \brief Ajouter d'une action.
		wxArrayString OnAddItem();

		//! \brief Liste des raccourcis/actions dans l'êta du dialogue (raccourci en version wxString).
		std::map<wxString, Action*> _listShortcutAction;
};

// *********************************************************************
// Class PanelListLists
// *********************************************************************

//! \brief Panel la liste de listes.
class PanelListLists : public PanelList 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		PanelListLists(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~PanelListLists();
		
		//! \brief Applique les modification et les sauvegarde dans le fichier de configuration.
		void applayAndSave(wxFileConfig & fileConfig);
		
	private:		
		//! \brief Suppression de la liste.
		void OnDeleteItem(wxString const& item);
		//! \brief Préférence de la liste.
		wxArrayString OnPreferencesItem(wxString const& item);
		//! \brief Ajouter d'une liste.
		wxArrayString OnAddItem();
};

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

//! \brief Dialogue générale des préférence.
class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		//! \brief Constructeur.
		DialogPreferences();
		//! \brief Destructeur.
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
