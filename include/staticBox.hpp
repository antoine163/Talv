//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.01.2014
//!
//! ****************************************************************************

#ifndef STATIC_BOX_H
#define STATIC_BOX_H

//WxWidgets
#include <wx/window.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>


// *****************************************************************************
// Class StaticBox
// *****************************************************************************

class StaticBox : public wxWindow
{	
	public:
		StaticBox(	wxWindow *parent,
					wxWindowID id,
					const wxString &label,
					bool withCheckBox=false,
					const wxPoint &pos=wxDefaultPosition,
					const wxSize &size=wxDefaultSize,
					long style=0,
					const wxString &name="StaticBox");
		virtual ~StaticBox();
		
		bool IsChecked();
		void setChecked(bool val);
		
		void SetSizer(wxSizer* sizer, bool deleteOld = true);
		bool Enable(bool enable = true);
		
	private:
		void onClick(wxMouseEvent& event);
		void onCheck(wxCommandEvent& event);
		
		wxSizer* _sizerMain;
		wxSizer* _sizerWork;
		wxSizer* _sizerLabel;
		wxCheckBox * _checkBox;
		wxStaticText* _staticText;
};

#endif //STATIC_BOX_H
