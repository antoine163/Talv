//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.12.2013
//!
//! ****************************************************************************

#ifndef CTRL_AUTHENTICATION_H
#define CTRL_AUTHENTICATION_H

//WxWidgets
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>

// *****************************************************************************
// Class CtrlAuthentication
// *****************************************************************************

class CtrlAuthentication : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlAuthentication(	wxWindow* parent,
							wxString const& username = wxEmptyString,
							wxString const& password = wxEmptyString);
		//! \brief Destructeur.
		virtual ~CtrlAuthentication();
		
		wxString getUsername()const;
		void setUsername(wxString const& username);
		
		wxString getPassword()const;
		void setPassword(wxString const& password);

	private:
		void onToggleButtonShow(wxCommandEvent& event);
		
		wxTextCtrl* _textCtrlUsername;
		wxTextCtrl* _textCtrlPassword;
};

#endif //CTRL_AUTHENTICATION_H
