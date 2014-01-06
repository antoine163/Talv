//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 27.12.2013
//!
//! ****************************************************************************

//App
#include "control/ctrlPickShortcutKey.hpp"
#include "manager/manAction.hpp"

//WxWidgets
#include <wx/sizer.h>


// *****************************************************************************
// Class CtrlPickShortcutKey
// *****************************************************************************

CtrlPickShortcutKey::CtrlPickShortcutKey(wxWindow* parent, ShortcutKey const& shortcutKey, bool check)
: wxWindow(parent, wxID_ANY)
{	
	//Initialisation des variable
	_modPressed = MODIFIER_NONE;
	_shortKeyIsValide = false;
	_isFocused = false;
	_check = check;
	
	//Créations du wxTextCtrl
	_textCtrlShortcutKey = new wxTextCtrl(this, wxID_ANY, _("Click here!"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_textCtrlShortcutKey, 1, wxEXPAND);
	SetSizerAndFit(sizerMain);
	
	//Installation du raccourcie.
	_shortcutKeyFault = shortcutKey;
	_shortcutKey = shortcutKey;
	setShortcutKey(_shortcutKey);
	
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
	_shortcutKey = shortcutKey;
	//Si le raccourcis est valide on l'installe dans le wxTextCtrl.
	if(_shortcutKey.isOk())
	{
		_textCtrlShortcutKey->SetValue(ShortcutKey::shortcutKeyToString(shortcutKey));
		_textCtrlShortcutKey->SetForegroundColour(wxNullColour);
		
		if(_check)
			checkInManAction();
	}
	else
		_textCtrlShortcutKey->SetValue(_("Press your shortcut."));
		
}

ShortcutKey CtrlPickShortcutKey::getShortcutKey()
{
	return _shortcutKey;
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
	
	//Mise a jour du modifier
	Modifier_e _modLastPressed = MODIFIER_NONE;
	switch((Key_e)event.GetRawKeyCode())
	{
		#ifdef __UNIX__
		case KEY_CONTROL_L:
		_modPressed |= MODIFIER_CONTROL;
		_modLastPressed = MODIFIER_CONTROL;
		break;
		case KEY_ALT_L:
		_modPressed |= MODIFIER_ALT;
		_modLastPressed = MODIFIER_ALT;
		break;
		case KEY_ISO_LEVEL3_SHIFT:
		_modPressed |= MODIFIER_ALTGR;
		_modLastPressed = MODIFIER_ALTGR;
		break;
		case KEY_SHIFT_L:
		_modPressed |= MODIFIER_SHIFT;
		_modLastPressed = MODIFIER_SHIFT;
		break;
		case KEY_SUPER_L:
		_modPressed |= MODIFIER_SUPER;
		_modLastPressed = MODIFIER_SUPER;
		break;
		#endif
		#ifdef __WXMSW__
		case KEY_CONTROL:
		_modPressed |= MODIFIER_CONTROL;
		_modLastPressed = MODIFIER_CONTROL;
		break;
		case KEY_MENU:
		_modPressed |= MODIFIER_ALT;
		_modLastPressed = MODIFIER_ALT;
		break;
		case KEY_SHIFT:
		_modPressed |= MODIFIER_SHIFT;
		_modLastPressed = MODIFIER_SHIFT;
		break;
		case KEY_LWIN:
		_modPressed |= MODIFIER_SUPER;
		_modLastPressed = MODIFIER_SUPER;
		break;
		#endif
		default:
		break;
	}
	_shortcutKey.setKey((Key_e)event.GetRawKeyCode());
	_shortcutKey.setModifiers(_modPressed);
	_shortcutKey.removeModifiers(_modLastPressed);
		
	//Mise à jour du texte.
	setShortcutKey(_shortcutKey);
}

void CtrlPickShortcutKey::onKeyUp(wxKeyEvent& event)
{			
	//Mise a jour des touches modifiers
	switch((Key_e)event.GetRawKeyCode())
	{
		#ifdef __UNIX__
		case KEY_CONTROL_L:
		_modPressed &= ~MODIFIER_CONTROL;
		break;
		case KEY_ALT_L:
		_modPressed &= ~MODIFIER_ALT;
		break;
		case KEY_ISO_LEVEL3_SHIFT:
		_modPressed &= ~MODIFIER_ALTGR;
		break;
		case KEY_SHIFT_L:
		_modPressed &= ~MODIFIER_SHIFT;
		break;
		case KEY_SUPER_L:
		_modPressed &= ~MODIFIER_SUPER;
		break;
		#endif
		#ifdef __WXMSW__
		case KEY_CONTROL:
		_modPressed &= ~MODIFIER_CONTROL;
		break;
		case KEY_MENU:
		_modPressed &= ~MODIFIER_ALT;
		break;
		case KEY_SHIFT:
		_modPressed &= ~MODIFIER_SHIFT;
		break;
		case KEY_LWIN:
		_modPressed &= ~MODIFIER_SUPER;
		break;
		#endif
		default:
		break;
	}
}

void CtrlPickShortcutKey::onSetFocus(wxFocusEvent&)
{
	if(!_shortcutKey.isOk())
	{
		_textCtrlShortcutKey->SetValue(_("Press your shortcut."));
		_textCtrlShortcutKey->SetFocus();
	}
		
	_isFocused = true;
}

void CtrlPickShortcutKey::onKillFocus(wxFocusEvent&)
{
	_isFocused = false;
	if(!_shortcutKey.isOk())
		_textCtrlShortcutKey->SetValue(_("Click here!"));
}

void CtrlPickShortcutKey::checkInManAction()
{	
	if(_shortcutKeyFault == _shortcutKey)
			return;
		
	//Si le raccourcis est connue par manAction on l'affiche en rouge.
	if(ManAction::get().exist(_shortcutKey))
		_textCtrlShortcutKey->SetForegroundColour(*wxRED);
}

void CtrlPickShortcutKey::SetFocus()
{
	_textCtrlShortcutKey->SetFocus();
}
		