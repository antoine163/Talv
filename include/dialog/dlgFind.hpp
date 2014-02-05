//! \file **********************************************************************
//! \brief Header Dialogue de rechercher.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 05.02.2014
//!
//! ****************************************************************************

#ifndef DLG_FIND_H
#define DLG_FIND_H

//WxWidgets
#include <wx/dialog.h>
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>

// *****************************************************************************
// Class DlgFind
// *****************************************************************************

class DlgFind : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DlgFind(wxWindow* parent, wxString const& title, wxArrayString const& choicesAutoComplete = wxArrayString());
		//! \brief Destructeur.
		~DlgFind();
		
		wxString getValue();
		
	private:
		
		wxTextCtrl* _textCtrlFind;
};

#endif //DLG_FIND_H
