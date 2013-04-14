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
#include <wx/menu.h>
#include <wx/listctrl.h>
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
		wxStaticText* _staticTextSetting;
		wxCheckBox* _checkBoxShowMenu;
		wxStaticText* _staticTextShutdown;
		wxToggleButton* _toggleBtnTurnOff;
		wxPanel* _panelShortcut;
		wxListCtrl* _listCtrlAction;
		wxMenu* _menuListAction;
		wxMenuItem* _menuItemListAdd;
		wxMenuItem* _menuItemListPreferences;
		wxMenuItem* _menuItemListDelete;
		wxButton* _buttonActDelete;
		wxButton* _buttonActPreferences;
		wxButton* _buttonActAdd;
		wxStdDialogButtonSizer* _sdbSizer;
		wxButton* _sdbSizerOK;
		wxButton* _sdbSizerApply;
		wxButton* _sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnListItemDeselectedAction( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemSelectedAction( wxListEvent& event ) { event.Skip(); }
		virtual void OnButtonClickActAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickActPreferences( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickActDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickApply( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GuiDialogPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT );
		~GuiDialogPreferences();
		
		void _listCtrlActionOnContextMenu( wxMouseEvent &event )
		{
			_listCtrlAction->PopupMenu( _menuListAction, event.GetPosition() );
		}
	
};

#endif //__guiDialogPreferences__
