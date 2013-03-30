//17.03.2013
//v 0.3

#include "action/actTranslation.hpp"

#include <iostream>

ActTranslation::ActTranslation(wxString const& lgsrc, wxString const& lgto)
: Action(_("Translation"), _("Translation a word or a group words from google.")),
_lgsrc(lgsrc), _lgto(lgto)
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

ActTranslation ActTranslation::load(wxFileConfig & fileConfig)
{
	wxString lgsrc;
	wxString lgto;
	
	//On récupère les préférence.
	fileConfig.Read("lgsrc", &lgsrc);
	fileConfig.Read("lgto", &lgto);
	
	return ActTranslation(lgsrc, lgto);
}
		
void ActTranslation::sove(wxFileConfig & fileConfig)const
{
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
}

wxString ActTranslation::getStringPreferences()const
{
	return _lgsrc + " to " + _lgto;
}
