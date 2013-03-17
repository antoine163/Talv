//version : 1.0
//02.01.2013

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include <map>

#include "guiDialogPreferences.h"

class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		DialogPreferences();
		~DialogPreferences();
		
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
		
		//! \brief Pour savoir si le bouton shutdown et actionner
		bool shutdownIsToggle()const;
		
	protected:		
};

#endif //DIALOG_PREFERENCES_H
