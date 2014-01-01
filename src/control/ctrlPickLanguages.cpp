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
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>


// *****************************************************************************
// Class CtrlPickLanguages
// *****************************************************************************

CtrlPickLanguages::CtrlPickLanguages(wxWindow* parent)
: wxWindow(parent, wxID_ANY)
{		
	//Créations des chois pour les wxChoice.
	wxArrayString languages = ManGeneral::get().GetLanguages();
	
	//Créations du wxStaticBox
	wxStaticBox* staticBoxPickLanguages = new wxStaticBox(this, wxID_ANY, _("Pick languages:"));
	wxStaticText* staticTextLgsrc = 	new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("Translate language:")); 
	_choiceLgsrc = 						new wxChoice(		staticBoxPickLanguages, wxID_ANY, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0));
	wxStaticText* staticTextLgto = 		new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("to language:")); 
	_choiceLgto = 						new wxChoice(		staticBoxPickLanguages, wxID_ANY, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0));

	
	//Mise en forme avec des sizers.
	wxSizer* sizerPickLanguages = new wxStaticBoxSizer(staticBoxPickLanguages, wxVERTICAL);
	wxSizer* flexGridSizerPickLanguages = new wxFlexGridSizer(2, 2, 0, 0);
	flexGridSizerPickLanguages->Add(staticTextLgsrc, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	flexGridSizerPickLanguages->Add(_choiceLgsrc, 		0, wxALIGN_CENTER_VERTICAL);	
	flexGridSizerPickLanguages->Add(staticTextLgto, 	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2*SIZE_BORDER);	
	flexGridSizerPickLanguages->Add(_choiceLgto, 		0, wxALIGN_CENTER_VERTICAL);	
	sizerPickLanguages->Add(flexGridSizerPickLanguages, 0, wxEXPAND);	
	
	SetSizer(sizerPickLanguages);
}

CtrlPickLanguages::~CtrlPickLanguages()
{
}