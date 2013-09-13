///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiFrameNotification__
#define __guiFrameNotification__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiFrameNotification
///////////////////////////////////////////////////////////////////////////////
class GuiFrameNotification : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* _staticTextTitle;
		wxStaticText* _staticTextMessage;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiFrameNotification( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxNO_BORDER );
		~GuiFrameNotification();
	
};

#endif //__guiFrameNotification__
