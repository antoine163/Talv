//04.01.2013
//v 0.4

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
