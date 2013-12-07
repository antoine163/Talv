//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 4.0
//! \date 02.01.2013
//!
//! ****************************************************************************

//App
#include "dialog/dialogPreferences.hpp"
#include "manager.hpp"
#include "manager/manGeneral.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/notebook.h>
#include <wx/bannerwindow.h>
#include <wx/statbmp.h>

// *****************************************************************************
// Class DialogPreferences
// *****************************************************************************

DialogPreferences::DialogPreferences()
: wxDialog(nullptr, wxID_ANY, _("Preferences"),
			wxDefaultPosition, wxDefaultSize,		wxDEFAULT_DIALOG_STYLE|
													wxRESIZE_BORDER|
													wxSTAY_ON_TOP|
													wxDIALOG_NO_PARENT)
{	
	//Désactivassions du menue dans la bar de notification.
	ManGeneral::get().enableTaskIcon(false);
	
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Création de la bannière.
	wxBannerWindow* banner = new wxBannerWindow(this, wxTOP);
	banner->SetText(PROJECT_NAME, _("Translation on the fly."));
	banner->SetGradient(wxColour(127, 127, 127, 127),
						wxColour(127, 127, 127, 0));	
	wxStaticBitmap* bitmapApp = new wxStaticBitmap(this, wxID_ANY, wxBitmap());
	bitmapApp->SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_32X32));
	
	//Ajout de l'icône
	wxSizer* bannerSizer = new wxBoxSizer(wxHORIZONTAL);
	bannerSizer->AddStretchSpacer(1);
	bannerSizer->Add(bitmapApp, 0, wxALIGN_CENTER_VERTICAL);
	banner->SetSizer(bannerSizer);
	
	//Création du notebook.
	wxNotebook* notebook = new wxNotebook(	this,
											wxID_ANY, 
											wxDefaultPosition,
											wxDefaultSize,
											wxNB_LEFT);
	for(auto it : Manager::getManagers())
	{
		wxWindow* tmpWindow = it->newEditWindow(notebook);
		if(tmpWindow != nullptr)
			notebook->AddPage(tmpWindow, tmpWindow->GetName());
	}
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxAPPLY|wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec des sizers.
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(banner, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	4);
	mainSizer->Add(notebook, 	1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		4);
	mainSizer->Add(staticLine, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM,		4);
	mainSizer->Add(buttons, 	0, wxEXPAND|wxBOTTOM, 						4);
	
	SetSizerAndFit(mainSizer);
	
	//Bind des boutons
	Bind(wxEVT_BUTTON, &DialogPreferences::onButtonClickApply, this, wxID_APPLY);
	Bind(wxEVT_BUTTON, &DialogPreferences::onButtonClickCancel, this, wxID_CANCEL);
	Bind(wxEVT_BUTTON, &DialogPreferences::onButtonClickOK, this, wxID_OK);
	
	Bind(wxEVT_CLOSE_WINDOW, &DialogPreferences::onClose, this);

	Centre();
}

DialogPreferences::~DialogPreferences()
{
	//Unbind des boutons
	Unbind(wxEVT_BUTTON, &DialogPreferences::onButtonClickApply, this, wxID_APPLY);
	Unbind(wxEVT_BUTTON, &DialogPreferences::onButtonClickCancel, this, wxID_CANCEL);
	Unbind(wxEVT_BUTTON, &DialogPreferences::onButtonClickOK, this, wxID_OK);
	
	Unbind(wxEVT_CLOSE_WINDOW, &DialogPreferences::onClose, this);
	
	//Activation du menue dans la bar de notification.
	ManGeneral::get().enableTaskIcon();
}

void DialogPreferences::onClose(wxCloseEvent&)
{
	Manager::loadManagers();
	Destroy();
}

void DialogPreferences::onButtonClickApply(wxCommandEvent&)
{
	Manager::saveManagers();
}

void DialogPreferences::onButtonClickCancel(wxCommandEvent&)
{
	Manager::loadManagers();
	Destroy();
}

void DialogPreferences::onButtonClickOK(wxCommandEvent&)
{
	Manager::saveManagers();
	Destroy();
}
		
