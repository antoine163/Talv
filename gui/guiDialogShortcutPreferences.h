///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogShortcutPreferences__
#define __guiDialogShortcutPreferences__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogShortcutPreferences
///////////////////////////////////////////////////////////////////////////////
class GuiDialogShortcutPreferences : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* _textCtrlChortcut;
		wxChoice* _choiceAction;
		wxStaticText* _staticTextDescription;
		wxPanel* m_panel1;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnKeyUp( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogShortcutPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Shortcut Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		~GuiDialogShortcutPreferences();
	
};

#endif //__guiDialogShortcutPreferences__
