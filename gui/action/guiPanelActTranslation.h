///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiPanelActTranslation__
#define __guiPanelActTranslation__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelActTranslation
///////////////////////////////////////////////////////////////////////////////
class GuiPanelActTranslation : public wxPanel 
{
	private:
	
	protected:
		wxChoice* _choiceLanguageSource;
		wxChoice* _choiceLanguageOfTranslation;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoiceSrc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceTo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiPanelActTranslation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActTranslation();
	
};

#endif //__guiPanelActTranslation__
