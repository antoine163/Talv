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
#include "dataText.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/sizer.h>

// *****************************************************************************
// Class ActTranslationToNotification
// *****************************************************************************

ActTranslationToNotification::ActTranslationToNotification()
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
}

ActTranslationToNotification::~ActTranslationToNotification()
{
}

IMPLEMENT_ACTION(ActTranslationToNotification, _("Translation to notification"), _("Translation a text from clipboard into notification."));

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
		ManNotification::get().notify(_("Nothing at translate"), _("Your clipboard is empty."), wxICON_WARNING);
		return;
	}
	
	//On récupère le texte traduit
	DataText translations;
	ManTranslator::get().getTranslations(&translations, clipboard, _lgsrc, _lgto);
	//On vérifie si une traduction existe.
	if(translations.getMainTranslation().IsEmpty())
	{
		ManNotification::get().notify(_("No translation"), _("Sorry, there is no translation for the text!"), wxICON_WARNING);
		return;
	}
	
	//On mes en forme la traduction dans un wxString
	wxString translationsNotify;
	translationsNotify << "\n==&gt; <big>" << translations.getMainTranslation() << "</big>";
	
	auto trls = translations.getTranslations();
	for(auto &it: trls)
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

void ActTranslationToNotification::getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

void ActTranslationToNotification::setLanguages(wxLanguage lgsrc, wxLanguage lgto)
{
	_lgsrc = lgsrc;
	_lgto = lgto;
}

void ActTranslationToNotification::actLoad(wxFileConfig& fileConfig)
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;	
	
	//On récupère les préférences.
	wxString lg;
	lg = fileConfig.Read("lgsrc", wxLocale::GetLanguageName(_lgsrc));
	_lgsrc = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
	lg = fileConfig.Read("lgto", wxLocale::GetLanguageName(_lgto));
	_lgto = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
}

void ActTranslationToNotification::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("lgsrc", wxLocale::GetLanguageName(_lgsrc));
	fileConfig.Write("lgto", wxLocale::GetLanguageName(_lgto));
}

// *****************************************************************************
// Class WinActTranslationToNotification
// *****************************************************************************

WinActTranslationToNotification::WinActTranslationToNotification(wxWindow* parent, ActTranslationToNotification const* act)
: WinAction(parent, act)
{
	//Créations du CtrlPickLanguages.
	wxLanguage lgsrc;
	wxLanguage lgto;
	static_cast<ActTranslationToNotification*>(_act)->getLanguages(&lgsrc, &lgto);
	_ctrlPickLanguages = new CtrlPickLanguages(this, lgsrc, lgto);
	
	GetSizer()->Add(_ctrlPickLanguages, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
}

WinActTranslationToNotification::~WinActTranslationToNotification()
{
}

void WinActTranslationToNotification::refreshActionFromGui()
{
	wxLanguage lgsrc;
	wxLanguage lgto;
	_ctrlPickLanguages->getLanguages(&lgsrc, &lgto);
	static_cast<ActTranslationToNotification*>(_act)->setLanguages(lgsrc, lgto);
}

