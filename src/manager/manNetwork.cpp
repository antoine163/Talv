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

//App
#include "manager/manNetwork.hpp"

// *****************************************************************************
// Class ManNetwork
// *****************************************************************************

ManNetwork::ManNetwork()
{
}

ManNetwork::~ManNetwork()
{
}

IMPLEMENT_MANAGER(ManNetwork);

wxWindow* ManNetwork::newEditWindow(wxWindow* parent)
{
	return new WinManNetwork(parent);
}

void ManNetwork::manLoad(wxFileConfig&)
{
}

void ManNetwork::manSave(wxFileConfig&)const
{
}

// *****************************************************************************
// Class WinManNetwork
// *****************************************************************************

WinManNetwork::WinManNetwork(wxWindow* parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Network"))
{
	//Mise en forme du GUI avec des sizer.
	//wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	//mainSizer->Add(_controlDataList, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);
	//mainSizer->Add(buttonsSizer, 	 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);	
	//SetSizer(mainSizer);
}

WinManNetwork::~WinManNetwork()
{
}
