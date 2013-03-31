//! \file **************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.5
//! \date 04.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action.hpp"

Action::Action(wxString const& actName, wxString const& actDescription)
:_actName(actName), _actDescription(actDescription)
{
}

Action::~Action()
{
}

wxString const& Action::getDescription()const
{
	return _actDescription;
}

wxString const& Action::getName()const
{
	return _actName;
}
