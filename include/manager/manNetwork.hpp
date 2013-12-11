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

#ifndef MAN_NETWORK_H
#define MAN_NETWORK_H

//App
#include "manager.hpp"
#include "control/ctrlAuthentication.hpp"

//WxWidgets
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/url.h>

// *****************************************************************************
// Enum UseProxy_e
// *****************************************************************************
enum UseProxy_e
{
	USE_PROXY_NO,
	USE_PROXY_SYSTEM,
	USE_PROXY_AUTO_DETECT,
	USE_PROXY_MANUAL
};

// *****************************************************************************
// Class ProxyInfo
// *****************************************************************************

//! \brief ProxyInfo
class ProxyInfo
{	
	public:
		ProxyInfo(	wxString const& proxy = wxEmptyString,
					int port = 80,
					wxString const& username = wxEmptyString,
					wxString const& password = wxEmptyString);
		~ProxyInfo();
		
		wxString getProxy()const;
		void setProxy(wxString const& proxy);
		int getPort()const;
		void setPort(int port);
		
		wxString getUsername()const;
		void setUsername(wxString const& username);
		wxString getPassword()const;
		void setPassword(wxString const& password);
	
	private:
		wxString _proxy;
		int _port;
		wxString _username;
		wxString _password;
};

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup manager
//! \brief ManNetwork
class ManNetwork : public Manager
{
	DECLARE_MANAGER(ManNetwork);
	
	public:
		//use Proxy
		UseProxy_e getUseProxy();
		void setUseProxy(UseProxy_e useProxy);
		
		//Proxy
		//ProxyInfo getProxyInfoManual();
		//void setProxyInfoManual(ProxyInfo const& proxy);
		//ProxyInfo getProxyInfoCourent();
		//void setProxyInfoCurrent(ProxyInfo const& proxy);

		
		//wxURLError download(wxMemoryBuffer* buffer, wxString const& url);
		
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:	
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		UseProxy_e _useProxy;
		wxURL _url;
};

// *****************************************************************************
// Class WinManNetwork
// *****************************************************************************

//! \brief WinManNetwork
class WinManNetwork : public WinManager
{
	public:
		WinManNetwork(wxWindow* parent);
		~WinManNetwork();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onButtonManualProxy(wxCommandEvent& event);
		void onCheckBoxUseAuthentication(wxCommandEvent& event);
		
		wxRadioButton* _radioButtonNoProxy;
		wxRadioButton* _radioButtonSystemProxy; 
		wxRadioButton* _radioButtonAutoDetectProxy;
		wxRadioButton* _radioButtonManualProxy;
		
		wxTextCtrl* _textCtrlProxy;
		wxSpinCtrl* _spinCtrlProxyPort;
		wxCheckBox* _checkBoxUseAuthentication;

		wxWindow* _windowManualProxy;
		CtrlAuthentication* _ctrlAuthentication;
};

#endif //MAN_NETWORK_H
