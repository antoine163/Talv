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

#ifndef MAN_NETWORK_H
#define MAN_NETWORK_H

//App
#include "manager.hpp"
#include "staticBox.hpp"
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
	//USE_PROXY_AUTO_DETECT,
	USE_PROXY_MANUAL
};

// *****************************************************************************
// Enum ShowError_e
// *****************************************************************************
enum ShowError_e
{
	SHOW_ERROR_NO,
	SHOW_ERROR_IN_NOTIFICATION,
	SHOW_ERROR_IN_DIALOG
};

// *****************************************************************************
// Class ManNetwork
// *****************************************************************************

//! \ingroup manager
//! \brief ManNetwork
//! \todo Ajouter le mode auto détecte pour le proxy.
class ManNetwork : public Manager
{
	DECLARE_MANAGER(ManNetwork);
	
	public:
		//Show error
		ShowError_e getShowError()const;
		void setShowError(ShowError_e showError);
		
		//use Proxy
		UseProxy_e getUseProxy()const;
		void setUseProxy(UseProxy_e useProxy);
		
		//Proxy
		ProxyInfo getProxyInfoManual()const;
		void setProxyInfoManual(ProxyInfo const& proxy);

		//Le contenue de l'url doit être coder en utf-8
		wxURLError downloadFromUrlToString(wxString const& url, wxString* ptrString);
				
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:	
		wxString getProxyInfoSystem()const;
		void showError(wxURLError err, wxString const& url)const;
	
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		ShowError_e _showError;
		UseProxy_e _useProxy;
		ProxyInfo _proxyInfoManual;
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
		
		StaticBox* _staticBoxProxyManual;
		CtrlProxyInfo* _ctrlProxyInfoProxyManual;
};

#endif //MAN_NETWORK_H
