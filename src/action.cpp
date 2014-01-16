//! \file **********************************************************************
//! \brief Source Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 04.01.2013
//!
//! ****************************************************************************

//App
#include "action.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/sizer.h>

#define CREATE_ACTION(action)					\
		if(actTypeName == #action || all)		\
		{										\
			ptrActions.push_back(new action());	\
		}
#include "actionDefs.hpp"

// *****************************************************************************
// Class Action
// *****************************************************************************

Action::Action()
{
}

Action::~Action()
{
}

void Action::load(wxFileConfig& fileConfig)
{
	actLoad(fileConfig);
}
	
void Action::save(wxFileConfig& fileConfig)const
{
	actSave(fileConfig);
}

std::vector<Action*> Action::createAllActions()
{
	wxString actTypeName;
	std::vector<Action*> ptrActions;
	bool all = true;
	MAKE_CREATE_ACTION();
	return ptrActions;
}

Action* Action::createAction(wxString const& actTypeName)
{
	std::vector<Action*> ptrActions;
	bool all = false;
	MAKE_CREATE_ACTION();
	
	if(ptrActions.size() == 1)
		return ptrActions[0];
	
	return nullptr;
}

// *****************************************************************************
// Class WinAction
// *****************************************************************************

WinAction::WinAction(wxWindow *parent, Action const* act)
: wxWindow(parent, wxID_ANY)
{
	_act = act->newClone();
	
	//Création de la description.
	wxStaticText* staticTextDescription = new wxStaticText(this, wxID_ANY, _act->getDescription());
	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticTextDescription, 	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(staticLine, 				0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	SetSizer(sizerMain);
}

WinAction::~WinAction()
{
}

Action* WinAction::newCloneAction()
{
	refreshActionFromGui();
	return _act->newClone();
}
