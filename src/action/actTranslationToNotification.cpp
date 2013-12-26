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

//WxWidgets
#include <wx/intl.h>


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
}

ActTranslationToNotification::~ActTranslationToNotification()
{
}

IMPLEMENT_ACTION(ActTranslationToNotification, _("Translation to Notification"), _("Translation a text from clipboard into notification."));

wxWindow* ActTranslationToNotification::newEditWindow(wxWindow*)
{
	return nullptr;
}

wxString ActTranslationToNotification::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto);
}

void ActTranslationToNotification::execute()
{
	ManNotification::get().notify("ActTranslationToNotification::execute", getStringPreferences(), wxICON_INFORMATION, true);
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

//// *****************************************************************************
//// Class PanelActTranslation
//// *****************************************************************************

//PanelActTranslation::PanelActTranslation(wxWindow* parent, wxButton* buttonOK, ActTranslation * act)
//: GuiPanelActTranslation(parent), _act(act), _buttonOK(buttonOK)
//{
	//std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	////Ajout des langues.
	//for(auto &it: languages)
	//{
		//_choiceLanguageSource->Append(it.second);
		//_choiceLanguageOfTranslation->Append(it.second);
	//}

	////Sélectionne les bonnes langues.
	//int n = _choiceLanguageSource->FindString(languages.at(_act->_lgsrc));
	//_choiceLanguageSource->SetSelection(n);
	//n = _choiceLanguageOfTranslation->FindString(languages.at(_act->_lgto));
	//_choiceLanguageOfTranslation->SetSelection(n);
	
	////Lier l'événement du bouton OK du wxWindow parent.
	//_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslation::OnOKButtonClick, this, _buttonOK->GetId());
//}

//PanelActTranslation::~PanelActTranslation()
//{
	//_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslation::OnOKButtonClick, this, _buttonOK->GetId());
//}

//void PanelActTranslation::OnOKButtonClick(wxCommandEvent& event)
//{
	////Affect le langage source.
	//int n = _choiceLanguageSource->GetSelection();
	//wxString s = _choiceLanguageSource->GetString(n);
	//_act->_lgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	////Affect le langage de destination.
	//n = _choiceLanguageOfTranslation->GetSelection();
	//s = _choiceLanguageOfTranslation->GetString(n);
	//_act->_lgto = Resource::getInstance()->languageToAbbreviation(s);
	
	////Propage l'événement.
	//event.Skip();
//}
