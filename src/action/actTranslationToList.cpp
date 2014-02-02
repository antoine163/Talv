//! \file **********************************************************************
//! \brief Source Action, traduction et sauvegarde dans une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.21
//! \date 31.03.2013
//!
//! ****************************************************************************
//App
#include "action/actTranslationToList.hpp"
#include "manager/manGeneral.hpp"
#include "manager/manNotification.hpp"

//WxWidgets
#include <wx/intl.h>

// *****************************************************************************
// Class ActTranslationToList
// *****************************************************************************

ActTranslationToList::ActTranslationToList()
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
}

ActTranslationToList::~ActTranslationToList()
{
}

IMPLEMENT_ACTION(ActTranslationToList, _("Translation to list"), _("Translation a text from clipboard into a list."));

WinAction* ActTranslationToList::newEditWindow(wxWindow* parent)
{
	return new WinAction(parent, this);
}

wxString ActTranslationToList::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto);
}

void ActTranslationToList::execute()
{
	ManNotification::get().notify("ActTranslationToList::execute", getStringPreferences(), wxICON_INFORMATION, true);
}

void ActTranslationToList::actLoad(wxFileConfig&)
{
	//On récupère les préférence.
	//fileConfig.Read("lgsrc", &_lgsrc);
	//fileConfig.Read("lgto", &_lgto);
}
		
void ActTranslationToList::actSave(wxFileConfig&)const
{
	//fileConfig.Write("lgsrc", _lgsrc);
	//fileConfig.Write("lgto", _lgto);
}