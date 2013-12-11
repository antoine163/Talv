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

CtrlAuthentication::CtrlAuthentication(wxWindow* parent)
: wxWindow(parent, wxID_ANY)
{
	//Créations du chant username.
	wxStaticText* staticTextUsername = new wxStaticText(this, wxID_ANY, _("Username:"));
	_textCtrlUsername = new wxTextCtrl(this, wxID_ANY);
		
	//Mise en forme avec un sizer.
	wxSizer* sizerUsername = new wxBoxSizer(wxHORIZONTAL);
	sizerUsername->Add(staticTextUsername, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerUsername->Add(_textCtrlUsername, 	1, wxEXPAND|wxALIGN_CENTER_VERTICAL);	
	
	//Créations du chant password.
	wxStaticText* staticTextPassword = new wxStaticText(this, wxID_ANY, _("Password:"));
	_textCtrlPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	_toggleButtonShow = new wxToggleButton(this, wxID_ANY, _("Show"));
		
	//Mise en forme avec un sizer.
	wxSizer* sizerPassword = new wxBoxSizer(wxHORIZONTAL);
	sizerPassword->Add(staticTextPassword, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerPassword->Add(_textCtrlPassword, 	1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerPassword->Add(_toggleButtonShow, 	0, wxEXPAND|wxALIGN_CENTER_VERTICAL);	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(sizerUsername, 0, wxEXPAND|wxBOTTOM, SIZE_BORDER);	
	mainSizer->Add(sizerPassword, 0, wxEXPAND);	
	SetSizer(mainSizer);
	
	//Bind
	_toggleButtonShow->Bind(wxEVT_TOGGLEBUTTON, &CtrlAuthentication::onToggleButtonShow, this);
}

CtrlAuthentication::~CtrlAuthentication()
{
	//Unbind
	_toggleButtonShow->Unbind(wxEVT_TOGGLEBUTTON, &CtrlAuthentication::onToggleButtonShow, this);
}

void CtrlAuthentication::onToggleButtonShow(wxCommandEvent&)
{
	if(_toggleButtonShow->GetValue())
		_textCtrlPassword->SetWindowStyleFlag(0);
	else
		_textCtrlPassword->SetWindowStyleFlag(wxTE_PASSWORD);
}
