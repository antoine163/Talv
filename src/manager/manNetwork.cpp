//! \file **********************************************************************
//! \brief Header Gestion réseau
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.12.2013
//!
//! ****************************************************************************

//App
#include "manager/manNetwork.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class ManNetwork
// *****************************************************************************

ManNetwork::ManNetwork()
{
}

ManNetwork::~ManNetwork()
{
}

IMPLEMENT_MANAGER(ManNetwork);

wxWindow* ManNetwork::newEditWindow(wxWindow* parent)
{
	return new WinManNetwork(parent);
}

void ManNetwork::manLoad(wxFileConfig&)
{
}

void ManNetwork::manSave(wxFileConfig&)const
{
}

// *****************************************************************************
// Class WinManNetwork
// *****************************************************************************

WinManNetwork::WinManNetwork(wxWindow* parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Network"))
{
	//Créations des buttons radios.
	wxStaticBox* staticBoxProxySetting = new wxStaticBox(this, wxID_ANY, _("Proxy setting"));
	_radioButtonNoProxy = 			new wxRadioButton(staticBoxProxySetting, wxID_ANY, _("No proxy (direct internet)"));
	_radioButtonSystemProxy = 		new wxRadioButton(staticBoxProxySetting, wxID_ANY, _("Use system proxy setting"));
	_radioButtonAutoDetectProxy = 	new wxRadioButton(staticBoxProxySetting, wxID_ANY, _("Auto-detect proxy setting"));
	_radioButtonManualProxy = 		new wxRadioButton(staticBoxProxySetting, wxID_ANY, _("Use manual proxy setting:"));
							
	//Créations du wxWindow pour la configuration manuel du proxy.
	_windowManualProxy = new wxWindow(staticBoxProxySetting, wxID_ANY);
	_windowManualProxy->Enable(false);
	wxStaticText* staticTextProxy = new wxStaticText(	_windowManualProxy, wxID_ANY, _("Proxy:"));
	_textCtrlProxy =				new wxTextCtrl(		_windowManualProxy, wxID_ANY);
	wxStaticText* staticTextPort = 	new wxStaticText(	_windowManualProxy, wxID_ANY, _("Port:"));
	_spinCtrlProxyPort = 			new wxSpinCtrl(		_windowManualProxy, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 80);
	_checkBoxUseAuthentication = 	new wxCheckBox(		_windowManualProxy, wxID_ANY, _("Use authentication:"));
	_ctrlAuthentication = new CtrlAuthentication(				_windowManualProxy);
	_ctrlAuthentication->Enable(false);

	//Mise en forme du _windowManualProxy avec des sizers.
	wxSizer* sizerManualProxyAndPort = new wxBoxSizer(wxHORIZONTAL);
	sizerManualProxyAndPort->Add(staticTextProxy, 		0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerManualProxyAndPort->Add(_textCtrlProxy, 		1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerManualProxyAndPort->Add(staticTextPort, 		0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	sizerManualProxyAndPort->Add(_spinCtrlProxyPort, 	0, wxALIGN_CENTER_VERTICAL);
	
	wxSizer* sizerManualProxyAuthentication = new wxBoxSizer(wxHORIZONTAL);
	sizerManualProxyAuthentication->AddSpacer(8*SIZE_BORDER);
	sizerManualProxyAuthentication->Add(_ctrlAuthentication, 1);
	
	wxSizer* sizerManualProxyMargin = new wxBoxSizer(wxVERTICAL);
	sizerManualProxyMargin->Add(sizerManualProxyAndPort, 		0, wxEXPAND|wxBOTTOM, SIZE_BORDER);			
	sizerManualProxyMargin->Add(_checkBoxUseAuthentication, 	0, wxEXPAND|wxBOTTOM, SIZE_BORDER);			
	sizerManualProxyMargin->Add(sizerManualProxyAuthentication, 0, wxEXPAND|wxBOTTOM, SIZE_BORDER);	
	
	wxSizer* sizerManualProxy = new wxBoxSizer(wxHORIZONTAL);
	sizerManualProxy->AddSpacer(8*SIZE_BORDER);
	sizerManualProxy->Add(sizerManualProxyMargin, 1, wxRIGHT, 2*SIZE_BORDER);
	_windowManualProxy->SetSizer(sizerManualProxy);
	
	//Mise en forme des buttons radios et du _windowManualProxy avec un sizer.
	wxSizer* proxySizer = new wxBoxSizer(wxVERTICAL);
	proxySizer->Add(_radioButtonNoProxy,			0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);	
	proxySizer->Add(_radioButtonSystemProxy, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	proxySizer->Add(_radioButtonAutoDetectProxy, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	proxySizer->Add(_radioButtonManualProxy, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	proxySizer->Add(_windowManualProxy, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	staticBoxProxySetting->SetSizer(proxySizer);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxProxySetting, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, SIZE_BORDER);	
	SetSizer(sizerMain);
	
	//Bind
	_radioButtonNoProxy->			Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonSystemProxy->		Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonAutoDetectProxy->	Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonManualProxy->		Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	
	_checkBoxUseAuthentication->	Bind(wxEVT_CHECKBOX, &WinManNetwork::onCheckBoxUseAuthentication, this);
}

WinManNetwork::~WinManNetwork()
{
	//Unbind
	_radioButtonNoProxy->			Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonSystemProxy->		Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonAutoDetectProxy->	Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	_radioButtonManualProxy->		Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	
	_checkBoxUseAuthentication->	Unbind(wxEVT_CHECKBOX, &WinManNetwork::onCheckBoxUseAuthentication, this);
}

void WinManNetwork::onButtonManualProxy(wxCommandEvent&)
{
	if(_radioButtonManualProxy->GetValue())
		_windowManualProxy->Enable();
	else
		_windowManualProxy->Enable(false);
}

void WinManNetwork::onCheckBoxUseAuthentication(wxCommandEvent& event)
{
	if(event.IsChecked())
		_ctrlAuthentication->Enable();
	else
		_ctrlAuthentication->Enable(false);
}
