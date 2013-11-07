//! \file **************************************************************
//! \brief Source Action, traduction et sauvegarde dans une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.21
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actTranslationToList.hpp"
#include "resource.hpp"
#include "listManager.hpp"

#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/log.h> 


//TEST
#include <iostream>


// *********************************************************************
// Class PanelActTranslationToList
// *********************************************************************

PanelActTranslationToList::PanelActTranslationToList(wxWindow* parent, wxButton* buttonOK, ActTranslationToList* act)
: GuiPanelActTranslationToList(parent), _act(act), _buttonOK(buttonOK)
{
	std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	//Ajout des langues.
	for(auto &it: languages)
	{
		_choiceLanguageSource->Append(it.second);
		_choiceLanguageOfTranslation->Append(it.second);
	}
	
	//Sélectionne les bonnes langues.
	int n = _choiceLanguageSource->FindString(languages.at(_act->_lgsrc));
	_choiceLanguageSource->SetSelection(n);
	n = _choiceLanguageOfTranslation->FindString(languages.at(_act->_lgto));
	_choiceLanguageOfTranslation->SetSelection(n);
	
	//Métre a jour le combo box
	updateComboBoxList();
		
	//Dessiner un dialogue
	if(_act->_showDialog)
		_checkBoxShowDialog->SetValue(true);
	else
		_checkBoxShowDialog->SetValue(false);
		
	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslationToList::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActTranslationToList::~PanelActTranslationToList()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActTranslationToList::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActTranslationToList::updateComboBoxList()
{	
	//Récupération du langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	wxString tmplgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	//Récupération du langage de traduction.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	wxString tmplgto = Resource::getInstance()->languageToAbbreviation(s);
	
	//Récupération de la liste des listes en fonction des langes.
	wxArrayString tmpLists = EditListManager::getInstance()->getNameListsByLanguages(tmplgsrc, tmplgto);
	
	//On modifie le combo box pour les nouveau chois de liste.
	_comboBoxList->Clear();
	_comboBoxList->Append(tmpLists);
	_comboBoxList->AutoComplete(tmpLists);
	
	//Chois de la liste de l'action si elle existe dans tmpLists.
	int selec = _comboBoxList->FindString(_act->_listName);
	if(selec != wxNOT_FOUND)
		_comboBoxList->SetSelection(selec);
}

void PanelActTranslationToList::OnChoiceSrc(wxCommandEvent&)
{
	updateComboBoxList();
}

void PanelActTranslationToList::OnChoiceTo(wxCommandEvent&)
{
	updateComboBoxList();
}

void PanelActTranslationToList::OnOKButtonClick(wxCommandEvent& event)
{
	//Récupération du langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	wxString tmpChoiceLgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	//Récupération du langage de traduction.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	wxString tmpChoiceLgto = Resource::getInstance()->languageToAbbreviation(s);
	
	//Récupère le nom de la liste
	wxString tmpListName = _comboBoxList->GetValue();
	
	//Vérifie si le nom de la liste et valide.
	if(tmpListName.IsEmpty())
	{
		wxMessageBox(_("The name of list is empty."), _("Name list invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE, this);
		return;
	}
	
	//Vérifie si la liste est déjà existante
	if(EditListManager::getInstance()->exist(tmpListName))
	{
		//Vérifie si la lite est configurer avec les même langage.
		List* tmpList = EditListManager::getInstance()->getValue(tmpListName);
		wxString tmplgsrc;
		wxString tmplgto;
		tmpList->getlanguages(&tmplgsrc, &tmplgto);
		
		if((tmplgsrc != tmpChoiceLgsrc) || (tmplgto != tmpChoiceLgto))
		{
			wxMessageDialog dlg(this,
								_("The list is already existing and isn't compatible with the preference of your action."),
								_("List already existing"),
								wxOK|wxICON_INFORMATION|wxCENTRE);
			dlg.ShowModal();
			return;
		}

	}
	//Sinon on la crée
	else
	{
		if(!EditListManager::getInstance()->createAndAddList(tmpListName, tmpChoiceLgsrc, tmpChoiceLgto))
		{
			wxMessageDialog dlg(this, _("A problem is occured, the list can't add!"), _("List corrupt"), wxOK|wxICON_INFORMATION|wxCENTRE);
			dlg.ShowModal();
			return;
		}
	}
	
	//Affect le nom de la list.
	_act->_listName = tmpListName;
	
	//Affect à l'action le langage source.
	_act->_lgsrc = tmpChoiceLgsrc;
	
	//Affect à l'action le langage de destination.
	_act->_lgto = tmpChoiceLgto;
	
	//Affect à l'action si il doit afficher un dialogue.
	_act->_showDialog = _checkBoxShowDialog->IsChecked();
		
	//Propage l'événement.
	event.Skip();
}

// *********************************************************************
// Class PanelPickTranslation
// *********************************************************************

PanelPickTranslation::PanelPickTranslation(	DialogPickMainTranslation* parent,
									wxString const& kind,
									wxArrayString const& translations)
: GuiPanelTranslation(parent),_parent(parent)
{
	_staticTextKind->SetLabelMarkup("<b>"+kind+" :</b>");

	//Création des boutons pour chaque traductions
	for(auto it : translations)
	{
		//Ajout un bouton
		wxButton* button = new wxButton(this, wxID_ANY, it, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT|wxBU_LEFT|wxNO_BORDER );
		_bSizerTranslation->Add(button, 0, wxEXPAND, 5);
		_buttons.push_back(button);
		
		//Bind l'événement du bouton
		button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogPickMainTranslation::OnButtonClick, _parent, button->GetId());
	}
}

PanelPickTranslation::~PanelPickTranslation()
{
	//Unbind les événements des boutons
	for(auto it : _buttons)
	{
		it->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogPickMainTranslation::OnButtonClick, _parent, it->GetId());
	}
}

// *********************************************************************
// Class DialogPickMainTranslation
// *********************************************************************

DialogPickMainTranslation::DialogPickMainTranslation(wxWindow* parent,
						wxString text,
						wxString mainTranslate,
						std::map<wxString, wxArrayString> const& translations)
: GuiDialogPickMainTranslation(parent), _choice(mainTranslate)
{
	//Afficher le texte et la traduction principale
	_staticText->SetLabelMarkup("<b>"+text+" :</b>");
	_buttonMainTranslation->SetLabel(mainTranslate);
	
	//Bind l'événement du bouton
	_buttonMainTranslation->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogPickMainTranslation::OnButtonClick, this, _buttonMainTranslation->GetId());

	
	//Ajout une spacer si il ni pas rien dans translations
	if(translations.size() == 0)
	{
		_bSizerTranslation->Add(0, 0, 1, wxEXPAND, 5);
	}
	//Sinon on remplir le dialogue avec les traductions
	else
	{
		//Ajout des panels avec les traductions pour touts les genres (le wxString de translations).
		PanelPickTranslation* panel;
		for(auto it : translations)
		{
			panel = new PanelPickTranslation(this, it.first, it.second);
			_bSizerTranslation->Add(panel, 1, wxEXPAND|wxALL, 5);
		}
	}
	
	//Recalcule de la tille de la fenêtre.
	this->Layout();
	GetSizer()->Fit(this);
	this->Centre(wxBOTH);
}	

