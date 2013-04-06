//! \file **************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.3
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
		
		DialogPreferences(ActionManager *actionManager);
		~DialogPreferences();
		
		//! \brief Pour savoir si le bouton shutdown et actionner.
		bool shutdownIsToggle()const;
		
		//! \brief Pour savoir si le boite de l'afficha de l'icône de l'application est cocher ou pas.
		bool showIcon()const;
		
	protected:		
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
		
		//! \brief ActionManager qu'il faut modifier si changement de l'utilisateur via le GUI.
		ActionManager *_actionManager;
		
		
		//! \brief Liste des Item qui sélectionner dans la liste des raccourcis/actions.
		std::vector<wxListItem> _listItemSelected;
		//! \brief Liste des raccourcis qui on été supprimé de la liste des raccourcis/actions et qu'il
		//! faudra probablement affecter à /ref _actionManager avec de quitter le dialogue ou a la sauvegarde.
		std::vector<ShortcutKey> _shortcutKeyActDelete;
};

#endif //DIALOG_PREFERENCES_H
