//! \file **********************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 04.01.2013
//!
//! ****************************************************************************

//App
#include "action.hpp"

#define CREATE_ACTION(action)					\
		if(actTypeName == #action || all)		\
		{										\
			ptrActions.push_back(new action());	\
		}
#include "actionDefs.hpp"

// *****************************************************************************
// Class Action
// *****************************************************************************

Action::Action()
{
}

Action::~Action()
{
}

void Action::load(wxFileConfig&)
{
}
	
void Action::save(wxFileConfig&)const
{
}

std::vector<Action*> Action::createActions()
{
	wxString actTypeName;
	std::vector<Action*> ptrActions;
	bool all = true;
	MAKE_CREATE_ACTION();
	return ptrActions;
}

Action* Action::createAction(wxString const& actTypeName)
{
	std::vector<Action*> ptrActions;
	bool all = false;
	MAKE_CREATE_ACTION();
	
	if(ptrActions.size() == 1)
		return ptrActions[0];
	
	return nullptr;
}
