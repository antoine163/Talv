//17.03.2013
//v 0.3

#include "action/actTranslation.hpp"

//TEST
#include <iostream>

//! ********************************************************************
//! Class PanelActTranslation
//! ********************************************************************
PanelActTranslation::PanelActTranslation(wxWindow* parent, ActTranslation * act)
: GuiPanelActTranslation(parent), _act(act)
{
}

PanelActTranslation::~PanelActTranslation()
{
	std::cout << "~PanelActTranslation()" << std::endl;
}

void PanelActTranslation::OnChoiceSrc(wxCommandEvent& event)
{
}

void PanelActTranslation::OnChoiceTo(wxCommandEvent& event)
{
}


//! ********************************************************************
//! Class ActTranslation
//! ********************************************************************

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

wxPanel* ActTranslation::getPanelPreferences(wxWindow* parent)
{
	return new PanelActTranslation(parent, this);
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
