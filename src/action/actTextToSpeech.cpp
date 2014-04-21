//! \file **************************************************************
//! \brief Source Action texte à la parole.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 25.04.2013
//!
//! ********************************************************************

//App
#include "action/actTextToSpeech.hpp"
#include "manager/manGeneral.hpp"
//#include "manager/manTts.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/log.h> 

// *****************************************************************************
// Class ActTextToSpeech
// *****************************************************************************

ActTextToSpeech::ActTextToSpeech()
{	
	ManGeneral::get().getSystemLanguage() == wxLANGUAGE_ENGLISH
	? _lg = wxLANGUAGE_FRENCH
	: _lg = wxLANGUAGE_ENGLISH;
}

ActTextToSpeech::~ActTextToSpeech()
{
}

IMPLEMENT_ACTION(ActTextToSpeech, _("Text to speech"), _("Speech the text from clipboard."));

WinAction* ActTextToSpeech::newEditWindow(wxWindow* parent)
{
	return new WinActTextToSpeech(parent, this);
}

wxString ActTextToSpeech::getStringPreferences()const
{
	return wxLocale::GetLanguageName(_lg) + " text to speech";
}

void ActTextToSpeech::execute()
{
	wxLogMessage("ActTextToSpeech::execute");
}

void ActTextToSpeech::getLanguage(wxLanguage* lg)const
{
	*lg = _lg;
}

void ActTextToSpeech::setLanguage(wxLanguage lg)
{
	_lg = lg;
}

void ActTextToSpeech::actLoad(wxFileConfig& fileConfig)
{
	ManGeneral::get().getSystemLanguage() == wxLANGUAGE_ENGLISH
	? _lg = wxLANGUAGE_FRENCH
	: _lg = wxLANGUAGE_ENGLISH;	
	
	//On récupère les préférences.
	wxString lg;
	lg = fileConfig.Read("lg", wxLocale::GetLanguageName(_lg));
	_lg = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
}

void ActTextToSpeech::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("lg", wxLocale::GetLanguageName(_lg));
}

// *****************************************************************************
// Class WinActTextToSpeech
// *****************************************************************************

WinActTextToSpeech::WinActTextToSpeech(wxWindow* parent, ActTextToSpeech const* act)
: WinAction(parent, act)
{
	//Créations du CtrlPickLanguages.
	wxLanguage lg;
	static_cast<ActTextToSpeech*>(_act)->getLanguage(&lg);
	_ctrlPickLanguages = new CtrlPickLanguages(this, lg);
	
	GetSizer()->Add(_ctrlPickLanguages, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
}

WinActTextToSpeech::~WinActTextToSpeech()
{
}

void WinActTextToSpeech::refreshActionFromGui()
{
	wxLanguage lg;
	_ctrlPickLanguages->getLanguage(&lg);
	static_cast<ActTextToSpeech*>(_act)->setLanguage(lg);
}