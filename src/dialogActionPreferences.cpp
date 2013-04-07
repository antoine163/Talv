//! \file **************************************************************
//! \brief Source Dialogue pour les préférences d'une action et sont
//! raccourci associer.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.6
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogActionPreferences.hpp"
#include "resource.hpp"

#include <wx/msgdlg.h>

//TEST
#include <iostream>

// *********************************************************************
// Class DialogActionPreferences
// *********************************************************************

DialogActionPreferences::DialogActionPreferences(wxWindow* parent)
: GuiDialogActionPreferences(parent)
{
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keySuperIsPressed = false;
	
	_shortKeyIsValide = false;
	
	
	//Ajout des actions dans les chois.
	std::map<wxString, wxString> const& actions = Resource::getInstance()->getActions();
	for(auto &it: actions)
		_choiceAction->Append(it.first);
	//Sélectionner une action par défaut.
	_choiceAction->SetSelection(0);
	
	//Installation d'un action par défaut.
	_action = nullptr;
	setUpAction(actions.at(_choiceAction->GetString(0)));
}

DialogActionPreferences::DialogActionPreferences(	wxWindow* parent,
													ShortcutKey const& inShortcutKey,
													Action const* inAct)
: GuiDialogActionPreferences(parent)
{
	//copie de l'action
	_action = Action::newAction(inAct);
	
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keySuperIsPressed = false;
	
	_shortKeyIsValide = true;
	
	//Ajout des actions dans la liste des chois.
	std::map<wxString, wxString> const& actions = Resource::getInstance()->getActions();
	for(auto &it: actions)
		_choiceAction->Append(it.first);
	//Sélectionner la bonne action.
	int n = _choiceAction->FindString(_action->getName());
	_choiceAction->SetSelection(n);
	
	//Affiche du raccourci.
	_textCtrlChortcut->SetValue(ShortcutKey::shortcutKeyToString(inShortcutKey));
	_textCtrlChortcut->SetForegroundColour(wxNullColour);
	
	//Affiche de la description de l'action
	_staticTextDescription->SetLabel(_action->getDescription());
	
	//Ajout du panel d'édition propre à l'action.
	_bSizerActPreference->Add(_action->getPanelPreferences(this, _sdbSizerOK), 1, wxEXPAND | wxALL, 5);

	//Mise a jour du dialogue.
	GetSizer()->Fit(this);
	this->Layout();
	this->Centre(wxBOTH);
}

DialogActionPreferences::~DialogActionPreferences()
{
	//Pour éviter un "Bus error (core dumped)" lorsque le panel de l'action est supprimer.
	_bSizerActPreference->Clear(true);
	
	//On suprime l'action.
	delete _action;
}

void DialogActionPreferences::OnKeyDown(wxKeyEvent& event)
{
	//Mise a jour des touches modifier
	#if defined(__UNIX__)
	switch(event.GetRawKeyFlags())
	#elif defined(__WXMSW__)
	switch(event.GetRawKeyCode())
	#endif
	{
		case RAW_KEY_CODE_MODIFIER_CONTROL:
		_keyCtrlIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_ALT:
		_keyAltIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_SHIFT:
		_keyShiftIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_SUPER:
		_keySuperIsPressed = true;
		break;
	}
	
	//Mise à jour du texte.
	_shortKeyIsValide = false;
	_textCtrlChortcut->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	updateTextCtrlChortcut(event.GetUnicodeKey());
}

void DialogActionPreferences::OnKeyUp(wxKeyEvent& event)
{
	//Mise à jour des touches modifier
	#if defined(__UNIX__)
	switch(event.GetRawKeyFlags())
	#elif defined(__WXMSW__)
	switch(event.GetRawKeyCode())
	#endif
	{
		case RAW_KEY_CODE_MODIFIER_CONTROL:
		_keyCtrlIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_ALT:
		_keyAltIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_SHIFT:
		_keyShiftIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_SUPER:
		_keySuperIsPressed = false;
		break;
	}
	
	//Mise à jour du texte.
	updateTextCtrlChortcut(event.GetUnicodeKey());
}

void DialogActionPreferences::updateTextCtrlChortcut(wxChar key)
{
	//Temps que le raccourci n'est pas valide, on met à jour le texte.
	if(!_shortKeyIsValide)
	{
		wxString strShortcut;

		if(_keyCtrlIsPressed)
			strShortcut << "ctrl";
		if(_keyAltIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "alt";
		}
		if(_keyShiftIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "shift";
		}
		if(_keySuperIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "super";
		}
			
		if(!strShortcut.IsEmpty() && key)
		{
			strShortcut << "+" << key;
			_shortKeyIsValide = true;
			_textCtrlChortcut->SetForegroundColour(wxNullColour);
			
			strShortcut.MakeLower();
			_textCtrlChortcut->SetValue(strShortcut);
		}
		else if(strShortcut.IsEmpty())
			_textCtrlChortcut->SetValue(_("Press a key modifier and a key"));
		else
		{
			strShortcut.MakeLower();
			_textCtrlChortcut->SetValue(strShortcut);
		}
	}
}

void DialogActionPreferences::OnLeftDown(wxMouseEvent&)
{
	_shortKeyIsValide = false;
	_textCtrlChortcut->SetForegroundColour( wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	_textCtrlChortcut->SetValue(_("Press a key modifier and a key"));
	_textCtrlChortcut->SetFocus();
}

void DialogActionPreferences::OnKillFocus(wxFocusEvent&)
{
	if(!_shortKeyIsValide)
		_textCtrlChortcut->SetValue(_("Click here"));
}

void DialogActionPreferences::OnChoiceAction(wxCommandEvent& event)
{
	setUpAction(Resource::getInstance()->actionsToType(event.GetString()));
}

void DialogActionPreferences::setUpAction(wxString const& actTypeName)
{
	if(_action == nullptr)
		delete _action;

	//Création d'une action a partir de son type.
	_action = Action::newAction(actTypeName);
	
	//Affiche de la description de l'action
	_staticTextDescription->SetLabel(_action->getDescription());
	
	//Ajout du panel d'édition propre à l'action.
	_bSizerActPreference->Clear(true);
	_bSizerActPreference->Add(_action->getPanelPreferences(this, _sdbSizerOK), 1, wxEXPAND | wxALL, 5);

	//Mise a jour du dialogue.
	GetSizer()->Fit(this);
	this->Layout();
	this->Centre(wxBOTH);
}

void DialogActionPreferences::OnOKButtonClick(wxCommandEvent& event)
{
	//vérifie si le raccourci est valide
	if(!_shortKeyIsValide)
	{
		wxMessageDialog dlg(this, _("The shortcut is not valid!"), _("Shortcut not valid"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
		dlg.ShowModal();
		
		return;
	}
			
	//Propage l'événement.
	event.Skip();
}

ShortcutKey DialogActionPreferences::getShortcutKey()const
{
	return ShortcutKey::stringToShortcutKey(_textCtrlChortcut->GetValue());
}

Action const* DialogActionPreferences::getAction()
{
	return _action;
}
