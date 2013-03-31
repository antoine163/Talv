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

#include "action/actTranslation.hpp"
#include "resource.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class PanelActSoveTranslation
// *********************************************************************

PanelActSoveTranslation::PanelActSoveTranslation(wxWindow* parent, ActTranslation * act)
: GuiPanelActSoveTranslation(parent), _act(act)
{
}

PanelActSoveTranslation::~PanelActSoveTranslation()
{
	std::cout << "~PanelActSoveTranslation()" << std::endl;
}


// *********************************************************************
// Class ActSoveTranslation
// *********************************************************************

ActSoveTranslation::ActSoveTranslation()
: Action(_("Sove a translation"), _("Translation a word or a group words from google and sove in the file."))
{
}

ActSoveTranslation::~ActSoveTranslation()
{
}

void ActSoveTranslation::execute()
{
	std::cout << "ActSoveTranslation::execute" << std::endl;
	std::cout << "-- " << getStringPreferences() << std::endl;
}

wxPanel* ActSoveTranslation::getPanelPreferences(wxWindow* parent)
{
	return new PanelActTranslation(parent, this);
}

ActSoveTranslation ActSoveTranslation::load(wxFileConfig & fileConfig)
{	
	return ActSoveTranslation();
}
		
void ActSoveTranslation::sove(wxFileConfig & fileConfig)const
{
}

wxString ActSoveTranslation::getStringPreferences()const
{
	return "ActSoveTranslation::getStringPreferences";
}
