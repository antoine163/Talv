//! \file **********************************************************************
//! \brief Source Action de traduction ver la presse papier.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.03.2014
//!
//! ****************************************************************************


//App
#include "action/actTranslationToClipboard.hpp"
#include "manager/manNotification.hpp"
#include "manager/manGeneral.hpp"
#include "manager/manTranslator.hpp"
#include "dialog/dlgPickTranslation.hpp"
#include "dataText.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/sizer.h>

// *****************************************************************************
// Class ActTranslationToClipboard
// *****************************************************************************

ActTranslationToClipboard::ActTranslationToClipboard()
: _dlgPick(false)
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
}

ActTranslationToClipboard::~ActTranslationToClipboard()
{
}

IMPLEMENT_ACTION(ActTranslationToClipboard, _("Translation to clipboard"), _("Translation a text from clipboard into clipboard."));

WinAction* ActTranslationToClipboard::newEditWindow(wxWindow* parent)
{
	return new WinActTranslationToClipboard(parent, this);
}

wxString ActTranslationToClipboard::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto);
}

//! \todo ajouter le compter de traduction
void ActTranslationToClipboard::execute()
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
	
	//Affiche le dialogue pour choisir la traduction.
	if(_dlgPick)
	{
		DlgPickTranslation dlg(nullptr, clipboard, translations);
		if(dlg.ShowModal() == wxID_OK)
			translations.setMainTranslation(dlg.getTranslation());
		else
			return;
	}
	
	//On mes la traduction dans la presse papier.
	ManGeneral::get().setClipboard(translations.getMainTranslation());
	
	//Affiche une notification approuvent le texte et dans la presse papier.
	ManNotification::get().notify(	_("Text in the clipboard"),
									wxString::Format(_("The text: \"%s\" is in the clipboard."), translations.getMainTranslation()),
									wxICON_INFORMATION);
}

void ActTranslationToClipboard::getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

void ActTranslationToClipboard::setLanguages(wxLanguage lgsrc, wxLanguage lgto)
{
	_lgsrc = lgsrc;
	_lgto = lgto;
}

bool ActTranslationToClipboard::IsUsedDlgPick()const
{
	return _dlgPick;
}

void ActTranslationToClipboard::UseDlgPick(bool use)
{
	_dlgPick = use;
}

void ActTranslationToClipboard::actLoad(wxFileConfig& fileConfig)
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
	
	_dlgPick = fileConfig.ReadBool("showDlgPick", false);
}

void ActTranslationToClipboard::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("lgsrc", wxLocale::GetLanguageName(_lgsrc));
	fileConfig.Write("lgto", wxLocale::GetLanguageName(_lgto));
	fileConfig.Write("showDlgPick", _dlgPick);
}

// *****************************************************************************
// Class WinActTranslationToClipboard
// *****************************************************************************

WinActTranslationToClipboard::WinActTranslationToClipboard(wxWindow* parent, ActTranslationToClipboard const* act)
: WinAction(parent, act)
{
	//Créations du _checkBoxShowDlgPick.
	_checkBoxShowDlgPick = new wxCheckBox(this, wxID_ANY, _("Show a dialog for pick your translation."));
	_checkBoxShowDlgPick->SetValue(act->IsUsedDlgPick());
	
	//Créations du CtrlPickLanguages.
	wxLanguage lgsrc;
	wxLanguage lgto;
	static_cast<ActTranslationToClipboard*>(_act)->getLanguages(&lgsrc, &lgto);
	_ctrlPickLanguages = new CtrlPickLanguages(this, lgsrc, lgto);
	
	GetSizer()->Add(_checkBoxShowDlgPick, 	0, wxEXPAND|wxLEFT|wxRIGHT, 			SIZE_BORDER);
	GetSizer()->Add(_ctrlPickLanguages, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
}

WinActTranslationToClipboard::~WinActTranslationToClipboard()
{
}

void WinActTranslationToClipboard::refreshActionFromGui()
{
	ActTranslationToClipboard* act = static_cast<ActTranslationToClipboard*>(_act);
	
	act->UseDlgPick(_checkBoxShowDlgPick->GetValue());
	
	wxLanguage lgsrc;
	wxLanguage lgto;
	_ctrlPickLanguages->getLanguages(&lgsrc, &lgto);
	act->setLanguages(lgsrc, lgto);
}

