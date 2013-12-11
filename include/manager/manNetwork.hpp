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

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup manager
//! \brief ManNetwork
class ManNetwork : public Manager
{
	DECLARE_MANAGER(ManNetwork);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

// *****************************************************************************
// Class WinManNetwork
// *****************************************************************************

//! \brief WinManNetwork
class WinManNetwork : public wxWindow
{
	public:
		WinManNetwork(wxWindow* parent);
		~WinManNetwork();
	
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
