//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 28.12.2013
//!
//! ****************************************************************************

#ifndef DLG_PICK_SHORTCUT_KEY_H
#define DLG_PICK_SHORTCUT_KEY_H

//App
#include "control/ctrlPickShortcutKey.hpp"
#include "shortcut.hpp"

//WxWidgets
#include <wx/dialog.h>
#include <wx/window.h>
#include <wx/string.h>

// *****************************************************************************
// Class DlgPickShortcutKey
// *****************************************************************************

class DlgPickShortcutKey : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DlgPickShortcutKey(wxWindow* parent, wxString const& title, ShortcutKey const& shortcutKey = ShortcutKey());
		//! \brief Destructeur.
		~DlgPickShortcutKey();
		
		void setShortcutKey(ShortcutKey const& shortcutKey);
		ShortcutKey getShortcutKey();
		
		void SetFocus();
		
	private:
		CtrlPickShortcutKey* _ctrlPickShortcutKey;
};

#endif //DLG_PICK_SHORTCUT_KEY_H
