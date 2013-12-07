//! \file **********************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 4.0
//! \date 02.01.2013
//!
//! ****************************************************************************

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

//WxWidgets
#include <wx/dialog.h>

// *****************************************************************************
// Class DialogPreferences
// *****************************************************************************

//! \brief Dialogue générale des préférences.
class DialogPreferences : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DialogPreferences();
		//! \brief Destructeur.
		~DialogPreferences();
		
	private:
		void onClose(wxCloseEvent& event);
		
		void onButtonClickApply(wxCommandEvent& event);
		void onButtonClickCancel(wxCommandEvent& event);
		void onButtonClickOK(wxCommandEvent& event);
		
};

#endif //DIALOG_PREFERENCES_H
