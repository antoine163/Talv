//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 27.12.2013
//!
//! ****************************************************************************

#ifndef CTRL_PICK_SHORTCUT_KEY_H
#define CTRL_PICK_SHORTCUT_KEY_H

//App
#include "shortcut.hpp"

//WxWidgets
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>

// *****************************************************************************
// Class CtrlPickShortcutKey
// *****************************************************************************

class CtrlPickShortcutKey : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		//! \param shortcutKey le raccourci par défaut.
		//! \param check si true le raccourci sélectionner par l'utilisateur changera de
		//! couleur si le raccourci est connue par. 
		CtrlPickShortcutKey(wxWindow* parent, ShortcutKey const& shortcutKey = ShortcutKey(), bool check = false);
		//! \brief Destructeur.
		virtual ~CtrlPickShortcutKey();
		
		void setShortcutKey(ShortcutKey const& shortcutKey);
		ShortcutKey getShortcutKey();
		
		void SetFocus();

	private:
		void onKeyDown(wxKeyEvent& event);
		void onKeyUp(wxKeyEvent& event);
		void onSetFocus(wxFocusEvent& event);
		void onKillFocus(wxFocusEvent& event);
		
		void checkInManAction();
		
		bool _shortKeyIsValide;
		bool _isFocused;
		bool _check;
		ShortcutKey _shortcutKeyFault;
		ShortcutKey _shortcutKey;
		Modifier_e _modPressed;
		
		wxTextCtrl* _textCtrlShortcutKey;
};

#endif //CTRL_PICK_SHORTCUT_KEY_H
