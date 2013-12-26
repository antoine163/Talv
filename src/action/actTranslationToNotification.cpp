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
// Class actTranslationToNotification
// *****************************************************************************

actTranslationToNotification::actTranslationToNotification()
{
	_lgto = (wxLanguage)wxLocale::GetSystemLanguage();
	if(_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
}

actTranslationToNotification::~actTranslationToNotification()
{
}

IMPLEMENT_ACTION(actTranslationToNotification, _("Translation To Notification"), _("Translation a text from clipboard into notification."));

wxWindow* actTranslationToNotification::newEditWindow(wxWindow*)
{
	return nullptr;
}

wxString actTranslationToNotification::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto);
}

void actTranslationToNotification::execute()
{
	ManNotification::get().notify("actTranslationToNotification::execute", getStringPreferences(), wxICON_INFORMATION, true);
}

void actTranslationToNotification::actLoad(wxFileConfig&)
{
	//On récupère les préférence.
	//fileConfig.Read("lgsrc", &_lgsrc);
	//fileConfig.Read("lgto", &_lgto);
}
		
void actTranslationToNotification::actSave(wxFileConfig&)const
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
