//version : 1.1
//02.01.2013

#include "dialogPreferences.hpp"
#include "dialogShortcutPreferences.hpp"
#include "shortcut.hpp"

#include <wx/artprov.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>

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
	std::cout << "OnButtonClickActDelete" << std::endl;
}

void DialogPreferences::OnButtonClickActPreferences(wxCommandEvent&)
{
	std::cout << "OnButtonClickActPreferences" << std::endl;
}

void DialogPreferences::OnButtonClickActAdd(wxCommandEvent&)
{
	std::cout << "OnButtonClickActAdd" << std::endl;
	
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
	
	//Si rien n'est sélectionner on désactive les boutons delete.
	if(_listItemSelected.size() <= 0)
	{
		_buttonActDelete->Enable(false);
		_menuItemListDelete->Enable(false);
	}
		
	//On désactive le bouton Préférence soft si il y a un seul item de sélectionner.
	if(_listItemSelected.size() != 1)
	{
		_buttonActPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
	else
	{
		_buttonActPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
}

void DialogPreferences::OnListItemSelectedAction(wxListEvent& event)
{
	_listItemSelected.push_back(event.GetItem());
	
	//activation du bouton delete
	_buttonActDelete->Enable();
	_menuItemListDelete->Enable();
	
	//on active le bouton préférence seulement si il y a qu'un item de sélectionner.
	if(_listItemSelected.size() == 1)
	{
		_buttonActPreferences->Enable();
		_menuItemListPreferences->Enable();
	}
	else
	{
		_buttonActPreferences->Enable(false);
		_menuItemListPreferences->Enable(false);
	}
}

bool DialogPreferences::shutdownIsToggle()const
{
	return _toggleBtnTurnOff->GetValue();
}

bool DialogPreferences::showIcon()const
{
	return _checkBoxShowMenu->GetValue();
}
		
