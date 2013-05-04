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
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

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
		wxTextCtrl* _textCtrlList;
		wxRadioButton* _radioBtnSaveAllTranslations;
		wxRadioButton* _radioBtnSaveATranslation;
		wxCheckBox* _checkBoxShowDialog;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoiceSrc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceTo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiPanelActSaveTranslation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActSaveTranslation();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GuiDialogPickMainTranslation
///////////////////////////////////////////////////////////////////////////////
class GuiDialogPickMainTranslation : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* _staticText;
		wxButton* _buttonMainTranslation;
		wxBoxSizer* _bSizerTranslation;
	
	public:
		
		GuiDialogPickMainTranslation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Pick a main translation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~GuiDialogPickMainTranslation();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelTranslation
///////////////////////////////////////////////////////////////////////////////
class GuiPanelTranslation : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* _staticTextKind;
		wxBoxSizer* _bSizerTranslation;
	
	public:
		
		GuiPanelTranslation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelTranslation();
	
};

#endif //__guiPanelActSaveTranslation__
