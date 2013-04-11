///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiPanelActSaveTranslation__
#define __guiPanelActSaveTranslation__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/filepicker.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelActSaveTranslation
///////////////////////////////////////////////////////////////////////////////
class GuiPanelActSaveTranslation : public wxPanel 
{
	private:
	
	protected:
		wxChoice* _choiceLanguageSource;
		wxChoice* _choiceLanguageOfTranslation;
		wxFilePickerCtrl* _filePickerFile;
		wxRadioButton* _radioBtnSaveAllTranslations;
		wxRadioButton* _radioBtnSaveATranslation;
		wxCheckBox* _checkBoxNoDoublon;
		wxCheckBox* _checkBoxShowDialog;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoiceSrc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceTo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiPanelActSaveTranslation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActSaveTranslation();
	
};

#endif //__guiPanelActSaveTranslation__
