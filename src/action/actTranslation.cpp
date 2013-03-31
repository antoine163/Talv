//! \file **************************************************************
//! \brief Source Action de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
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
	std::map<wxString, wxString> const& langs = Resource::getInstance()->getLangs();	
	
	//Ajout des langes.
	for(auto &it: langs)
	{
		_choiceLanguageSource->Append(it.second);
		_choiceLanguageOfTranslation->Append(it.second);
	}

	//Sélectionne les bonnes langs.
	int n = _choiceLanguageSource->FindString(langs.at(_act->_lgsrc));
	_choiceLanguageSource->SetSelection(n);
	n = _choiceLanguageOfTranslation->FindString(langs.at(_act->_lgto));
	_choiceLanguageOfTranslation->SetSelection(n);
}

PanelActTranslation::~PanelActTranslation()
{
	std::cout << "~PanelActTranslation()" << std::endl;
}

void PanelActTranslation::OnChoiceSrc(wxCommandEvent& event)
{
}

void PanelActTranslation::OnChoiceTo(wxCommandEvent& event)
{
}


// *********************************************************************
// Class ActTranslation
// *********************************************************************

ActTranslation::ActTranslation(wxString const& lgsrc, wxString const& lgto)
: Action(_("Translation"), _("Translation a word or a group words from google.")),
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

ActTranslation ActTranslation::load(wxFileConfig & fileConfig)
{
	wxString lgsrc;
	wxString lgto;
	
	//On récupère les préférence.
	fileConfig.Read("lgsrc", &lgsrc);
	fileConfig.Read("lgto", &lgto);
	
	return ActTranslation(lgsrc, lgto);
}
		
void ActTranslation::sove(wxFileConfig & fileConfig)const
{
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
}

wxString ActTranslation::getStringPreferences()const
{
	std::map<wxString, wxString> const& langs = Resource::getInstance()->getLangs();
	return langs.at(_lgsrc) + _(" to ") + langs.at(_lgto);
}
