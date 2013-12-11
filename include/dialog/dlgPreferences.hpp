//! \file **********************************************************************
//! \brief Header Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 4.1
//! \date 02.01.2013
//!
//! ****************************************************************************

#ifndef DLG_PREFERENCES_H
#define DLG_PREFERENCES_H

//WxWidgets
#include <wx/dialog.h>

// *****************************************************************************
// Class DialogPreferences
// *****************************************************************************

//! \brief Dialogue générale des préférences.
//!
//! Se dialogue va appeler  \ref Manager::newEditWindow() de touts les managers
//! et les insérais dans un \b wxNotebook.
class DlgPreferences : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DlgPreferences();
		//! \brief Destructeur.
		~DlgPreferences();
		
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

#endif //DLG_PREFERENCES_H
