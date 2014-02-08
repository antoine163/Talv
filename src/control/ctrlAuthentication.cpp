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
#include "utils.hpp"

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
		
	////Mise en forme avec un sizer.
	//wxSizer* sizerUsername = new wxBoxSizer(wxHORIZONTAL);
	//sizerUsername->Add(staticTextUsername, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	//sizerUsername->Add(_textCtrlUsername, 	1, wxEXPAND|wxALIGN_CENTER_VERTICAL);	
	
	//Créations du chant password.
	wxStaticText* staticTextPassword = new wxStaticText(this, wxID_ANY, _("Password:"));
	_textCtrlPassword = new wxTextCtrl(this, wxID_ANY, password, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	wxToggleButton* toggleButtonShow = new wxToggleButton(this, wxID_ANY, _("Show"));
		
	//Mise en forme de _textCtrlPassword et toggleButtonShow dans un sizer.
	wxSizer* sizerPassword = new wxBoxSizer(wxHORIZONTAL);
	sizerPassword->Add(_textCtrlPassword, 	1, wxALIGN_CENTER_VERTICAL|wxRIGHT, SIZE_BORDER);	
	sizerPassword->Add(toggleButtonShow, 	0, wxALIGN_CENTER_VERTICAL|wxEXPAND);	
	
	//Mise en forme du GUI avec un sizer.
	wxFlexGridSizer* sizerMain = new wxFlexGridSizer(2, 2, SIZE_BORDER, SIZE_BORDER);
	sizerMain->AddGrowableCol(1, 1); 
	sizerMain->Add(staticTextUsername, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);	
	sizerMain->Add(_textCtrlUsername, 	1, wxALIGN_CENTER_VERTICAL|wxEXPAND);
	sizerMain->Add(staticTextPassword, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);	
	sizerMain->Add(sizerPassword, 		1, wxALIGN_CENTER_VERTICAL|wxEXPAND);
	SetSizer(sizerMain);
	
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

bool CtrlAuthentication::Enable(bool enable)
{
	enableWindowsFromSizer(GetSizer(), enable);
	return true;
}

void CtrlAuthentication::onToggleButtonShow(wxCommandEvent& event)
{
	if(event.IsChecked())
		_textCtrlPassword->SetWindowStyleFlag(0);
	else
		_textCtrlPassword->SetWindowStyleFlag(wxTE_PASSWORD);
}