DialogPickMainTranslation::~DialogPickMainTranslation()
{
	//Unbind l'événement du bouton
	_buttonMainTranslation->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogPickMainTranslation::OnButtonClick, this, _buttonMainTranslation->GetId());
}
	
wxString const& DialogPickMainTranslation::GetChoice()
{
	return _choice;
}

void DialogPickMainTranslation::OnButtonClick(wxCommandEvent& event)
{
	//On récupère le bouton qui a générer l'événement.
	wxButton const* button = static_cast<wxButton const*>(event.GetEventObject());
	
	//On récupère le label du bouton.
	_choice = button->GetLabel();
	
	//On quitte le dialogue
	EndModal(wxID_OK);
}

// *********************************************************************
// Class ActTranslationToList
// *********************************************************************

//! \todo a compléter avec les locals
ActTranslationToList::ActTranslationToList()
: ActTranslationToList("en", "fr", wxEmptyString, true)
{
}

ActTranslationToList::ActTranslationToList(	wxString const& lgsrc,
											wxString const& lgto,
											wxString const& listName,
											bool showDialog)
: Action(_("Translation to list"), "ActTranslationToList",
_("Translation a text with google and save in a list.")),
_lgsrc(lgsrc), _lgto(lgto), _listName(listName), _showDialog(showDialog)
{
}

