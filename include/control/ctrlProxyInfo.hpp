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

#ifndef CTRL_PROXY_INFO_H
#define CTRL_PROXY_INFO_H

//App
#include "proxyInfo.hpp"
#include "staticBox.hpp"
#include "control/ctrlAuthentication.hpp"

//WxWidgets
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>

// *****************************************************************************
// Class CtrlProxyInfo
// *****************************************************************************

class CtrlProxyInfo : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlProxyInfo(	wxWindow* parent,
						ProxyInfo const& proxy = ProxyInfo(),
						long style = 0);
		//! \brief Destructeur.
		virtual ~CtrlProxyInfo();
		
		void setProxyInfo(ProxyInfo const& proxyInfo);
		ProxyInfo getProxyInfo();
		
		bool Enable(bool enable = true);

	private:
		wxTextCtrl* _textCtrlProxy;
		wxSpinCtrl* _spinCtrlPort;
		StaticBox* _staticBoxAuthentication;

		CtrlAuthentication* _ctrlAuthentication;
};

#endif //CTRL_PROXY_INFO_H
