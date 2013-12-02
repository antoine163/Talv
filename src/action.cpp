//! \file **************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.16
//! \date 04.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action.hpp"

#include "action/actTranslation.hpp"
//#include "action/actTranslationToList.hpp"
//#include "action/actLearn.hpp"

// *********************************************************************
// Class Action
// *********************************************************************

Action::Action(wxString const& name, wxString const& actTypeName, wxString const& actDescription)
:_name(name), _actTypeName(actTypeName), _actDescription(actDescription)
{
}

Action::~Action()
{
}

void Action::load(wxFileConfig & fileConfig)
{
	actLoad(fileConfig);
}
	
void Action::save(wxFileConfig & fileConfig)const
{
	fileConfig.Write("ActTypeName", _actTypeName);
	actSave(fileConfig);
}

wxString const& Action::getDescription()const
{
	return _actDescription;
}

wxString Action::getListNameUsed()const
{
	return wxEmptyString;
}

wxString const& Action::getName()const
{
	return _name;
}

wxString const& Action::getActTypeName()const
{
	return _actTypeName;
}
