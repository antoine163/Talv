//! \file **************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.10
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
	
void Action::save(wxFileConfig & fileConfig)const
{
	fileConfig.Write("ActTypeName", _actTypeName);
	actSave(fileConfig);
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

Action* Action::newAction(Action const* act)
{
	#ifdef USE_ACT_TRANSLATION
	if(act->_actTypeName == "ActTranslation")
		return new ActTranslation(static_cast<ActTranslation const&>(*act));
	#endif
		
	#ifdef USE_ACT_SAVE_TRANSLATION
	if(act->_actTypeName == "ActSaveTranslation")
		return new ActSaveTranslation(static_cast<ActSaveTranslation const&>(*act));
	#endif
		
	#ifdef USE_ACT_SAY
	if(act->_actTypeName == "ActSay")
		return new ActSay(static_cast<ActSay const&>(*act));
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
