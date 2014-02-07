//! \file **********************************************************************
//! \brief Source Dialogue pour choisie la traduction principale d'un texte.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 06.02.2014
//!
//! ****************************************************************************

//App
#include "dialog/dlgPickTranslation.hpp"
#include "manager/manGeneral.hpp"
#include "staticBox.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class DlgPickTranslation
// *****************************************************************************

DlgPickTranslation::DlgPickTranslation(wxWindow* parent, wxString const& text, DataText const& translations)
: 	wxDialog(parent, wxID_ANY, _("Pick translation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{		
	//Icônes
	SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_16X16));
	
	//Créations 
	wxStaticText* staticTextPickTranslation = new wxStaticText(this, wxID_ANY, _("Pick translation:"));
	_textCtrlTranslation = new wxTextCtrl(this, wxID_ANY, translations.getMainTranslation());
	
	wxSizer* sizerPickTranslation = new wxBoxSizer(wxHORIZONTAL);
	sizerPickTranslation->Add(staticTextPickTranslation,0, 	wxALIGN_CENTER_VERTICAL|wxRIGHT,	SIZE_BORDER);
	sizerPickTranslation->Add(_textCtrlTranslation, 	1, 	wxALIGN_CENTER_VERTICAL, 			SIZE_BORDER);
	
	//Créations des boutons.
	wxWindow* winContainer = new wxWindow(this, wxID_ANY);
	wxSizer* sizerContainer = new wxBoxSizer(wxHORIZONTAL);
	
	auto tmpTranslations = translations.getTranslations();
	for(auto itn: tmpTranslations)
	{
		StaticBox* staticBoxNature = new StaticBox(winContainer, wxID_ANY, itn.first+':');
		wxSizer* sizerNature = new wxBoxSizer(wxVERTICAL);
		for(auto itw: itn.second)
		{
			wxButton* button = new wxButton(staticBoxNature, wxID_ANY, itw, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT|wxBU_LEFT|wxBORDER_NONE);
			sizerNature->Add(button, 0, wxEXPAND);
		}
		staticBoxNature->SetSizer(sizerNature);
		sizerContainer->Add(staticBoxNature, 1, wxEXPAND|wxLEFT|wxRIGHT, SIZE_BORDER);
	}
	winContainer->SetSizer(sizerContainer);
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = CreateButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerPickTranslation, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(winContainer, 			1, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM,		SIZE_BORDER);
	sizerMain->Add(staticLine, 				0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 				0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	SetSizerAndFit(sizerMain);
	Center();
	
	Bind(wxEVT_BUTTON, &DlgPickTranslation::onButton, this);
}

DlgPickTranslation::~DlgPickTranslation()
{
	Unbind(wxEVT_BUTTON, &DlgPickTranslation::onButton, this);
}

wxString DlgPickTranslation::getTranslation()
{
	return _textCtrlTranslation->GetValue();
}

void DlgPickTranslation::onButton(wxCommandEvent& event)
{
	if(event.GetId() == wxID_CANCEL || event.GetId() == wxID_OK)
		event.Skip();
	else
	{
		//On récupère le bouton qui a générer l'événement.
		wxButton const* button = static_cast<wxButton const*>(event.GetEventObject());
		
		//On récupère le label du bouton.
		_textCtrlTranslation->SetValue(button->GetLabel());
		
		//On quitte le dialogue
		EndModal(wxID_OK);
	}
}

