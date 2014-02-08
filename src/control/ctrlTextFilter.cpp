//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

//App
#include "control/ctrlTextFilter.hpp"
#include "staticBox.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class CtrlTextFilter
// *****************************************************************************

CtrlTextFilter::CtrlTextFilter(wxWindow* parent, TextFilter const& filter)
: wxWindow(parent, wxID_ANY)
{
	//Création du _spinCtrlWeight
	wxStaticText* staticTextWeight = new wxStaticText(this, wxID_ANY, _("Weight:"));
	_spinCtrlWeight = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 0);
	
	//Mise en forme dans un sizer.
	wxSizer* sizerWeight = new wxBoxSizer(wxHORIZONTAL);
	sizerWeight->Add(staticTextWeight, 	0, wxALIGN_CENTER_HORIZONTAL|wxRIGHT, 	SIZE_BORDER);
	sizerWeight->Add(_spinCtrlWeight, 	1, wxALIGN_CENTER_HORIZONTAL);
	
	//Création des CheckBoxs
	StaticBox* staticBoxKnowledge = new StaticBox(this, wxID_ANY, _("Knowledge:"));
	_checkBoxUnknown = new wxCheckBox(staticBoxKnowledge, wxID_ANY, _("Unknown"));
	_checkBoxLittleKnown = new wxCheckBox(staticBoxKnowledge, wxID_ANY, _("Little known"));
	_checkBoxKnown = new wxCheckBox(staticBoxKnowledge, wxID_ANY, _("Known"));
	_checkBoxVeryKnown = new wxCheckBox(staticBoxKnowledge, wxID_ANY, _("Very known"));
	
	//Mise en forme dans un sizer.
	wxFlexGridSizer* flexGridSizerKnowledge = new wxFlexGridSizer(2, 2, SIZE_BORDER, SIZE_BORDER);
	flexGridSizerKnowledge->Add(_checkBoxUnknown, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerKnowledge->Add(_checkBoxLittleKnown, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerKnowledge->Add(_checkBoxKnown, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerKnowledge->Add(_checkBoxVeryKnown, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	staticBoxKnowledge->SetSizer(flexGridSizerKnowledge);
	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerWeight, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP|wxBOTTOM, 	SIZE_BORDER);
	sizerMain->Add(staticBoxKnowledge, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	SetSizer(sizerMain);
	
	setFilter(filter);
}

CtrlTextFilter::~CtrlTextFilter()
{
}

void CtrlTextFilter::setFilter(TextFilter const& filter)
{
	_spinCtrlWeight->SetValue((int)filter.getWeight());
	
	_checkBoxUnknown->SetValue(filter.getKnowledge()&KNOWLEDGE_UNKNOWN);
	_checkBoxLittleKnown->SetValue(filter.getKnowledge()&KNOWLEDGE_LITTLE_KNOWN);
	_checkBoxKnown->SetValue(filter.getKnowledge()&KNOWLEDGE_KNOWN);
	_checkBoxVeryKnown->SetValue(filter.getKnowledge()&KNOWLEDGE_VERY_KNOWN);
}

TextFilter CtrlTextFilter::getFilter()
{
	TextFilter tmpTextFilter;
	
	tmpTextFilter.setWeight((unsigned int)_spinCtrlWeight->GetValue());
	
	Knowledge_e tmpKnowledge = (Knowledge_e)0;
	if(_checkBoxUnknown->GetValue())
		tmpKnowledge |= KNOWLEDGE_UNKNOWN;
		
	if(_checkBoxLittleKnown->GetValue())
		tmpKnowledge |= KNOWLEDGE_LITTLE_KNOWN;
		
	if(_checkBoxKnown->GetValue())
		tmpKnowledge |= KNOWLEDGE_KNOWN;
		
	if(_checkBoxVeryKnown->GetValue())
		tmpKnowledge |= KNOWLEDGE_VERY_KNOWN;
	
	return tmpTextFilter;
}
