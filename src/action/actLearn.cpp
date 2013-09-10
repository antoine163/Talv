//! \file **************************************************************
//! \brief Source Action pour apprendre du liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.9
//! \date 15.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actLearn.hpp"
#include "listManager.hpp"
#include "resource.hpp"

#include <vector>
#include <wx/msgdlg.h> 
#include <stdlib.h>
#include <time.h>  

//TEST
#include <iostream>

// *********************************************************************
// Class DialogActLearn
// *********************************************************************

DialogActLearn::DialogActLearn(wxWindow* parent, wxString const& listName, unsigned int nbText)
: GuiDialogActLearn(parent), _listName(listName)
{
	//La valeur minimums de _nbText est 1.
	if(nbText == 0)
		_nbText = 1;
	else
		_nbText = nbText;
		
	_iNbText = 0;
	
	//Récupération de la liste.
	List* list = ListManager::getInstance()->getValue(_listName);
	
	//Récupération des langes de la liste.
	list->getlanguages(&_lgsrc, &_lgto);
	_guilgsrc = Resource::getInstance()->abbreviationToLanguage(_lgsrc);
	_guilgto = Resource::getInstance()->abbreviationToLanguage(_lgto);

	
	//Init pour le rendom
	srand(time(NULL));
}

DialogActLearn::~DialogActLearn()
{
}

int DialogActLearn::ShowModal()
{
	//On installe un texte dans le dialogue.
	if(!nextText())
		return wxID_CANCEL;
	
	//Mise a jour du dialogue.
	GetSizer()->Fit(this);
	
	//Verrouille la taille.
	wxSize size = this->GetSize();
	this->SetSizeHints(size, size);
	
	return GuiDialogActLearn::ShowModal();
}

bool DialogActLearn::nextText()
{
	//On quitte si on ne doit plus installe de nouveau texte.
	_iNbText++;
	if(_iNbText > _nbText)
		return false;
	
	//Active le bouton delete
	_buttonDelete->Enable();
	
	//Nettoyage de la réponse
	_textCtrlAnswer->Clear();
	_textCtrlAnswer->SetForegroundColour(wxNullColour);
	
	//Quelle que information à afficher.
	_staticTextInfo->SetLabel(wxString::Format(_("Learn the list : %s\nText %d sur %d"), _listName, _iNbText, _nbText));
	_staticTextInfo->SetForegroundColour(wxNullColour);
	
	//Récupération de la liste.
	List* list = ListManager::getInstance()->getValue(_listName);
	
	//Le nombre de texte présent dan la liste.
	size_t nbText = list->getNumberText();
	
	//Si il ni pas de texte dans la liste.
	if(nbText == 0)
		return false;
	
	//Chois de l'index parmi tout les textes.
	int indexText = (rand()%nbText)+1;
	
	//Détermine de l'index et de la connaissance choisis.
	_indexTextKnowledge = indexText;
	for(size_t i = 1; i<KNOWLEDGE_NB; i++)
	{
		_knowledge = (Knowledge_e)i;
		size_t nbText = list->getNumberTextByKnowledge(_knowledge);
		
		if(_indexTextKnowledge > nbText)
			_indexTextKnowledge -= nbText;
		else
			break;
	}
	
	//Récupération du texte
	list->getText(_indexTextKnowledge, &_knowledge, &_text, &_mainTranslate, nullptr);
	
	//choix de la lange de proposition.
	if(rand()%2 == 1)//On propose avec la lange source de la liste.
	{
		_choiceSrc = true;
		
		//Affiche des langes
		_staticTextPropose->SetLabel(_guilgsrc + " :"); 
		_staticTextAnswer->SetLabel(_guilgto + " :");
		
		//Affiche du texte proposer.
		_buttonTextPropose->SetLabel(_text);
		
		//La raiponce.
		_textAnswer = _mainTranslate;
	}
	else//On propose avec la lange de traduction de la liste.
	{
		_choiceSrc = false;
		
		//Affiche des langes
		_staticTextPropose->SetLabel(_guilgto + " :");
		_staticTextAnswer->SetLabel(_guilgsrc + " :");
		
		//Affiche du texte proposer.
		_buttonTextPropose->SetLabel(_mainTranslate);
		
		//La raiponce.
		_textAnswer = _text;
	}
	
	//Sélection de la connaissance.
	wxString sknowledge = List::knowledgeToString(_knowledge);
	int n = _choiceKnowledge->FindString(sknowledge);
	_choiceKnowledge->SetSelection(n);
	
	//Le texte n'a pas encore été vérifier.
	_statusAnswer = STATUS_ANSWER_NO_CHECK;
	_buttonCheck->SetLabel(_("Check !"));
	
	//Focus sur le textCtrl de la repose.
	_textCtrlAnswer->SetFocus();
	
	return true;
}

