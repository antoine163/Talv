//! \file **************************************************************
//! \brief Source Action de dire du texte.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 25.04.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actSay.hpp"
#include "resource.hpp"
#include "notification.hpp"

//TEST 
#include <iostream>

// *********************************************************************
// Class PanelActSay
// *********************************************************************

PanelActSay::PanelActSay(wxWindow* parent, wxButton* buttonOK, ActSay* act)
: GuiPanelActSay(parent), _act(act), _buttonOK(buttonOK)
{
	std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	//Ajout des langues.
	for(auto &it: languages)
	{
		_choice->Append(it.second);
	}

	//Sélectionne la bonne langue.
	int n = _choice->FindString(languages.at(_act->_lgsrc));
	_choice->SetSelection(n);
	
	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSay::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActSay::~PanelActSay()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSay::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActSay::OnOKButtonClick(wxCommandEvent& event)
{
	//Affect le langage source.
	int n = _choice->GetSelection();
	wxString s = _choice->GetString(n);
	_act->_lgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	//Propage l'événement.
	event.Skip();
}

// *********************************************************************
// Class ActSay
// *********************************************************************

ActSay::ActSay()
: ActSay("en")
{
}

ActSay::ActSay(wxString const& lgsrc)
: Action(_("Say a text"), "ActSay", _("Say a text with google."))
{
	_lgsrc = lgsrc;
}

ActSay::~ActSay()
{
}
		
void ActSay::execute()
{
	//On récupère le contenue de la presse papier.
	wxString clipboard = Resource::getClipboard();
	
	//La presse papier est t'elle vide ?
	if(clipboard.IsEmpty())
	{
		//Pas de texte à traduire
		Notification::getInstance()->notify(_("Translate clipboard"), _("Sorry, nothing at translate."));
		return;
	}
	
	//On dit le texte
	Resource::getInstance()->Tts(clipboard, _lgsrc);
}

wxPanel* ActSay::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActSay(parent, buttonOK, this);
}

wxString ActSay::getStringPreferences()const
{
	return wxString::Format(_("Say a text in %s"), Resource::getInstance()->abbreviationToLanguage(_lgsrc));
}

void ActSay::actLoad(wxFileConfig& fileConfig)
{
	fileConfig.Read("lgsrc", &_lgsrc);
}

void ActSay::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("lgsrc", _lgsrc);
}
