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

CtrlPickShortcutKey::CtrlPickShortcutKey(wxWindow* parent, ShortcutKey const& shortcutKey, bool check)
: wxWindow(parent, wxID_ANY)
{	
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keySuperIsPressed = false;
	_shortKeyIsValide = false;
	_isFocused = false;
	_check = check;
	
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
		
		if(_check)
			checkInManAction();
	}
}

ShortcutKey CtrlPickShortcutKey::getShortcutKey()
{
	return ShortcutKey();
}
#include <iostream>
//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include <X11/XKBlib.h>
void CtrlPickShortcutKey::onKeyDown(wxKeyEvent& event)
{
	std::cout << ShortcutKey::keyToString((Key_e)event.GetRawKeyCode()) << std::endl;
	
	//std::cout << event.GetRawKeyCode() << std::endl;
	//std::cout 	<< "keycode: " << event.GetRawKeyCode() << std::endl
				//<< "Keysym: " << XkbKeycodeToKeysym(XOpenDisplay(0), event.GetRawKeyFlags(), 0, 0) << std::endl
				//<< "String: " << (XKeysymToString(XkbKeycodeToKeysym(XOpenDisplay(0), event.GetRawKeyFlags(), 0, 0))) << std::endl;
				//<< "String: " << (XKeysymToString(event.GetRawKeyCode())) << std::endl;
	//if(!_isFocused)
		//return;
		
	////On passe si c'est WXK_RETURN
	//if(event.GetKeyCode() == WXK_RETURN)
	//{
		//event.Skip();
		//return;
	//}
	
	////Mise a jour des touches modifier (ne pas utiliser GetModifiers() qui pose problème quand il y a plusieurs Modifiers presser (win et atl))
	//#if defined(__UNIX__)
	//switch(event.GetRawKeyFlags())
	//#elif defined(__WXMSW__)
	//switch(event.GetRawKeyCode())
	//#endif
	//{
		//case RAW_KEY_CODE_MODIFIER_CONTROL:
		//_keyCtrlIsPressed = true;
		//break;
		//case RAW_KEY_CODE_MODIFIER_ALT:
		//_keyAltIsPressed = true;
		//break;
		//case RAW_KEY_CODE_MODIFIER_SHIFT:
		//_keyShiftIsPressed = true;
		//break;
		//case RAW_KEY_CODE_MODIFIER_SUPER:
		//_keySuperIsPressed = true;
		//break;
	//}
	
	////Mise à jour du texte.
	//_shortKeyIsValide = false;
	//_textCtrlShortcutKey->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	//updateTextCtrl(event);
}

