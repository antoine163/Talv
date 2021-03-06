//! \file **********************************************************************
//! \brief Header Gestion réseau
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 08.12.2013
//!
//! ****************************************************************************

//App
#include "manager/manNetwork.hpp"
#include "manager/manNotification.hpp"
#include "defs.hpp"
#include "utils.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/utils.h> 
#include <wx/sstream.h>
#include <wx/log.h> 
#include <wx/msgdlg.h>
#include <wx/statbox.h>

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
	_useProxy = useProxy;
}

ProxyInfo ManNetwork::getProxyInfoManual()const
{
	return _proxyInfoManual;
}

void ManNetwork::setProxyInfoManual(ProxyInfo const& proxy)
{
	_proxyInfoManual = proxy;
}

WinManager* ManNetwork::newEditWindow(wxWindow* parent)
{
	return new WinManNetwork(parent);
}

wxURLError ManNetwork::downloadFromUrlToString(wxString const& url, wxString* ptrString)
{
	wxURL _url(url);
	
	//On installe le proxy.
	switch(_useProxy)
	{
		case USE_PROXY_NO:
		_url.SetProxy(wxEmptyString);
		break;
		case USE_PROXY_SYSTEM:
		//wxLogError("Proxy: %s", getProxyInfoSystem());
		_url.SetProxy(getProxyInfoSystem());
		break;
		//case USE_PROXY_AUTO_DETECT:
		//break;
		case USE_PROXY_MANUAL:
		//wxLogError("Proxy: %s", _proxyInfoManual.toString());
		_url.SetProxy(_proxyInfoManual.toString());
		break;
	}
	
	//Erreur au niveau de l'url ?
	if (_url.GetError() != wxURL_NOERR)
	{
		showError(_url.GetError(), url);
		return _url.GetError();
	}
		
	//3s de Timeout
	_url.GetProtocol().SetDefaultTimeout(3);
	
	//Récupère le string.
	wxInputStream *inputStreamFromUrl = _url.GetInputStream();
	if (_url.GetError() != wxURL_NOERR)
	{
		showError(_url.GetError(), url);
		return _url.GetError();
	}
	
	wxStringOutputStream stringOutputStream(ptrString);
	inputStreamFromUrl->Read(stringOutputStream);
	delete inputStreamFromUrl;
	
	if (_url.GetError() != wxURL_NOERR)
		showError(_url.GetError(), url);
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

void ManNetwork::showError(wxURLError err, wxString const& url)const
{
	wxString mess;
	switch(err)
	{
		case wxURL_SNTXERR:
		wxLogError("Syntax error from the URL: %s", url);
		break;
		case wxURL_NOPROTO:
		wxLogError("Found no protocol which can get the URL: %s", url);
		break;
		case wxURL_NOHOST:
		wxLogError("A host name is required for the protocol from the URL: %s", url);
		mess = _("No access to internet.");
		break;
		case wxURL_NOPATH:
		wxLogError("A path is required for the protocol from the URL: %s", url);
		break;
		case wxURL_CONNERR:
		wxLogError("Connection error, URL: %s");
		break;
		case wxURL_PROTOERR:
		wxLogError("A path is required for the protocol from the URL: %s", url);
		mess = _("Bad connection or bad configuration.");
		break;
		default:
		break;
	}
	
	switch(_showError)
	{
		case SHOW_ERROR_NO:
		break;
		case SHOW_ERROR_IN_NOTIFICATION:
		ManNotification::get().notify(_("Network error"), mess, wxICON_ERROR);
		break;
		case SHOW_ERROR_IN_DIALOG:
		wxMessageDialog dlg(nullptr, mess, _("Network error"), wxOK|wxICON_ERROR|wxCENTRE);
		dlg.ShowModal();
		break;
	}
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
	StaticBox* staticBoxProxySetting = 		new StaticBox(this, wxID_ANY, _("Proxy setting:"));
	_radioButtonProxyNo = 					new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("No proxy (direct internet)"));
	_radioButtonProxySystem = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use system proxy setting"));
	//_radioButtonProxyAutoDetect = 		new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Auto-detect proxy setting"));
	_radioButtonProxyManual = 				new wxRadioButton(staticBoxProxySetting, 	wxID_ANY, _("Use manual proxy setting"));
	
	//Mise en forme des buttons radios avec un sizer.
	wxSizer* sizerProxy = new wxBoxSizer(wxVERTICAL);
	sizerProxy->Add(_radioButtonProxyNo,			0, wxEXPAND,	SIZE_BORDER);	
	sizerProxy->Add(_radioButtonProxySystem, 		0, wxEXPAND, 	SIZE_BORDER);	
	//sizerProxy->Add(_radioButtonProxyAutoDetect, 	0, wxEXPAND, 	SIZE_BORDER);	
	sizerProxy->Add(_radioButtonProxyManual, 		0, wxEXPAND,	SIZE_BORDER);
	staticBoxProxySetting->SetSizer(sizerProxy);
	
	//Créations des buttons radios pour afficher les erreurs.
	StaticBox* staticBoxShowError = 		new StaticBox(this, wxID_ANY, _("Show error in:"));
	_radioButtonShowErrorNo = 				new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Nothing"));
	_radioButtonShowErrorInNotification = 	new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Notification"));
	_radioButtonShowErrorInDialog = 		new wxRadioButton(staticBoxShowError, 	wxID_ANY, _("Dialog"));
	
	//Mise en forme dans un sizer
	wxSizer* sizerShowError = new wxBoxSizer(wxVERTICAL);
	sizerShowError->Add(_radioButtonShowErrorNo,			0, wxEXPAND,	SIZE_BORDER);	
	sizerShowError->Add(_radioButtonShowErrorInNotification,0, wxEXPAND, 	SIZE_BORDER);	
	sizerShowError->Add(_radioButtonShowErrorInDialog, 		0, wxEXPAND,	SIZE_BORDER);
	staticBoxShowError->SetSizer(sizerShowError);
	
	//Mise en forme des StaticBox dans un sizer.
	wxBoxSizer* sizerProxyAndShowError = new wxBoxSizer(wxHORIZONTAL);
	sizerProxyAndShowError->Add(staticBoxProxySetting, 1, wxRIGHT, SIZE_BORDER);
	sizerProxyAndShowError->Add(staticBoxShowError, 1);
	
	//Créations du contrôle ProxyInfo
	_staticBoxProxyManual = new StaticBox(this, wxID_ANY, _("Manual proxy setting:"));
	_ctrlProxyInfoProxyManual = new CtrlProxyInfo(_staticBoxProxyManual);
	
	//Mise en forme dans un sizer
	wxSizer* sizerCtrlProxyInfoProxyManual = new wxBoxSizer(wxVERTICAL);
	sizerCtrlProxyInfoProxyManual->Add(_ctrlProxyInfoProxyManual, 0, wxEXPAND);
	_staticBoxProxyManual->SetSizer(sizerCtrlProxyInfoProxyManual);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerProxyAndShowError,			0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 			SIZE_BORDER);	
	sizerMain->Add(_staticBoxProxyManual, 			0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
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
			//_staticBoxProxyManual->Enable(false);
		//break;
		case USE_PROXY_MANUAL:
			_radioButtonProxyManual->SetValue(true);
			_staticBoxProxyManual->Enable(true);
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
		_staticBoxProxyManual->Enable(true);
	else
		_staticBoxProxyManual->Enable(false);
}

