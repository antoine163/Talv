//! \file **************************************************************
//! \brief Source Action de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.6
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

PanelActTranslation::PanelActTranslation(wxWindow* parent, ActTranslation * act)
: GuiPanelActTranslation(parent), _act(act)
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
}

PanelActTranslation::~PanelActTranslation()
{
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
	std::cout << "ActTranslation::execute" << std::endl;
	std::cout << "-- " << getStringPreferences() << std::endl;
}

wxPanel* ActTranslation::getPanelPreferences(wxWindow* parent)
{
	return new PanelActTranslation(parent, this);
}

void ActTranslation::actLoad(wxFileConfig & fileConfig)
{
	//On récupère les préférence.
	fileConfig.Read("lgsrc", &_lgsrc);
	fileConfig.Read("lgto", &_lgto);
}
		
void ActTranslation::actSove(wxFileConfig & fileConfig)const
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
