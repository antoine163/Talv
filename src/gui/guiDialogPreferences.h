///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  1 2012)
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
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/choice.h>

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
		wxStaticText* _staticTextShortcut;
		wxListCtrl* _listCtrlShortcut;
		wxButton* _buttonDelete;
		wxButton* _buttonSetting;
		
		wxButton* _buttonAdd;
		wxStdDialogButtonSizer* _sdbSizer;
		wxButton* _sdbSizerOK;
		wxButton* _sdbSizerApply;
		wxButton* _sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClickDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickSetting( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickAdd( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT );
		~GuiDialogPreferences();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogShurtcut
///////////////////////////////////////////////////////////////////////////////
class GuiDialogShurtcut : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* _staticTextShortcut;
		wxTextCtrl* _textCtrlShortcut;
		wxStaticText* _staticTextAction;
		wxChoice* _choiceAction;
		wxStaticText* _staticTextSetting;
		wxPanel* _panelSetting;
	
	public:
		
		GuiDialogShurtcut( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Shurtcut"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,200 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GuiDialogShurtcut();
	
};

#endif //__guiDialogPreferences__
