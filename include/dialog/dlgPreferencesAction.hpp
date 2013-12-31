//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 31.12.2013
//!
//! ****************************************************************************

#ifndef DLG_PREFERENCES_ACTION_H
#define DLG_PREFERENCES_ACTION_H

//App
#include "control/ctrlPickShortcutKey.hpp"

//WxWidgets
#include <wx/dialog.h>
#include <wx/listbook.h>
#include <wx/window.h>

// *****************************************************************************
// Class DlgPreferencesAction
// *****************************************************************************

class DlgPreferencesAction : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DlgPreferencesAction(wxWindow* parent);
		//DlgPreferencesAction(wxWindow* parent, ShortcutKey const& shortcutKey, Action const& Action);
		//! \brief Destructeur.
		~DlgPreferencesAction();
		
		//ShortcutKey getShortcutKey();
		//Action* newCloneAction();
		
	private:
		//! \brief CallBack lorsque le listbook a changer de page.
		void onListbookChanged(wxBookCtrlEvent& event);
		
		//! \brief CallBack lorsque le dialogue est fermer.
		void onClose(wxCloseEvent& event);
		
		//! \brief CallBack lorsque le bouton \b Cancel à été cliquet.
		void onButtonClickCancel(wxCommandEvent& event);
		//! \brief CallBack lorsque le bouton \b OK à été cliquet.
		void onButtonClickOK(wxCommandEvent& event);
	
		//! \brief listbook du dialogue.
		wxListbook* _listbook;
		
		CtrlPickShortcutKey* _ctrlPickShortcutKey;
};

#endif //DLG_PREFERENCES_ACTION_H