ActTranslationToList::~ActTranslationToList()
{
}

void ActTranslationToList::execute()
{
	//On récupère le contenue de la presse papier.
	wxString clipboard = Resource::getClipboard();
	
	//La presse papier est t'elle vide ?
	if(clipboard.IsEmpty())
	{
		//Pas de texte à traduire.
		Notification::getInstance()->notify(_("Save clipboard translation"), _("Sorry, nothing at save."));
		return;
	}

	//On récupère le texte traduit.
	std::map<wxString, wxArrayString> translations;
	wxString mainTranslate = Resource::getTranslations(&translations, clipboard, _lgsrc, _lgto);
	//On vérifie si une traduction existe.
	if(mainTranslate.IsEmpty())
	{
		Notification::getInstance()->notify(_("Save clipboard translation"), _("Sorry, nothing at save."));
		return;
	}

	//On récupère la liste.
	List* tmpList = ListManager::getInstance()->getListCheckDialog(_listName, getName());
	if(tmpList == nullptr)
		return;
	
	//Vérification des lange de la liste.
	wxString tmplgsrc;
	wxString tmplgto;
	tmpList->getlanguages(&tmplgsrc, &tmplgto);
	wxASSERT(tmplgsrc==_lgsrc);
	wxASSERT(tmplgto==_lgto);
	
	//On vérifier l'existence du texte dans la liste
	if(tmpList->exist(clipboard) == 1)
	{
		Notification::getInstance()->notify(_("Save clipboard translation"), wxString::Format(_("The text is already existing in '%s'"), _listName));
		return;
	}
	
	//Si on doit afficher le dialogue pour choisie la traduction principale.
	if(_showDialog)
	{
		DialogPickMainTranslation dlg(nullptr, clipboard, mainTranslate, translations);
		if(dlg.ShowModal() == wxID_CANCEL)
		{
			//L'utilisateur à quitter le dialogue.
			Notification::getInstance()->notify(_("Save clipboard translation"), _("The text is not saved."));
			return;
		}
		
		//mainTranslate deviens le chois de l'utilisateur
		mainTranslate = dlg.GetChoice();
	}
	
	//Sinon on le sauvegarde.
	if(tmpList->save(clipboard, mainTranslate, translations) != 1)
		return;
	
	Notification::getInstance()->notify(_("Clipboard translation to list"), _("The text has be saved."));
}

wxPanel* ActTranslationToList::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActTranslationToList(parent, buttonOK, this);
}

void ActTranslationToList::actLoad(wxFileConfig & fileConfig)
{	
	//On récupère les langages.
	fileConfig.Read("lgsrc", &_lgsrc);
	fileConfig.Read("lgto", &_lgto);
	
	//On récupère la list.
	fileConfig.Read("listName", &_listName);
	
	//On sauvegarde si on doit dessiner un dialogue a la sauvage d'un texts.
	fileConfig.Read("showDialog", &_showDialog);
}
		
void ActTranslationToList::actSave(wxFileConfig & fileConfig)const
{	
	//On sauvegarde les langages.
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
	
	//On sauvegarde la liste.
	fileConfig.Write("listName", _listName);
	
	//On sauvegarde si on doit dessiner un dialogue a la sauvage d'un texts.
	fileConfig.Write("showDialog", _showDialog);
}

wxString ActTranslationToList::getStringPreferences()const
{
	return 	Resource::getInstance()->abbreviationToLanguage(_lgsrc) +
			' ' + _("to") + ' ' +
			Resource::getInstance()->abbreviationToLanguage(_lgto) +
			' ' + _("in list") + ' ' + _listName;
}

wxString ActTranslationToList::getListNameUsed()const
{
	return _listName;
}