void CtrlPickShortcutKey::onKeyUp(wxKeyEvent& event)
{	
	//if(!_isFocused)
		//return;
		
	////Mise à jour des touches modifier
	//#if defined(__UNIX__)
	//switch(event.GetRawKeyFlags())
	//#elif defined(__WXMSW__)
	//switch(event.GetRawKeyCode())
	//#endif
	//{
		//case RAW_KEY_CODE_MODIFIER_CONTROL:
		//_keyCtrlIsPressed = false;
		//break;
		//case RAW_KEY_CODE_MODIFIER_ALT:
		//_keyAltIsPressed = false;
		//break;
		//case RAW_KEY_CODE_MODIFIER_SHIFT:
		//_keyShiftIsPressed = false;
		//break;
		//case RAW_KEY_CODE_MODIFIER_SUPER:
		//_keySuperIsPressed = false;
		//break;
	//}
	
	////Mise à jour du texte.
	//updateTextCtrl(event);
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

void CtrlPickShortcutKey::updateTextCtrl(wxKeyEvent& event)
{		
	////Temps que le raccourci n'est pas valide, on met à jour le texte.
	//if(!_shortKeyIsValide)
	//{
		//char key[4] = {'\0', '\0', '\0', '\0'};
		//wxChar unicodeKey = event.GetUnicodeKey();
		//wxKeyCode keyCode = (wxKeyCode)event.GetKeyCode();
		 
		//if(	unicodeKey != WXK_NONE &&
			//((unicodeKey >= 'a' && unicodeKey <= 'z') ||
			//(unicodeKey >= 'A' && unicodeKey <= 'Z')))
		//{
			//key[0] = unicodeKey;		
		//}
		//else if(keyCode != WXK_NONE)
		//{
			//switch(keyCode)
			//{
				//case WXK_F1:
					//key[0] = 'f';
					//key[1] = '1';
				//break;	
				//case WXK_F2:
					//key[0] = 'f';
					//key[1] = '2';
				//break;	
				//case WXK_F3:
					//key[0] = 'f';
					//key[1] = '3';
				//break;	
				//case WXK_F4:
					//key[0] = 'f';
					//key[1] = '4';
				//break;	
				//case WXK_F5:
					//key[0] = 'f';
					//key[1] = '5';
				//break;	
				//case WXK_F6:
					//key[0] = 'f';
					//key[1] = '6';
				//break;	
				//case WXK_F7:
					//key[0] = 'f';
					//key[1] = '7';
				//break;	
				//case WXK_F8:
					//key[0] = 'f';
					//key[1] = '8';
				//break;	
				//case WXK_F9:
					//key[0] = 'f';
					//key[1] = '9';
				//break;	
				//case WXK_F10:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '0';
				//break; 	
				//case WXK_F11:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '1';
				//break; 	
				//case WXK_F12:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '2';
				//break; 	
				//case WXK_F13:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '3';
				//break; 	
				//case WXK_F14:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '4';
				//break; 	
				//case WXK_F15:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '5';
				//break; 	
				//case WXK_F16:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '6';
				//break; 	
				//case WXK_F17:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '7';
				//break; 	
				//case WXK_F18:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '8';
				//break; 	
				//case WXK_F19:
					//key[0] = 'f';
					//key[1] = '1';
					//key[2] = '9';
				//break; 	
				//case WXK_F20:
					//key[0] = 'f';
					//key[1] = '2';
					//key[2] = '0';
				//break;
				//case WXK_F21:
					//key[0] = 'f';
					//key[1] = '2';
					//key[2] = '1';
				//break;
				//case WXK_F22:
					//key[0] = 'f';
					//key[1] = '2';
					//key[2] = '2';
				//break;
				//case WXK_F23:
					//key[0] = 'f';
					//key[1] = '2';
					//key[2] = '3';
				//break; 
				//case WXK_F24:
					//key[0] = 'f';
					//key[1] = '2';
					//key[2] = '4';
				//break;
				
				//default:
				//break;
			//}
		//}
			
		//wxString strShortcut;

		//if(_keyCtrlIsPressed)
			//strShortcut << "ctrl";
		//if(_keyAltIsPressed)
		//{
			//if(!strShortcut.IsEmpty())
				//strShortcut << "+";
				
			//strShortcut << "alt";
		//}
		//if(_keyShiftIsPressed)
		//{
			//if(!strShortcut.IsEmpty())
				//strShortcut << "+";
				
			//strShortcut << "shift";
		//}
		//if(_keySuperIsPressed)
		//{
			//if(!strShortcut.IsEmpty())
				//strShortcut << "+";
				
			//strShortcut << "super";
		//}
			
		//if(!strShortcut.IsEmpty() && key[0] != '\0')
		//{
			//strShortcut << "+" << key;
			//_shortKeyIsValide = true;
			//_textCtrlShortcutKey->SetForegroundColour(wxNullColour);
			
			//strShortcut.MakeLower();
			//_textCtrlShortcutKey->SetValue(strShortcut);
			
			//if(_check)
				//checkInManAction();
		//}
		//else if(strShortcut.IsEmpty())
			//_textCtrlShortcutKey->SetValue(_("Press your shortcut."));
		//else
		//{
			//strShortcut.MakeLower();
			//_textCtrlShortcutKey->SetValue(strShortcut);
		//}
	//}
}

void CtrlPickShortcutKey::checkInManAction()
{
	ShortcutKey shortcutKey = getShortcutKey();
	
	if(_shortcutKeyFault == shortcutKey)
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
		