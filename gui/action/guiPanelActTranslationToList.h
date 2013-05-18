///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiPanelActTranslationToList__
#define __guiPanelActTranslationToList__

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
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GuiPanelActTranslationToList
///////////////////////////////////////////////////////////////////////////////
class GuiPanelActTranslationToList : public wxPanel 
{
	private:
	
	protected:
		wxChoice* _choiceLanguageSource;
		wxChoice* _choiceLanguageOfTranslation;
		wxComboBox* _comboBoxList;
		wxCheckBox* _checkBoxShowDialog;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoiceSrc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceTo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiPanelActTranslationToList( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~GuiPanelActTranslationToList();
	
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

#endif //__guiPanelActTranslationToList__
