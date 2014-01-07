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
#include <wx/stattext.h>
#include <wx/utils.h> 
#include <wx/sstream.h>

// *****************************************************************************
// Class ManNetwork
// *****************************************************************************

ManNetwork::ManNetwork()
: _showError(SHOW_ERROR_IN_NOTIFICATION), _useProxy(USE_PROXY_NO)
{
}

ManNetwork::~ManNetwork()
{
}

IMPLEMENT_MANAGER(ManNetwork);

ShowError_e ManNetwork::getShowError()const
{
	return _showError;
}

void ManNetwork::setShowError(ShowError_e showError)
{
	_showError = showError;
}

UseProxy_e ManNetwork::getUseProxy()const
{
	return _useProxy;
}

void ManNetwork::setUseProxy(UseProxy_e useProxy)
{
	_url.SetURL(wxEmptyString);
	
	_useProxy = useProxy;
	switch(_useProxy)
	{
		case USE_PROXY_NO:
		_url.SetProxy(wxEmptyString);
		break;
		case USE_PROXY_SYSTEM:
		_url.SetProxy(getProxyInfoSystem());
		break;
		//case USE_PROXY_AUTO_DETECT:
		//break;
		case USE_PROXY_MANUAL:
		_url.SetProxy(_proxyInfoManual.toString());
		break;
	}
}

ProxyInfo ManNetwork::getProxyInfoManual()const
{
	return _proxyInfoManual;
}

void ManNetwork::setProxyInfoManual(ProxyInfo const& proxy)
{
	_proxyInfoManual = proxy;
	
	if(_useProxy == USE_PROXY_MANUAL)
	{
		_url.SetURL(wxEmptyString);
		_url.SetProxy(_proxyInfoManual.toString());
	}
}

WinManager* ManNetwork::newEditWindow(wxWindow* parent)
{
	return new WinManNetwork(parent);
}

//! \todo Afficher les erreurs.
wxURLError ManNetwork::downloadFromUrlToString(wxString const& url, wxString* ptrString)
{
	_url.SetURL(url);
	
	//Erreur au niveau de l'url ?
	if (_url.GetError() != wxURL_NOERR)
		return _url.GetError();
		
	//3s de Timeout
	_url.GetProtocol().SetTimeout(3);
	
	//Récupère le string.
	wxInputStream *inputStreamFromUrl = _url.GetInputStream();
	if (_url.GetError() != wxURL_NOERR)
		return _url.GetError();
	
	wxStringOutputStream stringOutputStream(ptrString);
	inputStreamFromUrl->Read(stringOutputStream);
	delete inputStreamFromUrl;
	
	return _url.GetError();
}

wxString ManNetwork::getProxyInfoSystem()const
{
	wxString proxy;
	
	if(!wxGetEnv("http_proxy", &proxy))
	{
		if(!wxGetEnv("HTTP_PROXY", &proxy))
			return wxEmptyString;
	}
		
	proxy.Replace("http://", wxEmptyString, false);
	proxy.Replace("/", wxEmptyString);
		
	return proxy;
}

void ManNetwork::manLoad(wxFileConfig& fileConfig)
{
	fileConfig.SetPath("proxyInfoManual/");
		_proxyInfoManual.setProxy(fileConfig.Read("proxy", wxEmptyString));
		_proxyInfoManual.setPort(fileConfig.ReadLong("port", (long)80));
		_proxyInfoManual.useAuthentication(fileConfig.ReadBool("useAuthentication", false));
		_proxyInfoManual.setUsername(fileConfig.Read("username", wxEmptyString));
		_proxyInfoManual.setPassword(fileConfig.Read("password", wxEmptyString));
	fileConfig.SetPath("..");
	
	setShowError((ShowError_e)fileConfig.ReadLong("showError", (long)SHOW_ERROR_IN_NOTIFICATION));
	setUseProxy((UseProxy_e)fileConfig.ReadLong("useProxy", (long)USE_PROXY_NO));
}

