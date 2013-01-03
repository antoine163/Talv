///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  1 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogPreferences__
#define __guiDialogPreferences__

#include <wx/intl.h>

#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/statline.h>
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
		wxPanel* _panelShortcut;
		wxListCtrl* m_listCtrl1;
		wxStaticLine* m_staticline1;
		
		wxButton* _buttonDelete;
		wxButton* _addShortCut;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Apply;
		wxButton* m_sdbSizer1Cancel;
	
	public:
		
		GuiDialogPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GuiDialogPreferences();
	
};

#endif //__guiDialogPreferences__
