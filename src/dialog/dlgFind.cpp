//! \file **********************************************************************
//! \brief Source Dialogue de rechercher.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 05.02.2014
//!
//! ****************************************************************************

//App
#include "dialog/dlgFind.hpp"
#include "defs.hpp"
#include "manager/manGeneral.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>

// *****************************************************************************
// Class DlgFind
// *****************************************************************************

//! \todo vérifier l'utilité de SetIcon
DlgFind::DlgFind(wxWindow* parent, wxString const& title, wxArrayString const& choicesAutoComplete)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{		
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Création du textCtrlFind
	_textCtrlFind = new wxTextCtrl(this, wxID_ANY);
	_textCtrlFind->AutoComplete(choicesAutoComplete);
	wxStaticText* staticTextFind = new wxStaticText(this, wxID_ANY, _("Search for:"));
	
	//Mise en fore avec un sizer
	wxSizer* sizerFind = new wxBoxSizer(wxHORIZONTAL);
	sizerFind->Add(staticTextFind, 	0, 	wxALIGN_CENTER_VERTICAL|wxRIGHT,	SIZE_BORDER);
	sizerFind->Add(_textCtrlFind, 	1, 	wxALIGN_CENTER_VERTICAL,			SIZE_BORDER);
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerFind, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(staticLine, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	SetSizerAndFit(sizerMain);
	Center();
	
	_textCtrlFind->SetFocus();
}

DlgFind::~DlgFind()
{
}

wxString DlgFind::getValue()
{
	return _textCtrlFind->GetValue();
}
