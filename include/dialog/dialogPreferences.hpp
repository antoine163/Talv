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
//!
//! Se dialogue va appeler  \ref Manager::newEditWindow() de touts les managers
//! et les insérais dans un \b wxNotebook.
class DialogPreferences : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DialogPreferences();
		//! \brief Destructeur.
		~DialogPreferences();
		
	private:
		//! \brief CallBack lorsque le dialogue est fermer.
		void onClose(wxCloseEvent& event);
		
		//! \brief CallBack lorsque le bouton \b Apply à été cliquet.
		void onButtonClickApply(wxCommandEvent& event);
		//! \brief CallBack lorsque le bouton \b Cancel à été cliquet.
		void onButtonClickCancel(wxCommandEvent& event);
		//! \brief CallBack lorsque le bouton \b OK à été cliquet.
		void onButtonClickOK(wxCommandEvent& event);
		
};

#endif //DIALOG_PREFERENCES_H
