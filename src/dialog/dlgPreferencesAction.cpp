//! \file **********************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 31.12.2013
//!
//! ****************************************************************************

//App
#include "dialog/dlgPreferencesAction.hpp"
#include "action.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/settings.h>
#include <wx/stattext.h>

// *****************************************************************************
// Class DlgPreferencesAction
// *****************************************************************************

DlgPreferencesAction::DlgPreferencesAction(wxWindow* parent)
: DlgPreferencesAction(parent, ShortcutKey(), nullptr)
{		
	
}

DlgPreferencesAction::DlgPreferencesAction(wxWindow* parent, ShortcutKey const& shortcutKey, Action const* action)
: DialogInlay(parent, _("Preferences action"))
{	
	if(action == nullptr)
		SetName(_("Add action"));
	
	//Création de la listbook.
	_listbook = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_LEFT);
	
	std::vector<Action*> _allActions = Action::createAllActions();
	for(size_t i = 0; i < _allActions.size(); i++)
	{
		if(action != nullptr && action->getActTypeName() == _allActions[i]->getActTypeName())
		{
			delete _allActions[i];
			_allActions[i] = action->newClone();
			
			_listbook->AddPage(_allActions[i]->newEditWindow(_listbook), _allActions[i]->getName(), true);
		}
		else
			_listbook->AddPage(_allActions[i]->newEditWindow(_listbook), _allActions[i]->getName());
	}
	
	//Création du wxStaticText.
	wxStaticText* staticTextShortcut = new wxStaticText(this, wxID_ANY, _("Pick your shortcut:"));
	//Création du CtrlPickShortcutKey
	_ctrlPickShortcutKey = new CtrlPickShortcutKey(this, shortcutKey, true);
	
	//Mise en forme dans un sizer.
	wxSizer* sizerShortcut = new wxBoxSizer(wxHORIZONTAL);
	sizerShortcut->Add(staticTextShortcut,		0, 	wxALIGN_CENTER_VERTICAL|wxRIGHT, 		2*SIZE_BORDER);
	sizerShortcut->Add(_ctrlPickShortcutKey, 	1, 	wxEXPAND);
	
	//Création de deux statice line.
	wxStaticLine* staticLine1 = new wxStaticLine(this);
	wxStaticLine* staticLine2 = new wxStaticLine(this);
	
	//Créations des boutons.
	wxSizer* buttons = createButtonSizer(wxCANCEL|wxOK);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerShortcut,	0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	sizerMain->Add(staticLine1,		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(_listbook, 		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(staticLine2,		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	sizerMain->Add(buttons, 		0, 	wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);
	
	
	//SetSizerAndFit(sizerMain);
	SetSizer(sizerMain);
}

DlgPreferencesAction::~DlgPreferencesAction()
{	
	for(auto it: _allActions)
		delete it;
}

ShortcutKey DlgPreferencesAction::getShortcutKey()
{
	return _ctrlPickShortcutKey->getShortcutKey();
}

Action* DlgPreferencesAction::newCloneAction()
{
	wxWindow* windowActive = _listbook->GetCurrentPage();
	return static_cast<WinAction*>(windowActive)->newCloneAction();
}
		
