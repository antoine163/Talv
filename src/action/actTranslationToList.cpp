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
#include "manager/manNotification.hpp"

//WxWidgets
#include <wx/intl.h>

// *****************************************************************************
// Class ActTranslationToList
// *****************************************************************************

ActTranslationToList::ActTranslationToList()
{
	_lgto = (wxLanguage)wxLocale::GetSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH 				||
		_lgto == wxLANGUAGE_ENGLISH_UK 		        ||
		_lgto == wxLANGUAGE_ENGLISH_US 		        ||
		_lgto == wxLANGUAGE_ENGLISH_AUSTRALIA 		||
		_lgto == wxLANGUAGE_ENGLISH_BELIZE 		    ||
		_lgto == wxLANGUAGE_ENGLISH_BOTSWANA 		||
		_lgto == wxLANGUAGE_ENGLISH_CANADA 		    ||
		_lgto == wxLANGUAGE_ENGLISH_CARIBBEAN 		||
		_lgto == wxLANGUAGE_ENGLISH_DENMARK 		||
		_lgto == wxLANGUAGE_ENGLISH_EIRE 		    ||
		_lgto == wxLANGUAGE_ENGLISH_JAMAICA 		||
		_lgto == wxLANGUAGE_ENGLISH_NEW_ZEALAND 	||
		_lgto == wxLANGUAGE_ENGLISH_PHILIPPINES 	||
		_lgto == wxLANGUAGE_ENGLISH_SOUTH_AFRICA	||
		_lgto == wxLANGUAGE_ENGLISH_TRINIDAD 		||
		_lgto == wxLANGUAGE_ENGLISH_ZIMBABWE)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
		
		
		//Test
		_lgsrc = wxLANGUAGE_ENGLISH;
		_lgto = wxLANGUAGE_FRENCH;
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