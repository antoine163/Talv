//04.01.2013
//v 0.4

#include "action.hpp"

Action::Action(wxString const& actName):_actName(actName)
{
}

Action::~Action()
{
}

wxString const& Action::getName()const
{
	return _actName;
}
