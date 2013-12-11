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
: _useProxy(USE_PROXY_NO)
{
}

ManNetwork::~ManNetwork()
{
}

IMPLEMENT_MANAGER(ManNetwork);

UseProxy_e ManNetwork::getUseProxy()
{
	return _useProxy;
}

void ManNetwork::setUseProxy(UseProxy_e useProxy)
{
	_useProxy = useProxy;
	switch(_useProxy)
	{
		case USE_PROXY_NO:
		break;
		case USE_PROXY_SYSTEM:
		break;
		case USE_PROXY_AUTO_DETECT:
		break;
		case USE_PROXY_MANUAL:
		break;
	}
}

ProxyInfo ManNetwork::getProxyInfoManual()
{
	return ProxyInfo(	"mai2008@enib",
						2324,
						true,
						"a9maleyr",
						"kth4369iz");
}

WinManager* ManNetwork::newEditWindow(wxWindow* parent)
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
: WinManager(parent, _("Network"))
{
	//Créations des buttons radios.
	wxStaticBox* staticBoxProxySetting = 	new wxStaticBox(this, 						wxID_ANY, _("Proxy setting"));
	_radioButtonProxyNo = 					new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("No proxy (direct internet)"));
	_radioButtonProxySystem = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use system proxy setting"));
	//_radioButtonProxyAutoDetect = 		new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Auto-detect proxy setting"));
	_radioButtonProxyManual = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use manual proxy setting:"));
	
	//Créations du contrôle ProxyInfo
	_ctrlProxyInfoProxyManual = new CtrlProxyInfo(staticBoxProxySetting, ProxyInfo(), wxBORDER_SUNKEN);
	_ctrlProxyInfoProxyManual->Enable(false);
	
	//Mise en forme dans un sizer
	wxSizer* sizerCtrlProxyInfoProxyManual = new wxBoxSizer(wxHORIZONTAL);
	sizerCtrlProxyInfoProxyManual->AddSpacer(8*SIZE_BORDER);
	sizerCtrlProxyInfoProxyManual->Add(_ctrlProxyInfoProxyManual, 1, wxRIGHT, SIZE_BORDER);
	
	//Mise en forme des buttons radios et du sizerCtrlProxyInfoProxyManual avec un sizer.
	wxSizer* proxySizer = new wxBoxSizer(wxVERTICAL);
	proxySizer->Add(_radioButtonProxyNo,			0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);	
	proxySizer->Add(_radioButtonProxySystem, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	//proxySizer->Add(_radioButtonProxyAutoDetect, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	proxySizer->Add(_radioButtonProxyManual, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	proxySizer->Add(sizerCtrlProxyInfoProxyManual, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	staticBoxProxySetting->SetSizer(proxySizer);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxProxySetting, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, SIZE_BORDER);	
	SetSizer(sizerMain);
	
	//Bind
	Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
	
	//mise a jour du gui depuis les données du manager.
	refreshGuiFromManager();
}

WinManNetwork::~WinManNetwork()
{
	//Unbind
	Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onButtonManualProxy, this);
}

void WinManNetwork::refreshGuiFromManager()
{
	_ctrlProxyInfoProxyManual->setProxyInfo(ManNetwork::get().getProxyInfoManual());
	
	wxCommandEvent event(wxEVT_CHECKBOX);
	onButtonManualProxy(event);
	
	////Sélection du radioButton
	//switch(ManNetwork::get().getUseProxy())
	//{
		//case USE_PROXY_NO:
			//_radioButtonNoProxy->SetValue(true);
		//break;
		//case USE_PROXY_SYSTEM:
			//_radioButtonSystemProxy->SetValue(true);
		//break;
		//case USE_PROXY_AUTO_DETECT:
			////_radioButtonAutoDetectProxy->SetValue(true);
		//break;
		//case USE_PROXY_MANUAL:
			//_radioButtonManualProxy->SetValue(true);
		//break;
	//}
}

void WinManNetwork::refreshManagerFromGui()const
{
}

void WinManNetwork::onButtonManualProxy(wxCommandEvent&)
{
	if(_radioButtonProxyManual->GetValue())
		_ctrlProxyInfoProxyManual->Enable();
	else
		_ctrlProxyInfoProxyManual->Enable(false);
}
