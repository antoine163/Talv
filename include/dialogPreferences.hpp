//! \file **************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.11
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include "guiDialogPreferences.h"

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
		
	private:
		//! \brief applique les modifications et les sauvegardes dans le fichier de configuration.
		void applyAndSave();
		
		//! \brief quand l'utilisateur change de page.
		void OnNotebookPageChanged(wxNotebookEvent& event);
		//! \brief Applique les modifications et quitte le dialog.
		void OnButtonClickOK(wxCommandEvent& event);
		//! \brief Applique les modifications.
		void OnButtonClickApply(wxCommandEvent& event);
};

#endif //DIALOG_PREFERENCES_H
