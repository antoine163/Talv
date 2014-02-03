//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
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
: CtrlPickLanguages(parent, wxLANGUAGE_ENGLISH, wxLANGUAGE_FRENCH)
{
	wxLanguage lgto;
	wxLanguage lgsrc;
	
	lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	lgto == wxLANGUAGE_ENGLISH)
		lgsrc = wxLANGUAGE_FRENCH;
	else
		lgsrc = wxLANGUAGE_ENGLISH;
		
	setLanguages(lgsrc, lgto);
}

CtrlPickLanguages::CtrlPickLanguages(	wxWindow* parent,
										wxLanguage lgsrc,
										wxLanguage lgto)
: wxWindow(parent, wxID_ANY)
{
	//Créations des chois pour les wxChoice.
	wxArrayString languages = ManGeneral::get().getLanguages();
	
	//Créations du StaticBox
	StaticBox* staticBoxPickLanguages = new StaticBox(this, wxID_ANY, _("Pick languages:"));
	wxStaticText* staticTextLgsrc = 	new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("Translate language:")); 
	_comboBoxLgsrc = 					new wxComboBox(		staticBoxPickLanguages, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0), wxCB_SORT|wxCB_READONLY);
	_comboBoxLgsrc->AutoComplete(languages);
	wxStaticText* staticTextLgto = 		new wxStaticText(	staticBoxPickLanguages, wxID_ANY, _("to language:")); 
	_comboBoxLgto = 					new wxComboBox(		staticBoxPickLanguages, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, languages.GetCount(), &languages.Item(0), wxCB_SORT|wxCB_READONLY);
	_comboBoxLgto->AutoComplete(languages);
	
	//Mise en forme avec des sizers.
	wxFlexGridSizer* flexGridSizerPickLanguages = new wxFlexGridSizer(2, 2, SIZE_BORDER, SIZE_BORDER);
	flexGridSizerPickLanguages->AddGrowableCol(1, 1);
	flexGridSizerPickLanguages->Add(staticTextLgsrc, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerPickLanguages->Add(_comboBoxLgsrc, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	flexGridSizerPickLanguages->Add(staticTextLgto, 	0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerPickLanguages->Add(_comboBoxLgto, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	staticBoxPickLanguages->SetSizer(flexGridSizerPickLanguages);	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxPickLanguages, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, SIZE_BORDER);		
	SetSizer(sizerMain);
	
	setLanguages(lgsrc, lgto);
}

CtrlPickLanguages::~CtrlPickLanguages()
{
}

void CtrlPickLanguages::getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const
{
	*lgsrc = (wxLanguage)wxLocale::FindLanguageInfo(_comboBoxLgsrc->GetValue())->Language;
	*lgto = (wxLanguage)wxLocale::FindLanguageInfo(_comboBoxLgto->GetValue())->Language;
}

void CtrlPickLanguages::setLanguages(wxLanguage lgsrc, wxLanguage lgto)
{
	_comboBoxLgsrc->SetSelection(_comboBoxLgsrc->FindString(wxLocale::GetLanguageName(lgsrc)));
	_comboBoxLgto->SetSelection(_comboBoxLgto->FindString(wxLocale::GetLanguageName(lgto)));
}
