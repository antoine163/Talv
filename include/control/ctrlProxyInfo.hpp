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
#define CTRL_PROXY_SETTING_H

//App
#include "proxyInfo.hpp"
#include "control/ctrlAuthentication.hpp"

//WxWidgets
#include <wx/window.h>
#include <wx/string.h>
#include <wx/checkbox.h>
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

	private:
		void onCheckBoxUseAuthentication(wxCommandEvent& event);
		
		
		wxTextCtrl* _textCtrlProxy;
		wxSpinCtrl* _spinCtrlPort;
		wxCheckBox* _checkBoxUseAuthentication;

		CtrlAuthentication* _ctrlAuthentication;
};

#endif //CTRL_PROXY_SETTING_H
