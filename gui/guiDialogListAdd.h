///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogListAdd__
#define __guiDialogListAdd__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogListAdd
///////////////////////////////////////////////////////////////////////////////
class GuiDialogListAdd : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* _textCtrlName;
		wxStaticText* m_staticText9;
		wxChoice* _choiceLanguageSource;
		wxStaticText* m_staticText11;
		wxChoice* _choiceLanguageOfTranslation;
		wxStdDialogButtonSizer* _sdbSizer;
		wxButton* _sdbSizerOK;
		wxButton* _sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogListAdd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("List Add"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GuiDialogListAdd();
	
};

#endif //__guiDialogListAdd__
