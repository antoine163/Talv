//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 27.12.2013
//!
//! ****************************************************************************

//App
#include "control/ctrlPickShortcutKey.hpp"
#include "manager/manAction.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/settings.h>


// *****************************************************************************
// Class CtrlPickShortcutKey
// *****************************************************************************

CtrlPickShortcutKey::CtrlPickShortcutKey(wxWindow* parent, ShortcutKey const& shortcutKey)
: wxWindow(parent, wxID_ANY)
{	
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keySuperIsPressed = false;
	_shortKeyIsValide = false;
	_isFocused = false;
	
	//Créations du wxTextCtrl
	_textCtrlShortcutKey = new wxTextCtrl(this, wxID_ANY, _("Click here!"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY);
	_textCtrlShortcutKey->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_textCtrlShortcutKey, 1, wxEXPAND);
	SetSizerAndFit(sizerMain);
	
	//Installation du raccourcie.
	_shortcutKeyFault = shortcutKey;
	setShortcutKey(shortcutKey);
	
	//Bind
	_textCtrlShortcutKey->Bind(wxEVT_KEY_DOWN, 		&CtrlPickShortcutKey::onKeyDown, 	this);
	_textCtrlShortcutKey->Bind(wxEVT_KEY_UP, 		&CtrlPickShortcutKey::onKeyUp, 		this);
	_textCtrlShortcutKey->Bind(wxEVT_SET_FOCUS, 	&CtrlPickShortcutKey::onSetFocus, 	this);
	_textCtrlShortcutKey->Bind(wxEVT_KILL_FOCUS, 	&CtrlPickShortcutKey::onKillFocus, 	this);
}

CtrlPickShortcutKey::~CtrlPickShortcutKey()
{
	//Unbind
	_textCtrlShortcutKey->Unbind(wxEVT_KEY_DOWN, 	&CtrlPickShortcutKey::onKeyDown, 	this);
	_textCtrlShortcutKey->Unbind(wxEVT_KEY_UP, 		&CtrlPickShortcutKey::onKeyUp, 		this);
	_textCtrlShortcutKey->Unbind(wxEVT_SET_FOCUS, 	&CtrlPickShortcutKey::onSetFocus, 	this);
	_textCtrlShortcutKey->Unbind(wxEVT_KILL_FOCUS, 	&CtrlPickShortcutKey::onKillFocus, 	this);
}

void CtrlPickShortcutKey::setShortcutKey(ShortcutKey const& shortcutKey)
{
	//Si le raccourcis est valide on l'installe dans le wxTextCtrl.
	if(shortcutKey.isOk())
	{
		_textCtrlShortcutKey->SetValue(ShortcutKey::shortcutKeyToString(shortcutKey));
		_shortKeyIsValide = true;
		_textCtrlShortcutKey->SetForegroundColour(wxNullColour);
		
		checkInManAction();
	}
}

ShortcutKey CtrlPickShortcutKey::getShortcutKey()
{
	return ShortcutKey::stringToShortcutKey(_textCtrlShortcutKey->GetValue());
}

void CtrlPickShortcutKey::onKeyDown(wxKeyEvent& event)
{
	if(!_isFocused)
		return;
		
	//On passe si c'est WXK_RETURN
	if(event.GetKeyCode() == WXK_RETURN)
	{
		event.Skip();
		return;
	}
	
	//Mise a jour des touches modifier (ne pas utiliser GetModifiers() qui pose problème quand il y a plusieurs Modifiers presser (win et atl))
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
	_textCtrlShortcutKey->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	updateTextCtrl(event.GetUnicodeKey());
}

void CtrlPickShortcutKey::onKeyUp(wxKeyEvent& event)
{	
	if(!_isFocused)
		return;
		
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
	updateTextCtrl(event.GetUnicodeKey());
}

void CtrlPickShortcutKey::onSetFocus(wxFocusEvent&)
{
	if(!_shortKeyIsValide)
	{
		_textCtrlShortcutKey->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
		_textCtrlShortcutKey->SetValue(_("Press your shortcut."));
		_textCtrlShortcutKey->SetFocus();
	}
		
	_isFocused = true;
}

void CtrlPickShortcutKey::onKillFocus(wxFocusEvent&)
{
	_isFocused = false;;
	if(!_shortKeyIsValide)
		_textCtrlShortcutKey->SetValue(_("Click here!"));
}

void CtrlPickShortcutKey::updateTextCtrl(wxChar key)
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
			_textCtrlShortcutKey->SetForegroundColour(wxNullColour);
			
			strShortcut.MakeLower();
			_textCtrlShortcutKey->SetValue(strShortcut);
			
			checkInManAction();
		}
		else if(strShortcut.IsEmpty())
			_textCtrlShortcutKey->SetValue(_("Press your shortcut."));
		else
		{
			strShortcut.MakeLower();
			_textCtrlShortcutKey->SetValue(strShortcut);
		}
	}
}

void CtrlPickShortcutKey::checkInManAction()
{
	ShortcutKey shortcutKey = getShortcutKey();
	
	if(_shortcutKeyFault == shortcutKey || !_shortcutKeyFault.isOk())
			return;
		
	//Si le raccourcis est connue par manAction on l'affiche en rouge.
	for(auto it: ManAction::get().getShortcutKeysActions())
	{
		if(shortcutKey == it.first)
		{
			_textCtrlShortcutKey->SetForegroundColour(*wxRED);
			return;
		}
	}
}

void CtrlPickShortcutKey::SetFocus()
{
	_textCtrlShortcutKey->SetFocus();
}
		