void DialogActLearn::checkNextAnswer()
{
	if(	_statusAnswer == STATUS_ANSWER_NO ||
		_statusAnswer == STATUS_ANSWER_CORRECT)
	{
		if(!nextText())
			Close();
		
		return;
	}
	else if(_statusAnswer == STATUS_ANSWER_BAD)
	{
		//Nettoyage de la réponse
		_textCtrlAnswer->Clear();
		_textCtrlAnswer->SetForegroundColour(wxNullColour);
		
		//Quelle que information à afficher.
		_staticTextInfo->SetLabel(wxString::Format(_("Learn the list : %s\nText %d sur %d"), _listName, _iNbText, _nbText));
		_staticTextInfo->SetForegroundColour(wxNullColour);
		
		_statusAnswer = STATUS_ANSWER_NO_CHECK;
		return;
	}
	
	if(_textCtrlAnswer->GetLineText(0) == wxEmptyString)
	{
		_staticTextInfo->SetLabel(_("No answer"));
		_staticTextInfo->SetForegroundColour(wxColour(0, 0, 127));
		
		_buttonCheck->SetLabel(_("Next"));
		_statusAnswer = STATUS_ANSWER_NO;
	}
	else if(_textCtrlAnswer->GetLineText(0) == _textAnswer)
	{
		_staticTextInfo->SetLabel(_("Your answer is correct."));
		_staticTextInfo->SetForegroundColour(wxColour(0, 127, 0));
		
		_buttonCheck->SetLabel(_("Next"));
		_statusAnswer = STATUS_ANSWER_CORRECT;
	}
	else
	{
		_staticTextInfo->SetLabel(_("Your answer is bad."));
		_staticTextInfo->SetForegroundColour(wxColour(127, 0, 0));
		
		_statusAnswer = STATUS_ANSWER_BAD;
	}
	
	//Dans tous cas on affiche la raiponce.
	_textCtrlAnswer->ChangeValue(_textAnswer);
	_textCtrlAnswer->SetForegroundColour(wxNullColour);
}

void DialogActLearn::OnButtonClickPropose(wxCommandEvent& event)
{
}

void DialogActLearn::OnTextAnswer(wxCommandEvent& event)
{
	//Quelle que information à afficher.
	_staticTextInfo->SetLabel(wxString::Format(_("Learn the list : %s\nText %d sur %d"), _listName, _iNbText, _nbText));
	_staticTextInfo->SetForegroundColour(wxNullColour);
	
	
	if(_textAnswer.StartsWith(_textCtrlAnswer->GetLineText(0)))
		_textCtrlAnswer->SetForegroundColour(wxNullColour);
	else
		_textCtrlAnswer->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
}

void DialogActLearn::OnTextEnterAnswer(wxCommandEvent& event)
{
	checkNextAnswer();
}

void DialogActLearn::OnChoiceKnowledge(wxCommandEvent& event)
{	 
	//Récupération de la connaissance.
	int n = _choiceKnowledge->GetSelection();
	wxString sknowledge = _choiceKnowledge->GetString(n);
	_knowledge = List::stringToKnowledge(sknowledge);
	
	ListManager::getInstance()->getValue(_listName)->setKnowledge(_text, _knowledge);
}

void DialogActLearn::OnButtonClickDelete(wxCommandEvent& event)
{
	ListManager::getInstance()->getValue(_listName)->removeText(_text);
	_buttonDelete->Enable(false);
}

void DialogActLearn::OnButtonClickCheck(wxCommandEvent& event)
{
	checkNextAnswer();
}

// *********************************************************************
// Class PanelActLearn
// *********************************************************************

PanelActLearn::PanelActLearn(wxWindow* parent, wxButton* buttonOK, ActLearn* act)
: GuiPanelActLearn(parent), _act(act), _buttonOK(buttonOK)
{	
	//Obtenir la liste des lites.
	wxArrayString tmpLists = EditListManager::getInstance()->getNameLists();
	
	//Complète les chois.
	for(auto it: tmpLists)
		_choiceList->Append(it);
		
	//Sélectionne le chois.
	if(!act->_listName.IsEmpty())
	{
		int n = _choiceList->FindString(act->_listName);
		_choiceList->SetSelection(n);
	}
	
	//Sélection le nombre de texte.
	_spinCtrlNbText->SetValue(act->_nbText);

	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActLearn::~PanelActLearn()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActLearn::OnOKButtonClick(wxCommandEvent& event)
{
	//Vérifie si une liste est sélectionnée.
	int n = _choiceList->GetSelection();
	if(n == wxNOT_FOUND)
	{
		wxMessageBox(_("Please select a list."), _("Name list invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE, this);
		return;
	}
	
	//Récupération le nombre de texte.
	_act->_nbText = _spinCtrlNbText->GetValue();
	
	//Récupération du nom de la liste choisi.
	_act->_listName = _choiceList->GetString(n);
	
	//Propage l'événement.
	event.Skip();
}

// *********************************************************************
// Class ActLearn
// *********************************************************************

ActLearn::ActLearn()
: ActLearn(wxEmptyString, 1)
{
}

ActLearn::ActLearn(wxString const& listName, unsigned int nbText)
: Action(_("Learn a list"), "ActLearn",	_("Learning the contents of a list.")),
_listName(listName)
{
	//La valeur minimums de _nbText est 1.
	if(nbText == 0)
		_nbText = 1;
	else
		_nbText = nbText;
}

ActLearn::ActLearn(ActLearn const& other)
: ActLearn(other._listName, other._nbText)
{
}

ActLearn::~ActLearn()
{
}

void ActLearn::execute()
{
	//Pour ne pas lancer plusieurs dialogue en même temps.
	static bool dlgShowModal = false;
	
	if(!dlgShowModal)
	{
		dlgShowModal = true;
		DialogActLearn dlg(nullptr, _listName, _nbText);
		dlg.ShowModal();
		dlgShowModal = false;
	}
}

wxPanel* ActLearn::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActLearn(parent, buttonOK, this);
}

void ActLearn::actLoad(wxFileConfig & fileConfig)
{
	fileConfig.Read("listName", &_listName);
	double tmp;
	
	fileConfig.Read("nbText", &tmp);
	if(tmp == 0)//La valeur minimums de _nbText est 1.
		_nbText = 1;
	else
		_nbText = tmp;
}
		
void ActLearn::actSave(wxFileConfig & fileConfig)const
{
	fileConfig.Write("listName", _listName);
	fileConfig.Write("nbText", (double)_nbText);
}

wxString ActLearn::getStringPreferences()const
{
	return wxString::Format(_("Learn the list : %s"), _listName);
}

wxString ActLearn::getListNameUsed()const
{
	return _listName;
}
