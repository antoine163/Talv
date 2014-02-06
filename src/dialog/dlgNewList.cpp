//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 03.02.2014
//!
//! ****************************************************************************

//App
#include "dialog/dlgNewList.hpp"
#include "control/ctrlPickLanguages.hpp"
#include "staticBox.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>

// *****************************************************************************
// Class DlgNewList
// *****************************************************************************

DlgNewList::DlgNewList(wxWindow* parent)
: DialogInlay(parent, _("New List"))
{		
	//Créations du chant du nouveau non de liste. 
	StaticBox* staticBoxNameList = new StaticBox(this, wxID_ANY, _("Entry a new list name:"));
	_textCtrlNameList = new wxTextCtrl(staticBoxNameList, wxID_ANY);
	
	//Mise en forme avec un sizer.
	wxSizer* sizerNameList = new wxBoxSizer(wxVERTICAL);
	sizerNameList->Add(_textCtrlNameList, 0, wxEXPAND|wxTOP, SIZE_BORDER);	
	staticBoxNameList->SetSizer(sizerNameList);
	
	//Créations du ctrlPickLanguages. 
	_ctrlPickLanguages = new CtrlPickLanguages(this);
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = createButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxNameList,	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxTOP,		SIZE_BORDER);
	sizerMain->Add(_ctrlPickLanguages,	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
	sizerMain->Add(staticLine,			0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
	sizerMain->Add(buttons, 			0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
	
	SetSizer(sizerMain);
	
	_textCtrlNameList->SetFocus();
}

DlgNewList::~DlgNewList()
{	
}

wxString DlgNewList::getNameList()const
{
	return _textCtrlNameList->GetValue();
}

void DlgNewList::getLanguages(wxLanguage *lgsrc, wxLanguage *lgto)const
{
	_ctrlPickLanguages->getLanguages(lgsrc, lgto);
}
		
