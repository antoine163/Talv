///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
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
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
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
		wxCheckBox* _checkBoxTime;
		wxPanel* _panelTime;
		wxSpinCtrl* _spinCtrlHours;
		wxSpinCtrl* _spinCtrlMinutes;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiPanelActLearn( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActLearn();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl1;
		wxStaticLine* m_staticline1;
		wxStaticLine* m_staticline2;
		wxButton* m_button1;
		wxButton* m_button2;
	
	public:
		
		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~MyDialog1();
	
};

#endif //__guiPanelActLearn__
