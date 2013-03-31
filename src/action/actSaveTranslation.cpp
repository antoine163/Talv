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
}

PanelActSaveTranslation::~PanelActSaveTranslation()
{
	std::cout << "~PanelActSaveTranslation()" << std::endl;
}

// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

ActSaveTranslation::ActSaveTranslation()
: Action(_("Save a translation"), _("Translation a word or a group words from google and save in the file."))
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

ActSaveTranslation ActSaveTranslation::load(wxFileConfig & fileConfig)
{	
	return ActSaveTranslation();
}
		
void ActSaveTranslation::sove(wxFileConfig & fileConfig)const
{
}

wxString ActSaveTranslation::getStringPreferences()const
{
	return "ActSoveTranslation::getStringPreferences";
}
