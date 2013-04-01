//! \file **************************************************************
//! \brief Source Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actSaveTranslation.hpp"
#include "resource.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************

PanelActSaveTranslation::PanelActSaveTranslation(wxWindow* parent, ActSaveTranslation * act)
: GuiPanelActSaveTranslation(parent), _act(act)
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
	
	//Sélectionne le bon répertoire.
	_dirPickerFolder->SetPath(_act->_location);
	//Sélectionne le bon fichier.
	_textCtrlFile->SetValue(_act->_fileName);
	
	//Tout sauvegarder ?
	if(_act->_soveAll)
		_radioBtnSaveAllTranslations->SetValue(true);
	else
		_radioBtnSaveATranslation->SetValue(true);
		
	//Pas de doublon
	if(_act->_noDoublon)
		_checkBoxNoDoublon->SetValue(true);
	else
		_checkBoxNoDoublon->SetValue(false);
		
	//Dessiner un dialogue
	if(_act->_showDialog)
		_checkBoxShowDialog->SetValue(true);
	else
		_checkBoxShowDialog->SetValue(false);
}

PanelActSaveTranslation::~PanelActSaveTranslation()
{
}

// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

ActSaveTranslation::ActSaveTranslation(wxString const& lgsrc,
							wxString const& lgto,
							wxString const& location,
							wxString const& fileName,
							bool soveAll,
							bool noDoublon,
							bool showDialog)
: Action(_("Save a translation"),
_("Translation a word or a group words from google and save in a file.")),
_lgsrc(lgsrc), _lgto(lgto), _location(location), _fileName(fileName),
_soveAll(soveAll), _noDoublon(noDoublon), _showDialog(showDialog)
{
}

ActSaveTranslation::~ActSaveTranslation()
{
}

void ActSaveTranslation::execute()
{
	std::cout << "ActSaveTranslation::execute" << std::endl;
	std::cout << "-- " << getStringPreferences() << std::endl;
}

wxPanel* ActSaveTranslation::getPanelPreferences(wxWindow* parent)
{
	return new PanelActSaveTranslation(parent, this);
}

//! \todo a compléter avec les valeurs écrites dans le fichier.
ActSaveTranslation ActSaveTranslation::load(wxFileConfig & fileConfig)
{	
	return ActSaveTranslation(	"en",
								"fr",
								wxGetUserHome(),
								"translation",
								true,
								true,
								true);
}
		
void ActSaveTranslation::sove(wxFileConfig & fileConfig)const
{
}

wxString ActSaveTranslation::getStringPreferences()const
{
	return "ActSoveTranslation::getStringPreferences";
}
