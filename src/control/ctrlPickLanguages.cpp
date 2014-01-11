//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.01.2014
//!
//! ****************************************************************************

//App
#include "control/ctrlPickLanguages.hpp"
#include "manager/manGeneral.hpp"
#include "staticBox.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>


// *****************************************************************************
// Class CtrlPickLanguages
// *****************************************************************************

CtrlPickLanguages::CtrlPickLanguages(wxWindow* parent)
: wxWindow(parent, wxID_ANY)
{		
	//Créations des chois pour les wxChoice.
	wxArrayString languages = ManGeneral::get().getLanguages();
	
	//Créations du StaticBox
	StaticBox* staticBoxPickLanguages = new StaticBox(this, wxID_ANY, _("Pick languages:"));
	wxStaticText* staticTextLgsrc = 	new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("Translate language:")); 
	_choiceLgsrc = 						new wxChoice(		staticBoxPickLanguages, wxID_ANY, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0));
	wxStaticText* staticTextLgto = 		new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("to language:")); 
	_choiceLgto = 						new wxChoice(		staticBoxPickLanguages, wxID_ANY, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0));

	
	//Mise en forme avec des sizers.
	wxFlexGridSizer* flexGridSizerPickLanguages = new wxFlexGridSizer(2, 2, 0, 0);
	flexGridSizerPickLanguages->AddGrowableCol(1, 1);
	flexGridSizerPickLanguages->Add(staticTextLgsrc, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerPickLanguages->Add(_choiceLgsrc, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	flexGridSizerPickLanguages->Add(staticTextLgto, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerPickLanguages->Add(_choiceLgto, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	staticBoxPickLanguages->SetSizer(flexGridSizerPickLanguages);	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxPickLanguages, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, SIZE_BORDER);		
	SetSizer(sizerMain);
}

CtrlPickLanguages::~CtrlPickLanguages()
{
}