void ManNetwork::manSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("showError", (long)_showError);
	fileConfig.Write("useProxy", (long)_useProxy);
	
	fileConfig.SetPath("proxyInfoManual/");
		fileConfig.Write("proxy", _proxyInfoManual.getProxy());
		fileConfig.Write("port", (long)_proxyInfoManual.getPort());
		fileConfig.Write("useAuthentication", _proxyInfoManual.AuthenticationIsUsed());
		fileConfig.Write("username", _proxyInfoManual.getUsername());
		fileConfig.Write("password", _proxyInfoManual.getPassword());
	fileConfig.SetPath("..");
}

// *****************************************************************************
// Class WinManNetwork
// *****************************************************************************

WinManNetwork::WinManNetwork(wxWindow* parent)
: WinManager(parent, _("Network"))
{
	//Créations des buttons radios pour le proxy.
	wxStaticBox* staticBoxProxySetting = 	new wxStaticBox(this, wxID_ANY, _("Proxy setting:"));
	_radioButtonProxyNo = 					new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("No proxy (direct internet)"));
	_radioButtonProxySystem = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use system proxy setting"));
	//_radioButtonProxyAutoDetect = 		new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Auto-detect proxy setting"));
	_radioButtonProxyManual = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use manual proxy setting"));
	
	//Mise en forme des buttons radios avec un sizer.
	wxSizer* sizerProxy = new wxStaticBoxSizer(staticBoxProxySetting, wxVERTICAL);
	sizerProxy->Add(_radioButtonProxyNo,			0, wxEXPAND|wxRIGHT|wxLEFT|wxTOP,		SIZE_BORDER);	
	sizerProxy->Add(_radioButtonProxySystem, 		0, wxEXPAND|wxRIGHT|wxLEFT, 			SIZE_BORDER);	
	//sizerProxy->Add(_radioButtonProxyAutoDetect, 	0, wxEXPAND|wxRIGHT|wxLEFT, 			SIZE_BORDER);	
	sizerProxy->Add(_radioButtonProxyManual, 		0, wxEXPAND|wxRIGHT|wxLEFT|wxBOTTOM, 	SIZE_BORDER);	
	
	//Créations des buttons radios pour afficher les erreurs.
	wxStaticBox* staticBoxShowError = 		new wxStaticBox(this, wxID_ANY, _("Show error in:"));
	_radioButtonShowErrorNo = 				new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Nothing"));
	_radioButtonShowErrorInNotification = 	new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Notification"));
	_radioButtonShowErrorInDialog = 		new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Dialog"));
	
	//Mise en forme dans un sizer
	wxSizer* sizerShowError = new wxStaticBoxSizer(staticBoxShowError, wxVERTICAL);
	sizerShowError->Add(_radioButtonShowErrorNo,			0, wxEXPAND|wxRIGHT|wxLEFT|wxTOP,		SIZE_BORDER);	
	sizerShowError->Add(_radioButtonShowErrorInNotification,0, wxEXPAND|wxRIGHT|wxLEFT, 			SIZE_BORDER);	
	sizerShowError->Add(_radioButtonShowErrorInDialog, 		0, wxEXPAND|wxRIGHT|wxLEFT|wxBOTTOM, 	SIZE_BORDER);
	
	//Mise en forme des wxStaticBox dans un sizer.
	wxBoxSizer* sizerProxyAndShowError = new wxBoxSizer(wxHORIZONTAL);
	sizerProxyAndShowError->Add(sizerProxy, 1, wxRIGHT, SIZE_BORDER);
	sizerProxyAndShowError->Add(sizerShowError, 1);
	
	//Créations du contrôle ProxyInfo
	_staticBoxProxyManual = new wxStaticBox(this, wxID_ANY, _("Manual proxy setting:"));
	_ctrlProxyInfoProxyManual = new CtrlProxyInfo(_staticBoxProxyManual);
	_staticBoxProxyManual->Enable(false);
	
	//Mise en forme dans un sizer
	wxSizer* sizerCtrlProxyInfoProxyManual = new wxStaticBoxSizer(_staticBoxProxyManual, wxVERTICAL);
	sizerCtrlProxyInfoProxyManual->Add(_ctrlProxyInfoProxyManual, 0, wxEXPAND|wxRIGHT|wxLEFT|wxTOP|wxBOTTOM);		
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerProxyAndShowError,			0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 			SIZE_BORDER);	
	sizerMain->Add(sizerCtrlProxyInfoProxyManual, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	SetSizer(sizerMain);
	
	//Bind
	Bind(wxEVT_RADIOBUTTON, &WinManNetwork::onRadioButtonProxy, this);
}

