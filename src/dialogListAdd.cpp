//! \file **************************************************************
//! \brief Source Dialogue pour ajouter une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 09.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogListAdd.hpp"
#include "resource.hpp"

// *********************************************************************
// Class DialoglistAdd
// *********************************************************************

//! \todo implémenter avec les locals
DialogListAdd::DialogListAdd(wxWindow* parent)
: GuiDialogListAdd(parent)
{
	std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	//Ajout des langues.
	for(auto &it: languages)
	{
		_choiceLanguageSource->Append(it.second);
		_choiceLanguageOfTranslation->Append(it.second);
	}
	
	//Sélectionne les bonnes langues.
	int n = _choiceLanguageSource->FindString(languages.at("en"));
	_choiceLanguageSource->SetSelection(n);
	n = _choiceLanguageOfTranslation->FindString(languages.at("fr"));
	_choiceLanguageOfTranslation->SetSelection(n);
}

DialogListAdd::~DialogListAdd()
{
}

wxString DialogListAdd::getNamelist()const
{
	return _textCtrlName->GetLineText(0);
}

void DialogListAdd::getlanguages(wxString* lgsrc, wxString* lgto)const
{
	//Affect le langage source.
	int n = _choiceLanguageSource->GetSelection();
	*lgsrc = _choiceLanguageSource->GetString(n);
	*lgsrc = Resource::getInstance()->languageToAbbreviation(*lgsrc);
	
	//Affect le langage de destination.
	n = _choiceLanguageOfTranslation->GetSelection();
	*lgto = _choiceLanguageOfTranslation->GetString(n);
	*lgto = Resource::getInstance()->languageToAbbreviation(*lgto);
}
