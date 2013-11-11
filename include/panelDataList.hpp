//! \file **************************************************************
//! \brief Header panel widgets avec une liste des boutons et un menu.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 26.09.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef PANEL_LIST_H
#define PANEL_LIST_H

#include "guiPanelDataList.h"
#include <wx/menu.h>

#include <vector>

// *********************************************************************
// Class PanelDataList
// *********************************************************************

//! \brief Panel de base pour les listes.
class PanelDataList : public GuiPanelDataList
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		//! \param name non de la liste (tous en minuscule).
		PanelDataList(wxWindow* parent, wxString name);
		//! \brief Destructeur.
		virtual ~PanelDataList();
		
	protected:
		//! \brief Ajout un item a la liste.
		//! \param item a ajouter. Si il est vide il ne sera pas ajouter.
		//! Chaque wxString correspond à une colonne.
		//! \param select true pour sélectionner l'item ajouter.
		void addItem(wxArrayString const& item, bool select = true);
		
		//! \brief Suppression d'item.
		//!
		//! Quand l'utilisateur clique sue le bouton "delete" cette méthode est appeler.
		//! \param l'item à supprimer.
		//! \return doit retourner true pour supprimer l'item de la liste.
		virtual bool OnDeleteItem(wxString const& item)=0;
		
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
		
		//! \brief Supprimer tout les items de la liste.
		void clear();
		
	private:
		//! \brief Supprimer un item.
		void OnButtonClickDelete(wxCommandEvent&);
		//! \brief Préférence d'un item.
		void OnButtonClickPreferences(wxCommandEvent&);
		//! \brief Ajouter un item
		void OnButtonClickAdd(wxCommandEvent&);
		
		//! \brief l'osque que la sélection change dans la liste.
		void OnListSelectionChanged(wxDataViewEvent&);
		
		void OnListItemContextMenu(wxDataViewEvent&);
		
		//! \brief Nom de la liste
		wxString _name;
		
		//menu
		wxMenu* _menu;
		wxMenuItem* _menuItemListAdd;
		wxMenuItem* _menuItemListPreferences;
		wxMenuItem* _menuItemListDelete;
};

#endif //PANEL_LIST_H
