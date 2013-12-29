//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 02.01.2013
//!
//! ****************************************************************************

//App
#include "dialog/dlgPickShortcutKey.hpp"
#include "defs.hpp"
#include "manager/manGeneral.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>

// *****************************************************************************
// Class DlgPickShortcutKey
// *****************************************************************************

//! \todo vérifier l'utilité de SetIcon
DlgPickShortcutKey::DlgPickShortcutKey(wxWindow* parent, wxString const& title, ShortcutKey const& shortcutKey)
: 	wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{		
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Création du 
	_ctrlPickShortcutKey = new CtrlPickShortcutKey(this, shortcutKey);
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_ctrlPickShortcutKey, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(staticLine, 				0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 				0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	SetSizerAndFit(sizerMain);
	
	Center();
	
	SetFocus();
}

DlgPickShortcutKey::~DlgPickShortcutKey()
{
}

void DlgPickShortcutKey::setShortcutKey(ShortcutKey const& shortcutKey)
{
	_ctrlPickShortcutKey->setShortcutKey(shortcutKey);
}

ShortcutKey DlgPickShortcutKey::getShortcutKey()
{
	return _ctrlPickShortcutKey->getShortcutKey();
}

void DlgPickShortcutKey::SetFocus()
{
	_ctrlPickShortcutKey->SetFocus();
}
