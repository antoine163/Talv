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
#include "control/ctrlProxyInfo.hpp"

//WxWidgets
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
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
// Class ManNetwork
// *****************************************************************************

//! \ingroup manager
//! \brief ManNetwork
class ManNetwork : public Manager
{
	DECLARE_MANAGER(ManNetwork);
	
	public:
		//use Proxy
		UseProxy_e getUseProxy()const;
		void setUseProxy(UseProxy_e useProxy);
		
		//Proxy
		ProxyInfo getProxyInfoManual()const;
		void setProxyInfoManual(ProxyInfo const& proxy);

		//Le contenue de l'url doit être coder en utf-8
		wxURLError downloadFromUrlToStringl(wxString const& url, wxString* pString);
				
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:	
		wxString getProxyInfoSystem()const;
	
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		UseProxy_e _useProxy;
		ProxyInfo _proxyInfoManual;
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
		void onRadioButtonProxy(wxCommandEvent& event);
		
		wxRadioButton* _radioButtonProxyNo;
		wxRadioButton* _radioButtonProxySystem; 
		//wxRadioButton* _radioButtonProxyAutoDetect;
		wxRadioButton* _radioButtonProxyManual;
		
		wxRadioButton* _radioButtonShowErrorNo;
		wxRadioButton* _radioButtonShowErrorInNotification; 
		wxRadioButton* _radioButtonShowErrorInDialog;
		
		wxStaticBox* _staticBoxProxyManual;
		CtrlProxyInfo* _ctrlProxyInfoProxyManual;
};

#endif //MAN_NETWORK_H
