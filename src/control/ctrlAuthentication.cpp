//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.12.2013
//!
//! ****************************************************************************

//App
#include "control/ctrlAuthentication.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class CtrlAuthentication
// *****************************************************************************

CtrlAuthentication::CtrlAuthentication(	wxWindow* parent,
										wxString const& username,
										wxString const& password,
										long style)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style)
{
	//Créations du chant username.
	wxStaticText* staticTextUsername = new wxStaticText(this, wxID_ANY, _("Username:"));
	_textCtrlUsername = new wxTextCtrl(this, wxID_ANY, username);
		
	//Mise en forme avec un sizer.
	wxSizer* sizerUsername = new wxBoxSizer(wxHORIZONTAL);
	sizerUsername->Add(staticTextUsername, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerUsername->Add(_textCtrlUsername, 	1, wxEXPAND|wxALIGN_CENTER_VERTICAL);	
	
	//Créations du chant password.
	wxStaticText* staticTextPassword = new wxStaticText(this, wxID_ANY, _("Password:"));
	_textCtrlPassword = new wxTextCtrl(this, wxID_ANY, password, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	wxToggleButton* toggleButtonShow = new wxToggleButton(this, wxID_ANY, _("Show"));
		
	//Mise en forme avec un sizer.
	wxSizer* sizerPassword = new wxBoxSizer(wxHORIZONTAL);
	sizerPassword->Add(staticTextPassword, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 			2*SIZE_BORDER);	
	sizerPassword->Add(_textCtrlPassword, 	1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxRIGHT, 	2*SIZE_BORDER);	
	sizerPassword->Add(toggleButtonShow, 	0, wxEXPAND|wxALIGN_CENTER_VERTICAL);	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerUsername, 0, wxEXPAND|wxBOTTOM|wxLEFT|wxRIGHT|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(sizerPassword, 0, wxEXPAND|wxBOTTOM|wxLEFT|wxRIGHT, 			SIZE_BORDER);	
	SetSizerAndFit(sizerMain);
	
	//Bind
	Bind(wxEVT_TOGGLEBUTTON, &CtrlAuthentication::onToggleButtonShow, this);
}

CtrlAuthentication::~CtrlAuthentication()
{
	//Unbind
	Unbind(wxEVT_TOGGLEBUTTON, &CtrlAuthentication::onToggleButtonShow, this);
}

wxString CtrlAuthentication::getUsername()const
{
	return _textCtrlUsername->GetValue();
}

void CtrlAuthentication::setUsername(wxString const& username)
{
	_textCtrlUsername->SetValue(username);
}
		
wxString CtrlAuthentication::getPassword()const
{
	return _textCtrlPassword->GetValue();
}

void CtrlAuthentication::setPassword(wxString const& password)
{
	_textCtrlPassword->SetValue(password);
}

void CtrlAuthentication::onToggleButtonShow(wxCommandEvent& event)
{
	if(event.IsChecked())
		_textCtrlPassword->SetWindowStyleFlag(0);
	else
		_textCtrlPassword->SetWindowStyleFlag(wxTE_PASSWORD);
}
