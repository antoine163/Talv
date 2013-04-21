///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogNotification__
#define __guiDialogNotification__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogNotification
///////////////////////////////////////////////////////////////////////////////
class GuiDialogNotification : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* _staticTextTitle;
		wxStaticText* _staticTextMessage;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogNotification( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDIALOG_NO_PARENT|wxSTAY_ON_TOP|wxNO_BORDER );
		~GuiDialogNotification();
	
};

#endif //__guiDialogNotification__
