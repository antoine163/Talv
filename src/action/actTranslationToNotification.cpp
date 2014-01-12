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
#include "manager/manTranslator.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/sizer.h>

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

//! \todo ajouter le compter de traduction
void ActTranslationToNotification::execute()
{
	//On récupère le texte de la presse papier a traduire.
	wxString clipboard = ManGeneral::get().getClipboard();
	
	//La presse papier est t'elle vide ?
	if(clipboard.IsEmpty())
	{
		//Pas de texte à traduire
		ManNotification::get().notify(_("Nothing at translate"), _("Your clipboard is empty."), wxICON_INFORMATION);
		return;
	}
	
	//On récupère le texte traduit
	std::map<wxString, wxArrayString> translations;
	wxString mainTranslate = ManTranslator::get().getTranslations(&translations, clipboard, _lgsrc, _lgto);
	//On vérifie si une traduction existe.
	if(mainTranslate.IsEmpty())
	{
		ManNotification::get().notify(_("No translation"), _("Sorry, there is no translation for the text: \""+clipboard+"\""), wxICON_INFORMATION);
		return;
	}
	
	//On mes en forme la traduction dans un wxString
	wxString translationsNotify;
	translationsNotify << "\n==&gt; <big>" << mainTranslate << "</big>";
	
	for(auto &it: translations)
	{		
		translationsNotify << "\n\n<i>" << it.first << ":</i>";
		for(auto &itt: it.second)
		{
			translationsNotify << "\n\t" << itt;
		}
	}
	
	//On affiche la traduction
	ManNotification::get().notify(
		wxString::Format(_("Clipboard translation to %s:"), wxLocale::GetLanguageName(_lgto)), translationsNotify, wxICON_NONE, true);
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

