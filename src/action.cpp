//! \file **************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.14
//! \date 04.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action.hpp"

#include "action/actTranslation.hpp"
#include "action/actTranslationToList.hpp"
#include "action/actSay.hpp"
#include "action/actLearn.hpp"

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

Action* Action::newAction(wxString const& actTypeName)
{
	if(actTypeName == "ActTranslation")
		return new ActTranslation();

	if(actTypeName == "ActTranslationToList")
		return new ActTranslationToList();

	if(actTypeName == "ActSay")
		return new ActSay();

	if(actTypeName == "ActLearn")
		return new ActLearn();
	
	return nullptr;
}

Action* Action::newAction(Action const* act)
{
	if(act->_actTypeName == "ActTranslation")
		return new ActTranslation(static_cast<ActTranslation const&>(*act));

	if(act->_actTypeName == "ActTranslationToList")
		return new ActTranslationToList(static_cast<ActTranslationToList const&>(*act));

	if(act->_actTypeName == "ActSay")
		return new ActSay(static_cast<ActSay const&>(*act));

	if(act->_actTypeName == "ActLearn")
		return new ActLearn(static_cast<ActLearn const&>(*act));
	
	return nullptr;
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
