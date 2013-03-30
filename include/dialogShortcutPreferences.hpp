//version : 1.0
//02.01.2013

#ifndef DIALOG_SHORTCUT_PREFERENCES_H
#define DIALOG_SHORTCUT_PREFERENCES_H

#include "guiDialogShortcutPreferences.h"

#include "action.hpp"
#include "shortcut.hpp"

enum RawKeyCodeModifier_e
{
	#if defined(__UNIX__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 37,
	RAW_KEY_CODE_MODIFIER_ALT 		= 64,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 50,
	RAW_KEY_CODE_MODIFIER_WIN 		= 133,
	#elif defined(__WXMSW__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 17,
	RAW_KEY_CODE_MODIFIER_ALT 		= 18,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 16,
	RAW_KEY_CODE_MODIFIER_WIN 		= 91,
	#endif
};

class DialogShortcutPreferences : public GuiDialogShortcutPreferences 
{
	public:
		
		DialogShortcutPreferences(wxWindow* parent);
		DialogShortcutPreferences(	wxWindow* parent,
									ShortcutKey const& inShortcutKey,
									Action const& inAct);
		~DialogShortcutPreferences();
		
	protected:
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
		void OnLeftDown(wxMouseEvent&);
		void OnKillFocus(wxFocusEvent&);
		
		void updateTextCtrlChortcut(wxChar key);
		
	private:
		bool _keyCtrlIsPressed;
		bool _keyAltIsPressed;
		bool _keyShiftIsPressed;
		bool _keyWinIsPressed;
		
		bool _shortKeyIsValide;
};

#endif //DIALOG_SHORTCUT_PREFERENCES_H
