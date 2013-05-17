//! \file **************************************************************
//! \brief Source Action pour apprendre du liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 15.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actLearn.hpp"
#include "listManager.hpp"

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

	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActLearn::~PanelActLearn()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActLearn::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActLearn::OnOKButtonClick(wxCommandEvent& event)
{
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
: Action(_("Learn a list"), "ActLearn",	_("Learning the contents of a list."))
{
}

ActLearn::ActLearn(ActLearn const&)
: ActLearn()
{
}

ActLearn::~ActLearn()
{
}

void ActLearn::Notify()
{
	execute();
	std::cout << this << std::endl;
	Start(1000, true);
}

void ActLearn::execute()
{
	std::cout << "ActLearn::execute()" << std::endl;
}

wxPanel* ActLearn::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActLearn(parent, buttonOK, this);
}

void ActLearn::enable(bool enable)
{
	if(enable)
		Start(1000, true);
	else
		Stop();
}

void ActLearn::actLoad(wxFileConfig & fileConfig)
{
}
		
void ActLearn::actSave(wxFileConfig & fileConfig)const
{
}

wxString ActLearn::getStringPreferences()const
{
	return 	"ActLearn::getStringPreferences";
}
