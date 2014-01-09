//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 31.12.2013
//!
//! ****************************************************************************

#ifndef DLG_PREFERENCES_ACTION_H
#define DLG_PREFERENCES_ACTION_H

//App
#include "dialogInlay.hpp"
#include "action.hpp"
#include "shortcut.hpp"
#include "control/ctrlPickShortcutKey.hpp"

//WxWidgets
#include <wx/listbook.h>
#include <wx/window.h>

// *****************************************************************************
// Class DlgPreferencesAction
// *****************************************************************************

class DlgPreferencesAction : public DialogInlay 
{
	public:
		//! \brief Constructeur.
		DlgPreferencesAction(wxWindow* parent);
		//! \brief Constructeur.
		DlgPreferencesAction(wxWindow* parent, ShortcutKey const& shortcutKey, Action const* action);
		//! \brief Destructeur.
		~DlgPreferencesAction();
		
		ShortcutKey getShortcutKey();
		Action* newCloneAction();
		
	private:
		//! \brief listbook du dialogue.
		wxListbook* _listbook;
		
		CtrlPickShortcutKey* _ctrlPickShortcutKey;
		std::vector<Action*> _allActions;
};

#endif //DLG_PREFERENCES_ACTION_H
