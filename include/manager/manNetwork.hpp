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
		UseProxy_e getUseProxy();
		void setUseProxy(UseProxy_e useProxy);
		
		//Proxy
		ProxyInfo getProxyInfoManual();
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
		
		wxRadioButton* _radioButtonProxyNo;
		wxRadioButton* _radioButtonProxySystem; 
		//wxRadioButton* _radioButtonProxyAutoDetect;
		wxRadioButton* _radioButtonProxyManual;
		
		CtrlProxyInfo* _ctrlProxyInfoProxyManual;
};

#endif //MAN_NETWORK_H
