///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiPanelActLearn__
#define __guiPanelActLearn__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelActLearn
///////////////////////////////////////////////////////////////////////////////
class GuiPanelActLearn : public wxPanel 
{
	private:
	
	protected:
		wxChoice* _choiceList;
		wxSpinCtrl* _spinCtrlNbText;
	
	public:
		
		GuiPanelActLearn( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActLearn();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogActLearn
///////////////////////////////////////////////////////////////////////////////
class GuiDialogActLearn : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* _staticTextInfo;
		wxStaticText* _staticTextPropose;
		wxStaticText* _staticTextAnswer;
		wxButton* _buttonTextPropose;
		wxTextCtrl* _textCtrlAnswer;
		wxChoice* _choiceKnowledge;
		wxButton* _buttonDelete;
		
		wxButton* _buttonCancel;
		wxButton* _buttonCheck;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickPropose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextAnswer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextEnterAnswer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceKnowledge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCheck( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogActLearn( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Learn text"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		~GuiDialogActLearn();
	
};

#endif //__guiPanelActLearn__
