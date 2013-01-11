//02.01.2013

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include <map>

#include "gui/guiDialogPreferences.h"
#include "shortcut.hpp"
#include "action.hpp"

class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		DialogPreferences(std::map<ShortcutKey, Action*> const& shortcutAction);
		~DialogPreferences();
		
		void OnButtonClickDelete(wxCommandEvent&);
		void OnButtonClickAdd(wxCommandEvent&);
		
		void OnSelected(wxPropertyGridEvent& event);
		void OnDoubleClick(wxPropertyGridEvent& event);
		
	protected:
		std::map<wxString, wxString> _lang;
};

enum RawKeyCodeModifier_e
{
	#if defined(__UNIX__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 37,
	RAW_KEY_CODE_MODIFIER_ALT 		= 64,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 50,
	RAW_KEY_CODE_MODIFIER_WIN 		= 133,
	#elif defined(__WXMSW__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= ,
	RAW_KEY_CODE_MODIFIER_ALT 		= ,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= ,
	RAW_KEY_CODE_MODIFIER_WIN 		= ,
	#endif
};
	
class DialogChoiceShortcut : public GuiDialogChoiceShortcut 
{
	public:
		
		DialogChoiceShortcut(wxWindow* parent, wxString const& strShortcut = wxEmptyString);
		~DialogChoiceShortcut();

		void OnKeyUp(wxKeyEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		
		void updateStaticTextChoisShortcut(wxChar key);
		
		wxString GetShortcut();
		
	protected:
	
	private:
		bool _keyCtrlIsPressed;
		bool _keyAltIsPressed;
		bool _keyShiftIsPressed;
		bool _keyWinIsPressed;
		
		bool _shortKeyIsValide;
};

#endif //DIALOG_PREFERENCES_H
