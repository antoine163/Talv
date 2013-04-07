//! \file **************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
//! \date 04.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action.hpp"

#ifdef USE_ACT_TRANSLATION
#include "action/actTranslation.hpp"
#endif
#ifdef USE_ACT_SAVE_TRANSLATION
#include "action/actSaveTranslation.hpp"
#endif
#ifdef USE_ACT_SAY
#include "action/actSay.hpp"
#endif

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
	
void Action::sove(wxFileConfig & fileConfig)const
{
	fileConfig.Write("ActTypeName", _actTypeName);
	actSove(fileConfig);
}

Action* Action::newAction(wxString const& actTypeName)
{
	#ifdef USE_ACT_TRANSLATION
	if(actTypeName == "ActTranslation")
		return new ActTranslation();
	#endif
		
	#ifdef USE_ACT_SAVE_TRANSLATION
	if(actTypeName == "ActSaveTranslation")
		return new ActSaveTranslation();
	#endif
		
	#ifdef USE_ACT_SAY
	if(actTypeName == "ActSay")
		return new ActSay();
	#endif
	
	return nullptr;
}

Action* Action::newAction(Action const& act)
{
	#ifdef USE_ACT_TRANSLATION
	if(act.actTypeName == "ActTranslation")
		return new ActTranslation(act);
	#endif
		
	#ifdef USE_ACT_SAVE_TRANSLATION
	if(act.actTypeName == "ActSaveTranslation")
		return new ActSaveTranslation(act);
	#endif
		
	#ifdef USE_ACT_SAY
	if(act.actTypeName == "ActSay")
		return new ActSay(act);
	#endif
	
	return nullptr;
}

wxString const& Action::getDescription()const
{
	return _actDescription;
}

wxString const& Action::getName()const
{
	return _name;
}

wxString const& Action::getActTypeName()const
{
	return _actTypeName;
}
