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
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelActLearn
///////////////////////////////////////////////////////////////////////////////
class GuiPanelActLearn : public wxPanel 
{
	private:
	
	protected:
		wxChoice* _choiceList;
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

#endif //__guiPanelActLearn__
