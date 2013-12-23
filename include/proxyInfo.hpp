//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.12.2013
//!
//! ****************************************************************************

#ifndef PROXY_INFO_H
#define PROXY_INFO_H

//WxWidgets
#include <wx/string.h>

// *****************************************************************************
// Class ProxyInfo
// *****************************************************************************

class ProxyInfo
{	
	public:
		ProxyInfo(	wxString const& proxy = wxEmptyString,
					int port = 80,
					bool useAuthentication = false,
					wxString const& username = wxEmptyString,
					wxString const& password = wxEmptyString);
		~ProxyInfo();
		
		wxString getProxy()const;
		void setProxy(wxString const& proxy);
		int getPort()const;
		void setPort(int port);
		
		bool AuthenticationIsUsed()const;
		void useAuthentication(bool use = true);
		
		wxString getUsername()const;
		void setUsername(wxString const& username);
		wxString getPassword()const;
		void setPassword(wxString const& password);
		
		wxString toString()const;
	
	private:
		wxString _proxy;
		int _port;
		bool _useAuthentication;
		wxString _username;
		wxString _password;
};

#endif //PROXY_INFO_H
