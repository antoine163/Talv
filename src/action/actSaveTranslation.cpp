//! \file **************************************************************
//! \brief Source Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.16
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actSaveTranslation.hpp"
#include "resource.hpp"

#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/log.h> 


//TEST
#include <iostream>


// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************
//! \todo a implémenter avec ListManager
PanelActSaveTranslation::PanelActSaveTranslation(wxWindow* parent, wxButton* buttonOK, ActSaveTranslation * act)
: GuiPanelActSaveTranslation(parent), _act(act), _buttonOK(buttonOK)
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
	
	//Affiche le non de la liste si il y une liste.
	//if(_act->_list != nullptr)
		//(*_textCtrlList) << _act->_list->getName();
	
	//Tout sauvegarder ?
	if(_act->_saveAll)
		_radioBtnSaveAllTranslations->SetValue(true);
	else
		_radioBtnSaveATranslation->SetValue(true);
		
	//Dessiner un dialogue
	if(_act->_showDialog)
		_checkBoxShowDialog->SetValue(true);
	else
		_checkBoxShowDialog->SetValue(false);
		
		
	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSaveTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActSaveTranslation::~PanelActSaveTranslation()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSaveTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

//! \todo a implémenter avec ListManager
void PanelActSaveTranslation::OnOKButtonClick(wxCommandEvent& event)
{
	//Récupére le nom de la liste
	wxString tmpListName = _textCtrlList->GetLineText(0);
	
	//Vérifie si le nom de la liste et valide.
	if(tmpListName.IsEmpty())
	{
		wxMessageBox(_("The name of list is empty."), _("Name list invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE, this);
		return;
	}
	
	//Vérifie si le fichier du non de la lise et existent.
	//Ceci voudrai dire qu'une autre 
	//if(List::existInFileSystem(tmpListName))
	//{
		////Le fichier est déjà existent ?
		//if(tmpFileName.Exists() && tmpFileName != _act->_fileName)
		//{
			////Si il existe, on demande si il faut remplacer le fichier.
			//wxString message = wxString::Format(_("The file '%s' already exists.\nDo you want delete this file?"), tmpFileName.GetFullPath());
			//wxMessageDialog dlg(this, message, _("Delete a file"), wxYES_NO|wxICON_QUESTION|wxICON_EXCLAMATION|wxCENTRE);
			//if(dlg.ShowModal() != wxID_YES)
			//{
				//return;
			//}
			//else
			//{
				////Suppression du fichier.
				//if(!wxRemoveFile(_filePickerFile->GetPath()))
				//{
					//wxLogError(wxString::Format(_("Could not remove the file : '%s'"), tmpFileName.GetFullPath()));
				//}
			//}
		//}
	//}
	
	//Affect le langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	_act->_lgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	//Affect le langage de destination.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	_act->_lgto = Resource::getInstance()->languageToAbbreviation(s);
	
	//Affect les autres arguments.
	_act->_saveAll = _radioBtnSaveAllTranslations->GetValue();
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
// Class ActSaveTranslation
// *********************************************************************

//! \todo a compléter avec les locals
ActSaveTranslation::ActSaveTranslation()
: ActSaveTranslation(	"en", "fr", wxEmptyString,
						true, true)
{
}

//! \todo a implémenter avec ListManager
ActSaveTranslation::ActSaveTranslation(wxString const& lgsrc,
							wxString const& lgto,
							wxString const& listName,
							bool soveAll,
							bool showDialog)
: Action(_("Save a translation"), "ActSaveTranslation",
_("Translation a text with google and save in a file.")),
_lgsrc(lgsrc), _lgto(lgto),
_saveAll(soveAll), _showDialog(showDialog)
{
	//_list
}

ActSaveTranslation::~ActSaveTranslation()
{
}

void ActSaveTranslation::execute()
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
	
	//On vérifie la validités de la liste.
	if(_list == nullptr)
	{
		wxMessageBox(_("The name of file is wrong."), _("Name file invalid."), wxOK|wxICON_EXCLAMATION|wxCENTRE);
		return;
	}
	
	//On vérifier l'existence du texte dans le fichier
	if(_list->exist(clipboard))
	{
		Notification::getInstance()->notify(_("Save clipboard translation"), wxString::Format(_("The text is already existing in '%s'"), _list->getName()));
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
	if(_saveAll)//Doit ton tout sauvegarder ?
	{
		_list->save(clipboard, mainTranslate, translations);
	}
	else
	{
		_list->save(clipboard, mainTranslate);
	}
	
	Notification::getInstance()->notify(_("Save clipboard translation"), _("The text has be saved."));
}

wxPanel* ActSaveTranslation::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActSaveTranslation(parent, buttonOK, this);
}

//! \todo a implémenter avec ListManager
void ActSaveTranslation::actLoad(wxFileConfig & fileConfig)
{	
	//On récupère les langages.
	fileConfig.Read("lgsrc", &_lgsrc);
	fileConfig.Read("lgto", &_lgto);
	
	//On récupère la list.
	//wxString listName;
	//fileConfig.Read("listName", &listName);
	//newList(listName);
	
	//On récupère le reste
	fileConfig.Read("saveAll", &_saveAll);		
	fileConfig.Read("showDialog", &_showDialog);
}
		
//! \todo a implémenter avec ListManager
void ActSaveTranslation::actSave(wxFileConfig & fileConfig)const
{	
	//On sauvegarde les langages.
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
	
	//On sauvegarde la liste.
	//fileConfig.Write("listName", _list->getName());
	
	//On sauvegarde le reste
	fileConfig.Write("saveAll", _saveAll);
	fileConfig.Write("showDialog", _showDialog);
}

wxString ActSaveTranslation::getStringPreferences()const
{
	return 	Resource::getInstance()->abbreviationToLanguage(_lgsrc) +
			' ' + _("to") + ' ' +
			Resource::getInstance()->abbreviationToLanguage(_lgto) +
			' ' + _("in list") + ' ' + _list->getName();
}
