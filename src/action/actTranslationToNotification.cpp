//! \file **********************************************************************
//! \brief Source Action de traduction ver une notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 17.03.2013
//!
//! ***************************************************************************

//App
#include "action/actTranslationToNotification.hpp"
#include "manager/manNotification.hpp"
#include "manager/manGeneral.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/sizer.h>

//Test
#include "manager/manNetwork.hpp"

// *****************************************************************************
// Class ActTranslationToNotification
// *****************************************************************************

ActTranslationToNotification::ActTranslationToNotification()
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

ActTranslationToNotification::~ActTranslationToNotification()
{
}

IMPLEMENT_ACTION(ActTranslationToNotification, _("Translation to Notification"), _("Translation a text from clipboard into notification."));

WinAction* ActTranslationToNotification::newEditWindow(wxWindow* parent)
{
	return new WinActTranslationToNotification(parent, this);
}

wxString ActTranslationToNotification::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto);
}

void ActTranslationToNotification::execute()
{
	//On récupère le texte de la presse papier a traduire.
	wxString text = ManGeneral::get().getClipboard();
	
	wxString url;
	url << "http://translate.google.com/translate_a/t?ie=UTF-8&oe=UTF-8&client=x";
	url << "&text=" << text;
	url << "&hl=" << wxLocale::GetLanguageCanonicalName(_lgto);
	url << "&sl=" << wxLocale::GetLanguageCanonicalName(_lgsrc);
	url << "&tl=" << wxLocale::GetLanguageCanonicalName(_lgto);
	
	wxString json;
	std::cout << "URL error: " << ManNetwork::get().downloadFromUrlToString(url, &json) << std::endl;
	ManNotification::get().notify("ActTranslationToNotification::execute", json, wxICON_NONE, true);
}

void ActTranslationToNotification::actLoad(wxFileConfig&)
{
	//On récupère les préférence.
	//fileConfig.Read("lgsrc", &_lgsrc);
	//fileConfig.Read("lgto", &_lgto);
}
		
void ActTranslationToNotification::actSave(wxFileConfig&)const
{
	//fileConfig.Write("lgsrc", _lgsrc);
	//fileConfig.Write("lgto", _lgto);
}

// *****************************************************************************
// Class WinActTranslationToNotification
// *****************************************************************************

WinActTranslationToNotification::WinActTranslationToNotification(wxWindow* parent, ActTranslationToNotification const* act)
: WinAction(parent, act)
{
	//Créations du CtrlPickLanguages.
	_ctrlPickLanguages = new CtrlPickLanguages(this);
	
	GetSizer()->Add(_ctrlPickLanguages, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
}

WinActTranslationToNotification::~WinActTranslationToNotification()
{
}

void WinActTranslationToNotification::refreshActionFromGui()
{
}

