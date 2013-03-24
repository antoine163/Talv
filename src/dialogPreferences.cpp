//version : 1.1
//02.01.2013

#include "dialogPreferences.hpp"
#include "dialogShortcutPreferences.hpp"
#include "shortcut.hpp"

#include <wx/msgdlg.h>

//TEST
#include <iostream>

//! ****************************************************************************
//! Class DialogPreferences
//! ****************************************************************************

DialogPreferences::DialogPreferences(ActionManager *actionManager)
: GuiDialogPreferences(nullptr), _actionManager(actionManager)
{	
    //Magnifier 
    _staticTextSetting->SetLabelMarkup("<b>"+_("Setting")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");


	//_listCtrlAction->EnableAlternateRowColours();
	_listCtrlAction->AppendColumn(_("Shortcut"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Action"), wxLIST_FORMAT_LEFT, 100);
	_listCtrlAction->AppendColumn(_("Preferences"), wxLIST_FORMAT_LEFT, 170);
	
	//Rempli la list.
	for(auto it: *_actionManager->getAction())
	{
		_listCtrlAction->InsertItem(0, ShortcutKey::shortcutKeyToString(it.first));
		_listCtrlAction->SetItem(0, 1, it.second->getName());
		_listCtrlAction->SetItem(0, 2, it.second->getStringPreferences());
	}
}

DialogPreferences::~DialogPreferences()
{
}

void DialogPreferences::OnButtonClickActDelete(wxCommandEvent&)
{
	
}

void DialogPreferences::OnButtonClickActPreferences(wxCommandEvent&)
{
}

void DialogPreferences::OnButtonClickActAdd(wxCommandEvent&)
{
	for(auto it: _listItemSelected)
	{
		std::cout << it.GetText() << std::endl;
	}
	
	//DialogShortcutPreferences *dlg = new DialogShortcutPreferences(this);
	//dlg->ShowModal();
	//delete dlg;
}

void DialogPreferences::OnButtonClickOK(wxCommandEvent& event)
{	
	event.Skip();
}

void DialogPreferences::OnButtonClickApply(wxCommandEvent& event)
{	
	event.Skip();
}

void DialogPreferences::OnListItemDeselectedAction(wxListEvent& event)
{
	//Recherche e suppression de l'item désélectionner.
	for(size_t i = 0; i<_listItemSelected.size(); i++)
	{
		if(_listItemSelected[i] == event.GetItem())
		{
			_listItemSelected.erase(_listItemSelected.begin()+i);
			break;
		}
	}
}

void DialogPreferences::OnListItemRightClickAction(wxListEvent& event)
{
	std::cout << "OnListItemRightClickAction : " << event.GetItem().GetText() << std::endl;
}

void DialogPreferences::OnListItemSelectedAction(wxListEvent& event)
{
	_listItemSelected.push_back(event.GetItem());
}

bool DialogPreferences::shutdownIsToggle()const
{
	return _toggleBtnTurnOff->GetValue();
}

bool DialogPreferences::showIcon()const
{
	return _checkBoxShowMenu->GetValue();
}
		
