//! \file **************************************************************
//! \brief Source Action de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
//! \date 17.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actTranslation.hpp"
#include "resource.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class PanelActTranslation
// *********************************************************************

PanelActTranslation::PanelActTranslation(wxWindow* parent, wxButton* buttonOK, ActTranslation * act)
: GuiPanelActTranslation(parent), _act(act), _buttonOK(buttonOK)
{
	std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	//Ajout des langues.
	for(auto &it: languages)
	{
		_choiceLanguageSource->Append(it.second);
		_choiceLanguageOfTranslation->Append(it.second);
	}

	//Sélectionne les bonnes langues.
	int n = _choiceLanguageSource->FindString(languages.at(_act->_lgsrc));
	_choiceLanguageSource->SetSelection(n);
	n = _choiceLanguageOfTranslation->FindString(languages.at(_act->_lgto));
	_choiceLanguageOfTranslation->SetSelection(n);
	
	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActTranslation::~PanelActTranslation()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActTranslation::OnOKButtonClick(wxCommandEvent& event)
{
	//Affect le langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	_act->_lgsrc = Resource::getInstance()->languageToAcronym(s);
	
	//Affect le langage de destination.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	_act->_lgto = Resource::getInstance()->languageToAcronym(s);
	
	//Propage l'événement.
	event.Skip();
}


// *********************************************************************
// Class ActTranslation
// *********************************************************************

//! \todo a implémenter avec les locales.
ActTranslation::ActTranslation()
: ActTranslation("en", "fr")
{
}

ActTranslation::ActTranslation(wxString const& lgsrc, wxString const& lgto)
: Action(_("Translation"), "ActTranslation",
_("Translation a word or a group words from google.")),
_lgsrc(lgsrc), _lgto(lgto)
{
}

ActTranslation::~ActTranslation()
{
}

void ActTranslation::execute()
{
	wxString clipboard = Resource::getClipboard();
	Resource::getTranslation(clipboard, _lgsrc, _lgto);
}

wxPanel* ActTranslation::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActTranslation(parent, buttonOK, this);
}

void ActTranslation::actLoad(wxFileConfig & fileConfig)
{
	//On récupère les préférence.
	fileConfig.Read("lgsrc", &_lgsrc);
	fileConfig.Read("lgto", &_lgto);
}
		
void ActTranslation::actSave(wxFileConfig & fileConfig)const
{
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
}

wxString ActTranslation::getStringPreferences()const
{
	return 	Resource::getInstance()->acronymToLanguage(_lgsrc) +
			_(" to ") +
			Resource::getInstance()->acronymToLanguage(_lgto);
}
