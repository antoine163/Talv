//! \file **************************************************************
//! \brief Source Action pour apprendre du liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.6
//! \date 15.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actLearn.hpp"
#include "listManager.hpp"

#include <wx/msgdlg.h>

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
		
	
	_textCtrlAnswer->SetFocus();
}

DialogActLearn::~DialogActLearn()
{
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
	
	//Sélection du temps.
	_spinCtrlHours->SetValue(act->_callTime/60);
	_spinCtrlMinutes->SetValue(act->_callTime%60);
	
	//Active le panel time.
	if(act->_callTime != 0)
	{
		_panelTime->Enable(true);
		_checkBoxTime->SetValue(true);
	}

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
	
	//Récupération du temps choisi.
	_act->_callTime = 0;
	if(_checkBoxTime->GetValue())
		_act->_callTime = _spinCtrlHours->GetValue()*60+_spinCtrlMinutes->GetValue();
	
	//Propage l'événement.
	event.Skip();
}

void PanelActLearn::OnCheckBox(wxCommandEvent& event)
{
	//Active ou désactive le panel time.
	 _panelTime->Enable(event.IsChecked());
}

// *********************************************************************
// Class ActLearn
// *********************************************************************

ActLearn::ActLearn()
: ActLearn(wxEmptyString, 1, 0)
{
}

ActLearn::ActLearn(wxString const& listName, unsigned int nbText, unsigned int callTime)
: Action(_("Learn a list"), "ActLearn",	_("Learning the contents of a list.")),
_listName(listName), _callTime(callTime)
{
	//La valeur minimums de _nbText est 1.
	if(nbText == 0)
		_nbText = 1;
	else
		_nbText = nbText;
}

ActLearn::ActLearn(ActLearn const& other)
: ActLearn(other._listName, other._nbText, other._callTime)
{
}

ActLearn::~ActLearn()
{
}

void ActLearn::Notify()
{
	execute();
	Start(_callTime*60*1000, true);
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

void ActLearn::enable(bool enable)
{
	if(enable && _callTime != 0)
		Start(_callTime*60*1000, true);
	else
		Stop();
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
	
	fileConfig.Read("callTime", &tmp);
	_callTime = tmp;
}
		
void ActLearn::actSave(wxFileConfig & fileConfig)const
{
	fileConfig.Write("listName", _listName);
	fileConfig.Write("nbText", (double)_nbText);
	fileConfig.Write("callTime", (double)_callTime);
}

wxString ActLearn::getStringPreferences()const
{
	return wxString::Format(_("Learn the list : %s"), _listName);
}

wxString ActLearn::getListNameUsed()const
{
	return _listName;
}
