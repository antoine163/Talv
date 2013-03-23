//17.03.2013
//v 0.2

#include "action/actTranslation.hpp"

#include <iostream>

ActTranslation::ActTranslation(	wxString const& lgsrc, wxString const& lgto)
: _lgsrc(lgsrc), _lgto(lgto)
{
}

ActTranslation::~ActTranslation()
{
}

void ActTranslation::execute()
{
	std::cout << "ActTranslation::execute" << std::endl;
	std::cout << "-- " << getStringPreferences() << std::endl;
}

wxString ActTranslation::getStringPreferences()
{
	return _lgsrc + " to " + _lgto;
}
