//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
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
		//! \param shortcutKey le raccourci par défaut. Si le raccourcis est valides 
		//! le raccourci sélectionner par l'utilisateur changera de couleur si le raccourci est connue par \ref manAction (en excluent le raccourci par défaut).
		CtrlPickShortcutKey(wxWindow* parent, ShortcutKey const& shortcutKey = ShortcutKey());
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
		
		void updateTextCtrl(wxChar key);
		void checkInManAction();
		
		bool _keyCtrlIsPressed;
		bool _keyAltIsPressed;
		bool _keyShiftIsPressed;
		bool _keySuperIsPressed;
		bool _shortKeyIsValide;
		bool _isFocused;
		ShortcutKey _shortcutKeyFault;
		
		wxTextCtrl* _textCtrlShortcutKey;
};

#ifndef __DOXYGEN__
enum RawKeyCodeModifier_e
{
	#if defined(__UNIX__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 37,
	RAW_KEY_CODE_MODIFIER_ALT 		= 64,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 50,
	RAW_KEY_CODE_MODIFIER_SUPER		= 133,
	#elif defined(__WXMSW__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 17,
	RAW_KEY_CODE_MODIFIER_ALT 		= 18,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 16,
	RAW_KEY_CODE_MODIFIER_SUPER		= 91,
	#endif
};
#endif

#endif //CTRL_PICK_SHORTCUT_KEY_H
