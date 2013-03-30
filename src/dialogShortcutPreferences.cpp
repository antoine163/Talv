//version : 1.0
//02.01.2013

#include "dialogShortcutPreferences.hpp"

//TEST
#include <iostream>

//! ****************************************************************************
//! Class DialogShortcutPreferences
//! ****************************************************************************

DialogShortcutPreferences::DialogShortcutPreferences(wxWindow* parent)
: GuiDialogShortcutPreferences(parent)
{
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keyWinIsPressed = false;
	
	_shortKeyIsValide = false;
}

DialogShortcutPreferences::DialogShortcutPreferences(	wxWindow* parent,
														ShortcutKey const& inShortcutKey,
														Action const& inAct)
: GuiDialogShortcutPreferences(parent)
{
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keyWinIsPressed = false;
	
	_shortKeyIsValide = false;
	
	//
	_textCtrlChortcut->SetValue(ShortcutKey::shortcutKeyToString(inShortcutKey));
	_textCtrlChortcut->SetForegroundColour(wxNullColour);
	
	_staticTextDescription->SetLabel(inAct.getDescription());
}

DialogShortcutPreferences::~DialogShortcutPreferences()
{
}

void DialogShortcutPreferences::OnKeyDown(wxKeyEvent& event)
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
		case RAW_KEY_CODE_MODIFIER_WIN:
		_keyWinIsPressed = true;
		break;
	}
	
	//Mise à jour du texte.
	_shortKeyIsValide = false;
	_textCtrlChortcut->SetForegroundColour( wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	updateTextCtrlChortcut(event.GetUnicodeKey());
	
	event.Skip();
}

void DialogShortcutPreferences::OnKeyUp(wxKeyEvent& event)
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
		case RAW_KEY_CODE_MODIFIER_WIN:
		_keyWinIsPressed = false;
		break;
	}
	
	//Mise à jour du texte.
	updateTextCtrlChortcut(event.GetUnicodeKey());
}

void DialogShortcutPreferences::updateTextCtrlChortcut(wxChar key)
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
		if(_keyWinIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "win";
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

void DialogShortcutPreferences::OnLeftDown(wxMouseEvent&)
{
	_shortKeyIsValide = false;
	_textCtrlChortcut->SetForegroundColour( wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	_textCtrlChortcut->SetValue(_("Press a key modifier and a key"));
	_textCtrlChortcut->SetFocus();
}

void DialogShortcutPreferences::OnKillFocus(wxFocusEvent&)
{
	if(!_shortKeyIsValide)
		_textCtrlChortcut->SetValue(_("Click here"));
}
