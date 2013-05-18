//! \file **************************************************************
//! \brief Source Action pour apprendre du liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
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
// Class PanelActLearn
// *********************************************************************

PanelActLearn::PanelActLearn(wxWindow* parent, wxButton* buttonOK, ActLearn* act)
: GuiPanelActLearn(parent), _act(act), _buttonOK(buttonOK)
{	
	//Obtenir la liste des lites.
	wxArrayString tmpLists = EditListManager::getInstance()->getNameLists();
	
	//Complète les chois
	for(auto it: tmpLists)
		_choiceList->Append(it);
		
	//Sélectionne le chois
	if(!act->_listName.IsEmpty())
	{
		int n = _choiceList->FindString(act->_listName);
		_choiceList->SetSelection(n);
	}
	
	//sélection du temps
	_spinCtrlHours->SetValue(act->_callTime/60);
	_spinCtrlMinutes->SetValue(act->_callTime%60);

	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActLearn::~PanelActLearn()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

//! \bug segfauld
void PanelActLearn::OnOKButtonClick(wxCommandEvent& event)
{
	//Vérifie si une liste est sélectionnée.
	int n = _choiceList->GetSelection();
	
	if(n == wxNOT_FOUND)
	{
		wxMessageBox(_("Please select a list."), _("Name list invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE, this);
		return;
	}
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
: ActLearn(wxEmptyString, 0)
{
}

ActLearn::ActLearn(wxString const& listName, unsigned int callTime)
: Action(_("Learn a list"), "ActLearn",	_("Learning the contents of a list.")),
_listName(listName), _callTime(callTime)
{
}

ActLearn::ActLearn(ActLearn const& other)
: ActLearn(other._listName, other._callTime)
{
}

ActLearn::~ActLearn()
{
}

void ActLearn::Notify()
{
	execute();
	std::cout << this << std::endl;
	Start(_callTime*1000, true);
}

void ActLearn::execute()
{
	std::cout << "ActLearn::execute() " << _listName << std::endl;
}

wxPanel* ActLearn::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActLearn(parent, buttonOK, this);
}

void ActLearn::enable(bool enable)
{
	if(enable && _callTime != 0)
		Start(_callTime*1000, true);
	else
		Stop();
}

void ActLearn::actLoad(wxFileConfig & fileConfig)
{
	fileConfig.Read("listName", &_listName);
	double tmp;
	fileConfig.Read("callTime", &tmp);
	_callTime = tmp;
}
		
void ActLearn::actSave(wxFileConfig & fileConfig)const
{
	fileConfig.Write("listName", _listName);
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
