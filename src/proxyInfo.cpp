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
#include "proxyInfo.hpp"

// *****************************************************************************
// Class ProxyInfo
// *****************************************************************************

ProxyInfo::ProxyInfo(	wxString const& proxy, int port,
						bool useAuthentication,
						wxString const& username, wxString const& password)
: 	_proxy(proxy), _port(port),
	_useAuthentication(useAuthentication),
	_username(username), _password(password)
{
}

ProxyInfo::~ProxyInfo()
{
}

wxString ProxyInfo::getProxy()const
{
	return _proxy;
}

void ProxyInfo::setProxy(wxString const& proxy)
{
	_proxy = proxy;
}

int ProxyInfo::getPort()const
{
	return _port;
}

void ProxyInfo::setPort(int port)
{
	_port = port;
}

bool ProxyInfo::AuthenticationIsUsed()const
{
	return _useAuthentication;
}

void ProxyInfo::useAuthentication(bool use)
{
	_useAuthentication = use;
}

wxString ProxyInfo::getUsername()const
{
	return _username;
}

void ProxyInfo::setUsername(wxString const& username)
{
	_username = username;
}

wxString ProxyInfo::getPassword()const
{
	return _password;
}

void ProxyInfo::setPassword(wxString const& password)
{
	_password = password;
}

wxString ProxyInfo::toString()const
{
	wxString proxy;
	
	if(_useAuthentication)
	{
		proxy << _username;
		proxy << ':';
		proxy << _password;
		proxy << '@';
	}
	
	proxy << _proxy;
	proxy << ':';
	proxy << _port;
	
	return proxy;
}
