//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.12.2013
//!
//! ****************************************************************************

//App
#include "control/ctrlProxyInfo.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class CtrlProxyInfo
// *****************************************************************************

CtrlProxyInfo::CtrlProxyInfo(	wxWindow* parent,
								ProxyInfo const& proxy,
								long style)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style)
{
	//Créations du wxTextCtrl pour entré le non du proxy et du wxSpinCtrl pour
	//entrées le numéro du port.
	wxStaticText* staticTextProxy = new wxStaticText(	this, wxID_ANY, _("Proxy:"));
	_textCtrlProxy =				new wxTextCtrl(		this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1));
	wxStaticText* staticTextPort = 	new wxStaticText(	this, wxID_ANY, _("Port:"));
	_spinCtrlPort = 				new wxSpinCtrl(		this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999);

	//Mise en forme avec un sizer.
	wxSizer* sizerProxyAndPort = new wxBoxSizer(wxHORIZONTAL);
	sizerProxyAndPort->Add(staticTextProxy, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, SIZE_BORDER);	
	sizerProxyAndPort->Add(_textCtrlProxy, 		1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerProxyAndPort->Add(staticTextPort, 		0, wxALIGN_CENTER_VERTICAL|wxRIGHT, SIZE_BORDER);	
	sizerProxyAndPort->Add(_spinCtrlPort,		0, wxALIGN_CENTER_VERTICAL);
	
	//Créations wxCheckBox et du CtrlAuthentication
	_checkBoxUseAuthentication = 	new wxCheckBox(			this, wxID_ANY, _("Use authentication:"));
	_ctrlAuthentication = 			new CtrlAuthentication(	this, wxEmptyString, wxEmptyString, wxBORDER_SUNKEN);
	_ctrlAuthentication->Enable(false);
	
	//Mise en forme avec des sizers.
	wxSizer* sizerAuthentication = new wxBoxSizer(wxVERTICAL);
	sizerAuthentication->Add(_checkBoxUseAuthentication, 	0, wxEXPAND|wxBOTTOM, 	SIZE_BORDER);
	sizerAuthentication->Add(_ctrlAuthentication, 			0, wxEXPAND|wxLEFT, 	8*SIZE_BORDER);
	
	wxSizer* sizerAuthenticationMargin = new wxBoxSizer(wxHORIZONTAL);
	sizerAuthenticationMargin->AddSpacer(8*SIZE_BORDER);
	sizerAuthenticationMargin->Add(sizerAuthentication, 1);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerProxyAndPort, 			0, wxEXPAND|wxBOTTOM|wxLEFT|wxRIGHT|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(sizerAuthenticationMargin, 	0, wxEXPAND|wxBOTTOM|wxLEFT|wxRIGHT, 		SIZE_BORDER);	
	SetSizerAndFit(sizerMain);
	
	//Bind
	_checkBoxUseAuthentication->Bind(wxEVT_CHECKBOX, &CtrlProxyInfo::onCheckBoxUseAuthentication, this);
	
	setProxyInfo(proxy);
}

CtrlProxyInfo::~CtrlProxyInfo()
{
	//Unbind
	_checkBoxUseAuthentication->Unbind(wxEVT_CHECKBOX, &CtrlProxyInfo::onCheckBoxUseAuthentication, this);
}

void CtrlProxyInfo::setProxyInfo(ProxyInfo const& proxyInfo)
{
	_textCtrlProxy->SetValue(proxyInfo.getProxy());
	_spinCtrlPort->SetValue(proxyInfo.getPort());
	_checkBoxUseAuthentication->SetValue(proxyInfo.AuthenticationIsUsed());
	wxCommandEvent event(wxEVT_CHECKBOX);
	onCheckBoxUseAuthentication(event);
	
	_ctrlAuthentication->setUsername(proxyInfo.getUsername());
	_ctrlAuthentication->setPassword(proxyInfo.getPassword());
}

ProxyInfo CtrlProxyInfo::getProxyInfo()
{	
	return ProxyInfo(	_textCtrlProxy->GetValue(),
						_spinCtrlPort->GetValue(),
						_checkBoxUseAuthentication->GetValue(),
						_ctrlAuthentication->getUsername(),
						_ctrlAuthentication->getPassword());
}

void CtrlProxyInfo::onCheckBoxUseAuthentication(wxCommandEvent&)
{
	if(_checkBoxUseAuthentication->IsChecked())
		_ctrlAuthentication->Enable();
	else
		_ctrlAuthentication->Enable(false);
}
		