WinManNetwork::~WinManNetwork()
{
	//Unbind
	Unbind(wxEVT_RADIOBUTTON, &WinManNetwork::onRadioButtonProxy, this);
}

void WinManNetwork::refreshGuiFromManager()
{
	_ctrlProxyInfoProxyManual->setProxyInfo(ManNetwork::get().getProxyInfoManual());
	
	//Sélection du radioButton du proxy
	switch(ManNetwork::get().getUseProxy())
	{
		case USE_PROXY_NO:
			_radioButtonProxyNo->SetValue(true);
			_staticBoxProxyManual->Enable(false);
		break;
		case USE_PROXY_SYSTEM:
			_radioButtonProxySystem->SetValue(true);
			_staticBoxProxyManual->Enable(false);
		break;
		//case USE_PROXY_AUTO_DETECT:
			//_radioButtonProxyAutoDetect->SetValue(true);
		//break;
		case USE_PROXY_MANUAL:
			_radioButtonProxyManual->SetValue(true);
			_staticBoxProxyManual->Enable();
		break;
	}
	
	//Sélection du radioButton des erreurs
	switch(ManNetwork::get().getShowError())
	{
		case SHOW_ERROR_NO:
			_radioButtonShowErrorNo->SetValue(true);
		break;
		case SHOW_ERROR_IN_NOTIFICATION:
			_radioButtonShowErrorInNotification->SetValue(true);
		break;
		case SHOW_ERROR_IN_DIALOG:
			_radioButtonShowErrorInDialog->SetValue(true);
		break;
	}
}

void WinManNetwork::refreshManagerFromGui()const
{
	ManNetwork::get().setProxyInfoManual(_ctrlProxyInfoProxyManual->getProxyInfo());
	
	//Quelle proxy utiliser ?
	if(_radioButtonProxyNo->GetValue())
		ManNetwork::get().setUseProxy(USE_PROXY_NO);
	else if(_radioButtonProxySystem->GetValue())
		ManNetwork::get().setUseProxy(USE_PROXY_SYSTEM);
	//else if(_radioButtonProxyAutoDetect->GetValue())
		//ManNetwork::get().setUseProxy(USE_PROXY_AUTO_DETECT);
	else if(_radioButtonProxyManual->GetValue())
		ManNetwork::get().setUseProxy(USE_PROXY_MANUAL);
		
	//les erreurs
	if(_radioButtonShowErrorNo->GetValue())
		ManNetwork::get().setShowError(SHOW_ERROR_NO);
	else if(_radioButtonShowErrorInNotification->GetValue())
		ManNetwork::get().setShowError(SHOW_ERROR_IN_NOTIFICATION);
	else if(_radioButtonShowErrorInDialog->GetValue())
		ManNetwork::get().setShowError(SHOW_ERROR_IN_DIALOG);
}

void WinManNetwork::onRadioButtonProxy(wxCommandEvent&)
{
	if(_radioButtonProxyManual->GetValue())
		_staticBoxProxyManual->Enable();
	else
		_staticBoxProxyManual->Enable(false);
}

