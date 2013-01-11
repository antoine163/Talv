///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogPreferences__
#define __guiDialogPreferences__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/propgrid/propgrid.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogPreferences
///////////////////////////////////////////////////////////////////////////////
class GuiDialogPreferences : public wxDialog 
{
	private:
	
	protected:
		wxPanel* _panelGeneral;
		wxStaticText* _staticTextSartup;
		wxCheckBox* _checkBoxShowMenu;
		wxStaticText* _staticTextShutdown;
		wxToggleButton* _toggleBtnTurnOff;
		wxPanel* _panelShortcut;
		wxPropertyGrid* _propertyGridShortcut;
		wxButton* _buttonDelete;
		wxButton* _buttonAdd;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickAdd( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT );
		~GuiDialogPreferences();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogChoiceShortcut
///////////////////////////////////////////////////////////////////////////////
class GuiDialogChoiceShortcut : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* _staticTextChoisShortcut;
		wxStdDialogButtonSizer* _sdbSizer;
		wxButton* _sdbSizerOK;
		wxButton* _sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnKeyUp( wxKeyEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogChoiceShortcut( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Choice your shortcut"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,80 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GuiDialogChoiceShortcut();
	
};

#endif //__guiDialogPreferences__
