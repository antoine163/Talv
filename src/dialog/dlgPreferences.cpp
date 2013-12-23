//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 4.2
//! \date 02.01.2013
//!
//! ****************************************************************************

//App
#include "dialog/dlgPreferences.hpp"
#include "defs.hpp"
#include "manager.hpp"
#include "manager/manGeneral.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/bannerwindow.h>
#include <wx/statbmp.h>
#include <wx/settings.h>

// *****************************************************************************
// Class DlgPreferences
// *****************************************************************************

DlgPreferences::DlgPreferences()
: 	wxDialog(nullptr, wxID_ANY, _("Preferences"), wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxDIALOG_NO_PARENT),
	_windowActive(nullptr)
{	
	//Désactivassions du menue dans la bar de notification.
	ManGeneral::get().enableTaskIcon(false);
	
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Création de la bannière.
	wxBannerWindow* banner = new wxBannerWindow(this, wxTOP);
	banner->SetText(PROJECT_NAME, _("Translation on the fly."));
	banner->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));	
	wxStaticBitmap* bitmapApp = new wxStaticBitmap(this, wxID_ANY, wxBitmap());
	bitmapApp->SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_32X32));
	
	//Ajout de l'icône
	wxSizer* bannerSizer = new wxBoxSizer(wxHORIZONTAL);
	bannerSizer->AddStretchSpacer(1);
	bannerSizer->Add(bitmapApp, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, SIZE_BORDER);
	banner->SetSizer(bannerSizer);
	
	//Création du notebook.
	_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT);
	for(auto it : Manager::getManagers())
	{
		wxWindow* tmpWindow = it->newEditWindow(_notebook);
		if(tmpWindow != nullptr)
		{
			#ifdef DEV_RUN_START_PREFERENCES
			if(tmpWindow->GetName() == DEV_RUN_START_PREFERENCES)
				_notebook->AddPage(tmpWindow, tmpWindow->GetName(), true);
			else
			#endif
			_notebook->AddPage(tmpWindow, tmpWindow->GetName());	
		}
	}
	
	_windowActive = _notebook->GetCurrentPage();
	static_cast<WinManager*>(_windowActive)->refreshGuiFromManager();
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxAPPLY|wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(banner, 		0, 	wxEXPAND);
	sizerMain->Add(_notebook, 	1, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(staticLine, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	SetSizerAndFit(sizerMain);
	
	//Bind des boutons
	Bind(wxEVT_BUTTON, &DlgPreferences::onButtonClickApply,		this, wxID_APPLY);
	Bind(wxEVT_BUTTON, &DlgPreferences::onButtonClickCancel, 	this, wxID_CANCEL);
	Bind(wxEVT_BUTTON, &DlgPreferences::onButtonClickOK, 		this, wxID_OK);
	
	_notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DlgPreferences::onNotebookChanged, this);
	Bind(wxEVT_CLOSE_WINDOW, &DlgPreferences::onClose, this);

	Centre();
}

DlgPreferences::~DlgPreferences()
{
	//Unbind des boutons
	Unbind(wxEVT_BUTTON, &DlgPreferences::onButtonClickApply, 	this, wxID_APPLY);
	Unbind(wxEVT_BUTTON, &DlgPreferences::onButtonClickCancel, 	this, wxID_CANCEL);
	Unbind(wxEVT_BUTTON, &DlgPreferences::onButtonClickOK, 		this, wxID_OK);
	
	_notebook->Unbind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DlgPreferences::onNotebookChanged, this);
	Unbind(wxEVT_CLOSE_WINDOW, &DlgPreferences::onClose, this);
	
	//Activation du menue dans la bar de notification.
	ManGeneral::get().enableTaskIcon();
}

void DlgPreferences::onNotebookChanged(wxBookCtrlEvent&)
{
	if(_windowActive != nullptr)
		static_cast<WinManager*>(_windowActive)->refreshManagerFromGui();
	
	_windowActive = _notebook->GetCurrentPage();
	static_cast<WinManager*>(_windowActive)->refreshGuiFromManager();
}

void DlgPreferences::onClose(wxCloseEvent& event)
{
	Manager::loadManagers();
	event.Skip();
}

void DlgPreferences::onButtonClickApply(wxCommandEvent&)
{
	static_cast<WinManager*>(_windowActive)->refreshManagerFromGui();
	Manager::saveManagers();
}

void DlgPreferences::onButtonClickCancel(wxCommandEvent&)
{
	Close();
}

void DlgPreferences::onButtonClickOK(wxCommandEvent&)
{
	static_cast<WinManager*>(_windowActive)->refreshManagerFromGui();
	Manager::saveManagers();
	Close();
}
		
