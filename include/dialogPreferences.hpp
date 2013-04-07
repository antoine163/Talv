//! \file **************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.8
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
		
		//! \brief Pour savoir si le boite de l'afficha de l'icône de l'application est cocher ou pas.
		bool showIcon()const;
		
	private:
		//! \brief Applique les modification et les sauvegarder dans le fichier de config.
		void applyAndSave();
		
		//! \brief Supprimer une action.
		void OnButtonClickActDelete(wxCommandEvent&);
		//! \brief Configurai une action une action.
		void OnButtonClickActPreferences(wxCommandEvent&);
		//! \brief Ajouter une action une action.
		void OnButtonClickActAdd(wxCommandEvent&);
		
		//! \brief Applique les modifications.
		void OnButtonClickApply(wxCommandEvent&);
		//! \brief Applique les modifications est quitte le dialog.
		void OnButtonClickOK(wxCommandEvent&);
		
		//! \brief Un item a été désélectionner.
		void OnListItemDeselectedAction(wxListEvent& event);
		//! \brief Un item a été sélectionner.
		void OnListItemSelectedAction(wxListEvent& event);
		
		//! \brief Ajout un raccourci/action.
		//! \return true si le raccourci a bien été ajouter. false si le raccourci existe déjà.
		bool addListShortcutAction(ShortcutKey const& shortcut, Action const* act, long item = -1);
		//! \brief Supprime un raccourci/action.
		//! \return le numéro de l'item supprimer. -1 si le raccourci n'existe pas.
		long deleteListShortcutAction(ShortcutKey const& shortcut);
		//! \brief Pour savoir si un raccourci existe.
		//! \return true si le raccourci existe, false sinon.
		bool existListShortcutAction(ShortcutKey const& shortcut);

		//! \brief Liste des raccourcis/actions dans l'êta du dialogue.
		std::map<ShortcutKey, Action*> _listShortcutAction;
		
		//! \brief Liste des Item qui sont sélectionner dans la liste des raccourcis/actions.
		std::vector<wxListItem> _listItemSelected;
};

#endif //DIALOG_PREFERENCES_H
