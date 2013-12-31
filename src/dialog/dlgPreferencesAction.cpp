//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 31.12.2013
//!
//! ****************************************************************************

//App
#include "dialog/dlgPreferencesAction.hpp"
#include "action.hpp"
#include "manager/manGeneral.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/settings.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class DlgPreferencesAction
// *****************************************************************************

DlgPreferencesAction::DlgPreferencesAction(wxWindow* parent)
: 	wxDialog(parent, wxID_ANY, _("Preferences action"), wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{		
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Création de la listbook.
	_listbook = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_LEFT);
	
	std::vector<Action*> allActions = Action::createAllActions();
	for(auto it: allActions)
	{
		_listbook->AddPage(it->newEditWindow(_listbook), it->getName());
	}
	
	//Création du wxStaticText.
	wxStaticText* staticTextShortcut = new wxStaticText(this, wxID_ANY, _("Pick your shortcut:"));
	//Création du CtrlPickShortcutKey
	_ctrlPickShortcutKey = new CtrlPickShortcutKey(this);
	
	//Mise en forme dans un sizer.
	wxSizer* sizerShortcut = new wxBoxSizer(wxHORIZONTAL);
	sizerShortcut->Add(staticTextShortcut,		0, 	wxALIGN_CENTER_VERTICAL|wxRIGHT, 		2*SIZE_BORDER);
	sizerShortcut->Add(_ctrlPickShortcutKey, 	1, 	wxEXPAND);
	
	//Création de deux statice line.
	wxStaticLine* staticLine1 = new wxStaticLine(this);
	wxStaticLine* staticLine2 = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerShortcut,	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(staticLine1,		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(_listbook, 		1, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(staticLine2,		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	SetSizerAndFit(sizerMain);
	
	//Bind des boutons
	Bind(wxEVT_BUTTON, &DlgPreferencesAction::onButtonClickCancel, 	this, wxID_CANCEL);
	Bind(wxEVT_BUTTON, &DlgPreferencesAction::onButtonClickOK, 		this, wxID_OK);
	
	//_notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DlgPreferences::onNotebookChanged, this);
	//Bind(wxEVT_CLOSE_WINDOW, &DlgPreferences::onClose, this);

	Centre();
}

DlgPreferencesAction::~DlgPreferencesAction()
{
	//Unbind des boutons
	Unbind(wxEVT_BUTTON, &DlgPreferencesAction::onButtonClickCancel, 	this, wxID_CANCEL);
	Unbind(wxEVT_BUTTON, &DlgPreferencesAction::onButtonClickOK, 		this, wxID_OK);
	
	//_notebook->Unbind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DlgPreferences::onNotebookChanged, this);
	//Unbind(wxEVT_CLOSE_WINDOW, &DlgPreferences::onClose, this);
}

void DlgPreferencesAction::onListbookChanged(wxBookCtrlEvent&)
{
	//if(_windowActive != nullptr)
		//static_cast<WinManager*>(_windowActive)->refreshManagerFromGui();
	
	//_windowActive = _notebook->GetCurrentPage();
	//static_cast<WinManager*>(_windowActive)->refreshGuiFromManager();
}

void DlgPreferencesAction::onClose(wxCloseEvent& event)
{
	//Manager::loadManagers();
	event.Skip();
}

void DlgPreferencesAction::onButtonClickCancel(wxCommandEvent& event)
{
	event.Skip();
}

void DlgPreferencesAction::onButtonClickOK(wxCommandEvent& event)
{
	//static_cast<WinManager*>(_windowActive)->refreshManagerFromGui();
	//Manager::saveManagers();
	event.Skip();
}
		
