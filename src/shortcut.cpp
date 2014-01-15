//! \file **********************************************************************
//! \brief Source Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie.
//! \version 2.0
//! \date 13.12.12
//!
//! ****************************************************************************

//App
#include "shortcut.hpp"

#if defined(__UNIX__)
#include <X11/XKBlib.h>
#endif

// *****************************************************************************
// Class ShortcutKey
// *****************************************************************************

ShortcutKey::ShortcutKey()
{
	setModifiers(MODIFIER_NONE);
	setKey(KEY_NONE);
}

ShortcutKey::ShortcutKey(Modifier_e modifiers, Key_e key)
{
	setModifiers(modifiers);
	setKey(key);
}

bool ShortcutKey::operator<(ShortcutKey const& ins)const
{
	if(_key < ins._key)
		return true;
	else if(_key == ins._key)
	{
		if(_modifiers < ins._modifiers)
			return true;
	}
	
	return false;
}

bool ShortcutKey::operator==(ShortcutKey const& ins)const
{
	if((_modifiers == ins._modifiers) && (_key == ins._key))
		return true;
		
	return false;
}

bool ShortcutKey::operator!=(ShortcutKey const& ins)const
{
	if((_modifiers != ins._modifiers) || (_key != ins._key))
		return true;
		
	return false;
}

Key_e ShortcutKey::getKey()const
{
	return _key;
}

void ShortcutKey::setKey(Key_e key)
{
	#ifdef __UNIX__
	Display* display = (Display*)wxGetDisplay();
	KeyCode keyCode = XKeysymToKeycode(display, (KeySym)key);
	KeySym keySym = XkbKeycodeToKeysym(display, keyCode, 0, 0);
	_key = (Key_e)keySym;
	#elif __WXMSW__
	_key = key;
	#endif
}

Modifier_e ShortcutKey::getModifiers()const
{
	return _modifiers;
}
void ShortcutKey::setModifiers(Modifier_e mod)
{
	_modifiers = mod;
}

void ShortcutKey::addModifiers(Modifier_e mod)
{
	_modifiers |= mod;
}

void ShortcutKey::removeModifiers(Modifier_e mod)
{
	_modifiers &= ~mod;
}

bool ShortcutKey::isOk()const
{
	if(_key == KEY_NONE)
		return false;
		
	return true;
}

wxString ShortcutKey::shortcutKeyToString(ShortcutKey const& shortcut)
{	
	wxString r;
	
	// ShortcutKey valide ?
	if(!shortcut.isOk())
		return wxEmptyString;
	
	//Conversion du modificateur.	
	wxString strModifier;
	strModifier = modifierToString(shortcut._modifiers&MODIFIER_CONTROL);
	r << strModifier;
	
	strModifier = modifierToString(shortcut._modifiers&MODIFIER_ALT);
	if(!r.IsEmpty() && !strModifier.IsEmpty())
		r << '+';
	r << strModifier;
		
	strModifier = modifierToString(shortcut._modifiers&MODIFIER_ALTGR);
	if(!r.IsEmpty() && !strModifier.IsEmpty())
		r << '+';
	r << strModifier;
	
	strModifier = modifierToString(shortcut._modifiers&MODIFIER_SHIFT);
	if(!r.IsEmpty() && !strModifier.IsEmpty())
		r << '+';
	r << strModifier;
	
	strModifier = modifierToString(shortcut._modifiers&MODIFIER_SUPER);
	if(!r.IsEmpty() && !strModifier.IsEmpty())
		r << '+';
	r << strModifier;
	
	//Conversion de la touche.
	if(!r.IsEmpty())
		r << '+';
	r << keyToString(shortcut._key);
	
	return r;
}

ShortcutKey ShortcutKey::stringToShortcutKey(wxString const& shortcut)
{
	
	Modifier_e modifiers = MODIFIER_NONE;
	Key_e key = KEY_NONE;
	
	//Avent ou après le premier '+'.
	wxString before;
	wxString after;
	
	//Obtenir avant ou après le premier '+'.
	before = shortcut.BeforeFirst('+', &after);
	
	//Conversion du modificateur.
	while(!after.IsEmpty())
	{				
		Modifier_e mtmp = stringToModifier(before);
		if(mtmp == MODIFIER_NONE)//Raccourci erronée.
			return ShortcutKey(MODIFIER_NONE, KEY_NONE);
			
		modifiers |= mtmp;
		
		//Obtenir le nouveau avent ou après le premier '+'
		wxString stmp = after;
		before = stmp.BeforeFirst('+', &after);
	}
	
	key = stringToKey(before);
	if(key == KEY_NONE)//Raccourci erronée.
		return ShortcutKey(MODIFIER_NONE, KEY_NONE);
	
	return ShortcutKey(modifiers, key);
}

wxString ShortcutKey::modifierToString(Modifier_e modifier)
{
	if(modifier == MODIFIER_CONTROL)
		return "Ctrl";
	if(modifier == MODIFIER_ALT)
		return "Alt";
	#ifdef __UNIX__
	if(modifier == MODIFIER_ALTGR)
		return "Altgr";
	#endif
	if(modifier == MODIFIER_SHIFT)
		return "Shift";
	if(modifier == MODIFIER_SUPER)
		return "Super";
		
	return wxEmptyString;
}

Modifier_e ShortcutKey::stringToModifier(wxString modifier)
{
	modifier.MakeLower();
	
	if(modifier == "ctrl")
		return MODIFIER_CONTROL;
	if(modifier == "alt")
		return MODIFIER_ALT;
	#ifdef __UNIX__
	if(modifier == "altgr")
		return MODIFIER_ALTGR;
	#endif
	if(modifier == "shift")
		return MODIFIER_SHIFT;
	if(modifier == "super")
		return MODIFIER_SUPER;
		
	return MODIFIER_NONE;
}

wxArrayString ShortcutKey::getModifiersStrings()
{
	wxArrayString r;
	r.Add("Ctrl");
	r.Add("Alt");
	#ifdef __UNIX__
	r.Add("Altgr");
	#endif
	r.Add("Shift");
	r.Add("Super");
	return r;
}

wxString ShortcutKey::keyToString(Key_e key)
{
	#ifdef __UNIX__
	Display* display = (Display*)wxGetDisplay();
	KeyCode keyCode = XKeysymToKeycode(display, (KeySym)key);
	KeySym keySym = XkbKeycodeToKeysym(display, keyCode, 0, 0);
	return XKeysymToString(keySym);
	#elif __WXMSW__
	if(KEY_CANCEL)
		return "Cancel";
	if(KEY_BACK)
		return "Back";
	if(KEY_TAB)
		return "Tab";
	if(KEY_CLEAR)
		return "Clear";
	if(KEY_RETURN)
		return "Return";
	if(KEY_SHIFT)
		return "Shift";
	if(KEY_CONTROL)
		return "Control";
	if(KEY_MENU)
		return "Menu";
	if(KEY_PAUSE)
		return "Pause";
	if(KEY_CAPITAL)
		return "Capital";
	if(KEY_KANA)
		return "Kana";
	if(KEY_HANGEUL)
		return "Hangeul";
	if(KEY_HANGUL)
		return "Hangul";
	if(KEY_JUNJA)
		return "Junja";
	if(KEY_FINAL)
		return "Final";
	if(KEY_HANJA)
		return "Hanja";
	if(KEY_KANJI)
		return "Kanji";
	if(KEY_ESCAPE)
		return "Escape";
	if(KEY_CONVERT)
		return "Convert";
	if(KEY_NONCONVERT)
		return "Nonconvert";
	if(KEY_ACCEPT)
		return "Accept";
	if(KEY_MODECHANGE)
		return "Modechange";
	if(KEY_SPACE)
		return "Space";
	if(KEY_PRIOR)
		return "Prior";
	if(KEY_NEXT)
		return "Next";
	if(KEY_END)
		return "End";
	if(KEY_HOME)
		return "Home";
	if(KEY_LEFT)
		return "Left";
	if(KEY_UP)
		return "Up";
	if(KEY_RIGHT)
		return "Right";
	if(KEY_DOWN)
		return "Down";
	if(KEY_SELECT)
		return "Select";
	if(KEY_PRINT)
		return "Print";
	if(KEY_EXECUTE)
		return "Execute";
	if(KEY_SNAPSHOT)
		return "Snapshot";
	if(KEY_INSERT)
		return "Insert";
	if(KEY_DELETE)
		return "Delete";
	if(KEY_HELP)
		return "Help";
	if(KEY_LWIN)
		return "Lwin";
	if(KEY_RWIN)
		return "Rwin";
	if(KEY_APPS)
		return "Apps";
	if(KEY_SLEEP)
		return "Sleep";
	if(KEY_NUMPAD0)
		return "Numpad0";
	if(KEY_NUMPAD1)
		return "Numpad1";
	if(KEY_NUMPAD2)
		return "Numpad2";
	if(KEY_NUMPAD3)
		return "Numpad3";
	if(KEY_NUMPAD4)
		return "Numpad4";
	if(KEY_NUMPAD5)
		return "Numpad5";
	if(KEY_NUMPAD6)
		return "Numpad6";
	if(KEY_NUMPAD7)
		return "Numpad7";
	if(KEY_NUMPAD8)
		return "Numpad8";
	if(KEY_NUMPAD9)
		return "Numpad9";
	if(KEY_MULTIPLY)
		return "Multiply";
	if(KEY_ADD)
		return "Add";
	if(KEY_SEPARATOR)
		return "Separator";
	if(KEY_SUBTRACT)
		return "Subtract";
	if(KEY_DECIMAL)
		return "Decimal";
	if(KEY_DIVIDE)
		return "Divide";
	if(KEY_F1)
		return "F1";
	if(KEY_F2)
		return "F2";
	if(KEY_F3)
		return "F3";
	if(KEY_F4)
		return "F4";
	if(KEY_F5)
		return "F5";
	if(KEY_F6)
		return "F6";
	if(KEY_F7)
		return "F7";
	if(KEY_F8)
		return "F8";
	if(KEY_F9)
		return "F9";
	if(KEY_F10)
		return "F10";
	if(KEY_F11)
		return "F11";
	if(KEY_F12)
		return "F12";
	if(KEY_F13)
		return "F13";
	if(KEY_F14)
		return "F14";
	if(KEY_F15)
		return "F15";
	if(KEY_F16)
		return "F16";
	if(KEY_F17)
		return "F17";
	if(KEY_F18)
		return "F18";
	if(KEY_F19)
		return "F19";
	if(KEY_F20)
		return "F20";
	if(KEY_F21)
		return "F21";
	if(KEY_F22)
		return "F22";
	if(KEY_F23)
		return "F23";
	if(KEY_F24)
		return "F24";
	if(KEY_NUMLOCK)
		return "Numlock";
	if(KEY_SCROLL)
		return "Scroll";
	if(KEY_OEM_NEC_EQUAL)
		return "Oem_nec_equal";
	if(KEY_OEM_FJ_JISHO)
		return "Oem_fj_jisho";
	if(KEY_OEM_FJ_MASSHOU)
		return "Oem_fj_masshou";
	if(KEY_OEM_FJ_TOUROKU)
		return "Oem_fj_touroku";
	if(KEY_OEM_FJ_LOYA)
		return "Oem_fj_loya";
	if(KEY_OEM_FJ_ROYA)
		return "Oem_fj_roya";
	if(KEY_LSHIFT)
		return "Lshift";
	if(KEY_RSHIFT)
		return "Rshift";
	if(KEY_LCONTROL)
		return "Lcontrol";
	if(KEY_RCONTROL)
		return "Rcontrol";
	if(KEY_LMENU)
		return "Lmenu";
	if(KEY_RMENU)
		return "Rmenu";
	if(KEY_BROWSER_BACK)
		return "Browser_back";
	if(KEY_BROWSER_FORWARD)
		return "Browser_forward";
	if(KEY_BROWSER_REFRESH)
		return "Browser_refresh";
	if(KEY_BROWSER_STOP)
		return "Browser_stop";
	if(KEY_BROWSER_SEARCH)
		return "Browser_search";
	if(KEY_BROWSER_FAVORITES)
		return "Browser_favorites";
	if(KEY_BROWSER_HOME)
		return "Browser_home";
	if(KEY_VOLUME_MUTE)
		return "Volume_mute";
	if(KEY_VOLUME_DOWN)
		return "Volume_down";
	if(KEY_VOLUME_UP)
		return "Volume_up";
	if(KEY_MEDIA_NEXT_TRACK)
		return "Media_next_track";
	if(KEY_MEDIA_PREV_TRACK)
		return "Media_prev_track";
	if(KEY_MEDIA_STOP)
		return "Media_stop";
	if(KEY_MEDIA_PLAY_PAUSE)
		return "Media_play_pause";
	if(KEY_LAUNCH_MAIL)
		return "Launch_mail";
	if(KEY_LAUNCH_MEDIA_SELECT)
		return "Launch_media_select";
	if(KEY_LAUNCH_APP1)
		return "Launch_app1";
	if(KEY_LAUNCH_APP2)
		return "Launch_app2";
	if(KEY_OEM_1)
		return "Oem_1";
	if(KEY_OEM_PLUS)
		return "Oem_plus";
	if(KEY_OEM_COMMA)
		return "Oem_comma";
	if(KEY_OEM_MINUS)
		return "Oem_minus";
	if(KEY_OEM_PERIOD)
		return "Oem_period";
	if(KEY_OEM_2)
		return "Oem_2";
	if(KEY_OEM_3)
		return "Oem_3";
	if(KEY_OEM_4)
		return "Oem_4";
	if(KEY_OEM_5)
		return "Oem_5";
	if(KEY_OEM_6)
		return "Oem_6";
	if(KEY_OEM_7)
		return "Oem_7";
	if(KEY_OEM_8)
		return "Oem_8";
	if(KEY_OEM_AX)
		return "Oem_ax";
	if(KEY_OEM_102)
		return "Oem_102";
	if(KEY_ICO_HELP)
		return "Ico_help";
	if(KEY_ICO_00)
		return "Ico_00";
	if(KEY_PROCESSKEY)
		return "Processkey";
	if(KEY_ICO_CLEAR)
		return "Ico_clear";
	if(KEY_PACKET)
		return "Packet";
	if(KEY_OEM_RESET)
		return "Oem_reset";
	if(KEY_OEM_JUMP)
		return "Oem_jump";
	if(KEY_OEM_PA1)
		return "Oem_pa1";
	if(KEY_OEM_PA2)
		return "Oem_pa2";
	if(KEY_OEM_PA3)
		return "Oem_pa3";
	if(KEY_OEM_WSCTRL)
		return "Oem_wsctrl";
	if(KEY_OEM_CUSEL)
		return "Oem_cusel";
	if(KEY_OEM_ATTN)
		return "Oem_attn";
	if(KEY_OEM_FINISH)
		return "Oem_finish";
	if(KEY_OEM_COPY)
		return "Oem_copy";
	if(KEY_OEM_AUTO)
		return "Oem_auto";
	if(KEY_OEM_ENLW)
		return "Oem_enlw";
	if(KEY_OEM_BACKTAB)
		return "Oem_backtab";
	if(KEY_ATTN)
		return "Attn";
	if(KEY_CRSEL)
		return "Crsel";
	if(KEY_EXSEL)
		return "Exsel";
	if(KEY_EREOF)
		return "Ereof";
	if(KEY_PLAY)
		return "Play";
	if(KEY_ZOOM)
		return "Zoom";
	if(KEY_NONAME)
		return "Noname";
	if(KEY_PA1)
		return "Pa1";
	if(KEY_OEM_CLEAR)
		return "Oem_clear";
	if(KEY_A)
		return "A";
	if(KEY_B)
		return "B";
	if(KEY_C)
		return "C";
	if(KEY_D)
		return "D";
	if(KEY_E)
		return "E";
	if(KEY_F)
		return "F";
	if(KEY_G)
		return "G";
	if(KEY_H)
		return "H";
	if(KEY_I)
		return "I";
	if(KEY_J)
		return "J";
	if(KEY_K)
		return "K";
	if(KEY_L)
		return "L";
	if(KEY_M)
		return "M";
	if(KEY_N)
		return "N";
	if(KEY_O)
		return "O";
	if(KEY_P)
		return "P";
	if(KEY_Q)
		return "Q";
	if(KEY_R)
		return "R";
	if(KEY_S)
		return "S";
	if(KEY_T)
		return "T";
	if(KEY_U)
		return "U";
	if(KEY_V)
		return "V";
	if(KEY_W)
		return "W";
	if(KEY_X)
		return "X";
	if(KEY_Y)
		return "Y";
	if(KEY_Z)
		return "Z";
	}
	#endif

	return wxEmptyString;
}

Key_e ShortcutKey::stringToKey(wxString key)
{
	key.MakeUpper();
	#ifdef __UNIX__
	KeySym keySym = XStringToKeysym(key.c_str());
	if(keySym == NoSymbol)
		return KEY_NONE;
	else
	{
		Display* display = (Display*)wxGetDisplay();
		KeyCode keyCode = XKeysymToKeycode(display, keySym);
		keySym = XkbKeycodeToKeysym(display, keyCode, 0, 0);
		return (Key_e)keySym;
	}
	#elif __WXMSW__
	if(key == "CANCEL")
		return KEY_CANCEL;
	if(key == "BACK")
		return KEY_BACK;
	if(key == "TAB")
		return KEY_TAB;
	if(key == "CLEAR")
		return KEY_CLEAR;
	if(key == "RETURN")
		return KEY_RETURN;
	if(key == "SHIFT")
		return KEY_SHIFT;
	if(key == "CONTROL")
		return KEY_CONTROL;
	if(key == "MENU")
		return KEY_MENU;
	if(key == "PAUSE")
		return KEY_PAUSE;
	if(key == "CAPITAL")
		return KEY_CAPITAL;
	if(key == "KANA")
		return KEY_KANA;
	if(key == "HANGEUL")
		return KEY_HANGEUL;
	if(key == "HANGUL")
		return KEY_HANGUL;
	if(key == "JUNJA")
		return KEY_JUNJA;
	if(key == "FINAL")
		return KEY_FINAL;
	if(key == "HANJA")
		return KEY_HANJA;
	if(key == "KANJI")
		return KEY_KANJI;
	if(key == "ESCAPE")
		return KEY_ESCAPE;
	if(key == "CONVERT")
		return KEY_CONVERT;
	if(key == "NONCONVERT")
		return KEY_NONCONVERT;
	if(key == "ACCEPT")
		return KEY_ACCEPT;
	if(key == "MODECHANGE")
		return KEY_MODECHANGE;
	if(key == "SPACE")
		return KEY_SPACE;
	if(key == "PRIOR")
		return KEY_PRIOR;
	if(key == "NEXT")
		return KEY_NEXT;
	if(key == "END")
		return KEY_END;
	if(key == "HOME")
		return KEY_HOME;
	if(key == "LEFT")
		return KEY_LEFT;
	if(key == "UP")
		return KEY_UP;
	if(key == "RIGHT")
		return KEY_RIGHT;
	if(key == "DOWN")
		return KEY_DOWN;
	if(key == "SELECT")
		return KEY_SELECT;
	if(key == "PRINT")
		return KEY_PRINT;
	if(key == "EXECUTE")
		return KEY_EXECUTE;
	if(key == "SNAPSHOT")
		return KEY_SNAPSHOT;
	if(key == "INSERT")
		return KEY_INSERT;
	if(key == "DELETE")
		return KEY_DELETE;
	if(key == "HELP")
		return KEY_HELP;
	if(key == "LWIN")
		return KEY_LWIN;
	if(key == "RWIN")
		return KEY_RWIN;
	if(key == "APPS")
		return KEY_APPS;
	if(key == "SLEEP")
		return KEY_SLEEP;
	if(key == "NUMPAD0")
		return KEY_NUMPAD0;
	if(key == "NUMPAD1")
		return KEY_NUMPAD1;
	if(key == "NUMPAD2")
		return KEY_NUMPAD2;
	if(key == "NUMPAD3")
		return KEY_NUMPAD3;
	if(key == "NUMPAD4")
		return KEY_NUMPAD4;
	if(key == "NUMPAD5")
		return KEY_NUMPAD5;
	if(key == "NUMPAD6")
		return KEY_NUMPAD6;
	if(key == "NUMPAD7")
		return KEY_NUMPAD7;
	if(key == "NUMPAD8")
		return KEY_NUMPAD8;
	if(key == "NUMPAD9")
		return KEY_NUMPAD9;
	if(key == "MULTIPLY")
		return KEY_MULTIPLY;
	if(key == "ADD")
		return KEY_ADD;
	if(key == "SEPARATOR")
		return KEY_SEPARATOR;
	if(key == "SUBTRACT")
		return KEY_SUBTRACT;
	if(key == "DECIMAL")
		return KEY_DECIMAL;
	if(key == "DIVIDE")
		return KEY_DIVIDE;
	if(key == "F1")
		return KEY_F1;
	if(key == "F2")
		return KEY_F2;
	if(key == "F3")
		return KEY_F3;
	if(key == "F4")
		return KEY_F4;
	if(key == "F5")
		return KEY_F5;
	if(key == "F6")
		return KEY_F6;
	if(key == "F7")
		return KEY_F7;
	if(key == "F8")
		return KEY_F8;
	if(key == "F9")
		return KEY_F9;
	if(key == "F10")
		return KEY_F10;
	if(key == "F11")
		return KEY_F11;
	if(key == "F12")
		return KEY_F12;
	if(key == "F13")
		return KEY_F13;
	if(key == "F14")
		return KEY_F14;
	if(key == "F15")
		return KEY_F15;
	if(key == "F16")
		return KEY_F16;
	if(key == "F17")
		return KEY_F17;
	if(key == "F18")
		return KEY_F18;
	if(key == "F19")
		return KEY_F19;
	if(key == "F20")
		return KEY_F20;
	if(key == "F21")
		return KEY_F21;
	if(key == "F22")
		return KEY_F22;
	if(key == "F23")
		return KEY_F23;
	if(key == "F24")
		return KEY_F24;
	if(key == "NUMLOCK")
		return KEY_NUMLOCK;
	if(key == "SCROLL")
		return KEY_SCROLL;
	if(key == "OEM_NEC_EQUAL")
		return KEY_OEM_NEC_EQUAL;
	if(key == "OEM_FJ_JISHO")
		return KEY_OEM_FJ_JISHO;
	if(key == "OEM_FJ_MASSHOU")
		return KEY_OEM_FJ_MASSHOU;
	if(key == "OEM_FJ_TOUROKU")
		return KEY_OEM_FJ_TOUROKU;
	if(key == "OEM_FJ_LOYA")
		return KEY_OEM_FJ_LOYA;
	if(key == "OEM_FJ_ROYA")
		return KEY_OEM_FJ_ROYA;
	if(key == "LSHIFT")
		return KEY_LSHIFT;
	if(key == "RSHIFT")
		return KEY_RSHIFT;
	if(key == "LCONTROL")
		return KEY_LCONTROL;
	if(key == "RCONTROL")
		return KEY_RCONTROL;
	if(key == "LMENU")
		return KEY_LMENU;
	if(key == "RMENU")
		return KEY_RMENU;
	if(key == "BROWSER_BACK")
		return KEY_BROWSER_BACK;
	if(key == "BROWSER_FORWARD")
		return KEY_BROWSER_FORWARD;
	if(key == "BROWSER_REFRESH")
		return KEY_BROWSER_REFRESH;
	if(key == "BROWSER_STOP")
		return KEY_BROWSER_STOP;
	if(key == "BROWSER_SEARCH")
		return KEY_BROWSER_SEARCH;
	if(key == "BROWSER_FAVORITES")
		return KEY_BROWSER_FAVORITES;
	if(key == "BROWSER_HOME")
		return KEY_BROWSER_HOME;
	if(key == "VOLUME_MUTE")
		return KEY_VOLUME_MUTE;
	if(key == "VOLUME_DOWN")
		return KEY_VOLUME_DOWN;
	if(key == "VOLUME_UP")
		return KEY_VOLUME_UP;
	if(key == "MEDIA_NEXT_TRACK")
		return KEY_MEDIA_NEXT_TRACK;
	if(key == "MEDIA_PREV_TRACK")
		return KEY_MEDIA_PREV_TRACK;
	if(key == "MEDIA_STOP")
		return KEY_MEDIA_STOP;
	if(key == "MEDIA_PLAY_PAUSE")
		return KEY_MEDIA_PLAY_PAUSE;
	if(key == "LAUNCH_MAIL")
		return KEY_LAUNCH_MAIL;
	if(key == "LAUNCH_MEDIA_SELECT")
		return KEY_LAUNCH_MEDIA_SELECT;
	if(key == "LAUNCH_APP1")
		return KEY_LAUNCH_APP1;
	if(key == "LAUNCH_APP2")
		return KEY_LAUNCH_APP2;
	if(key == "OEM_1")
		return KEY_OEM_1;
	if(key == "OEM_PLUS")
		return KEY_OEM_PLUS;
	if(key == "OEM_COMMA")
		return KEY_OEM_COMMA;
	if(key == "OEM_MINUS")
		return KEY_OEM_MINUS;
	if(key == "OEM_PERIOD")
		return KEY_OEM_PERIOD;
	if(key == "OEM_2")
		return KEY_OEM_2;
	if(key == "OEM_3")
		return KEY_OEM_3;
	if(key == "OEM_4")
		return KEY_OEM_4;
	if(key == "OEM_5")
		return KEY_OEM_5;
	if(key == "OEM_6")
		return KEY_OEM_6;
	if(key == "OEM_7")
		return KEY_OEM_7;
	if(key == "OEM_8")
		return KEY_OEM_8;
	if(key == "OEM_AX")
		return KEY_OEM_AX;
	if(key == "OEM_102")
		return KEY_OEM_102;
	if(key == "ICO_HELP")
		return KEY_ICO_HELP;
	if(key == "ICO_00")
		return KEY_ICO_00;
	if(key == "PROCESSKEY")
		return KEY_PROCESSKEY;
	if(key == "ICO_CLEAR")
		return KEY_ICO_CLEAR;
	if(key == "PACKET")
		return KEY_PACKET;
	if(key == "OEM_RESET")
		return KEY_OEM_RESET;
	if(key == "OEM_JUMP")
		return KEY_OEM_JUMP;
	if(key == "OEM_PA1")
		return KEY_OEM_PA1;
	if(key == "OEM_PA2")
		return KEY_OEM_PA2;
	if(key == "OEM_PA3")
		return KEY_OEM_PA3;
	if(key == "OEM_WSCTRL")
		return KEY_OEM_WSCTRL;
	if(key == "OEM_CUSEL")
		return KEY_OEM_CUSEL;
	if(key == "OEM_ATTN")
		return KEY_OEM_ATTN;
	if(key == "OEM_FINISH")
		return KEY_OEM_FINISH;
	if(key == "OEM_COPY")
		return KEY_OEM_COPY;
	if(key == "OEM_AUTO")
		return KEY_OEM_AUTO;
	if(key == "OEM_ENLW")
		return KEY_OEM_ENLW;
	if(key == "OEM_BACKTAB")
		return KEY_OEM_BACKTAB;
	if(key == "ATTN")
		return KEY_ATTN;
	if(key == "CRSEL")
		return KEY_CRSEL;
	if(key == "EXSEL")
		return KEY_EXSEL;
	if(key == "EREOF")
		return KEY_EREOF;
	if(key == "PLAY")
		return KEY_PLAY;
	if(key == "ZOOM")
		return KEY_ZOOM;
	if(key == "NONAME")
		return KEY_NONAME;
	if(key == "PA1")
		return KEY_PA1;
	if(key == "OEM_CLEAR")
		return KEY_OEM_CLEAR;
	if(key == KEY_A)
		return "A";
	if(key == KEY_B)
		return "B";
	if(key == KEY_C)
		return "C";
	if(key == KEY_D)
		return "D";
	if(key == KEY_E)
		return "E";
	if(key == KEY_F)
		return "F";
	if(key == KEY_G)
		return "G";
	if(key == KEY_H)
		return "H";
	if(key == KEY_I)
		return "I";
	if(key == KEY_J)
		return "J";
	if(key == KEY_K)
		return "K";
	if(key == KEY_L)
		return "L";
	if(key == KEY_M)
		return "M";
	if(key == KEY_N)
		return "N";
	if(key == KEY_O)
		return "O";
	if(key == KEY_P)
		return "P";
	if(key == KEY_Q)
		return "Q";
	if(key == KEY_R)
		return "R";
	if(key == KEY_S)
		return "S";
	if(key == KEY_T)
		return "T";
	if(key == KEY_U)
		return "U";
	if(key == KEY_V)
		return "V";
	if(key == KEY_W)
		return "W";
	if(key == KEY_X)
		return "X";
	if(key == KEY_Y)
		return "Y";
	if(key == KEY_Z)
		return "Z";
	#endif

	return KEY_NONE;
}

wxArrayString ShortcutKey::getKeysStrings()
{
	wxArrayString r;

	#ifdef __UNIX__
	#ifdef XK_3270
	r.Add(keyToString(KEY_3270_DUPLICATE));
	r.Add(keyToString(KEY_3270_FIELDMARK));
	r.Add(keyToString(KEY_3270_RIGHT2));
	r.Add(keyToString(KEY_3270_LEFT2));
	r.Add(keyToString(KEY_3270_BACKTAB));
	r.Add(keyToString(KEY_3270_ERASEEOF));
	r.Add(keyToString(KEY_3270_ERASEINPUT));
	r.Add(keyToString(KEY_3270_RESET));
	r.Add(keyToString(KEY_3270_QUIT));
	r.Add(keyToString(KEY_3270_PA1));
	r.Add(keyToString(KEY_3270_PA2));
	r.Add(keyToString(KEY_3270_PA3));
	r.Add(keyToString(KEY_3270_TEST));
	r.Add(keyToString(KEY_3270_ATTN));
	r.Add(keyToString(KEY_3270_CURSORBLINK));
	r.Add(keyToString(KEY_3270_ALTCURSOR));
	r.Add(keyToString(KEY_3270_KEYCLICK));
	r.Add(keyToString(KEY_3270_JUMP));
	r.Add(keyToString(KEY_3270_IDENT));
	r.Add(keyToString(KEY_3270_RULE));
	r.Add(keyToString(KEY_3270_COPY));
	r.Add(keyToString(KEY_3270_PLAY));
	r.Add(keyToString(KEY_3270_SETUP));
	r.Add(keyToString(KEY_3270_RECORD));
	r.Add(keyToString(KEY_3270_CHANGESCREEN));
	r.Add(keyToString(KEY_3270_DELETEWORD));
	r.Add(keyToString(KEY_3270_EXSELECT));
	r.Add(keyToString(KEY_3270_CURSORSELECT));
	r.Add(keyToString(KEY_3270_PRINTSCREEN));
	r.Add(keyToString(KEY_3270_ENTER));
	#endif
	#ifdef XK_APL
	r.Add(keyToString(KEY_LEFTCARET));
	r.Add(keyToString(KEY_RIGHTCARET));
	r.Add(keyToString(KEY_DOWNCARET));
	r.Add(keyToString(KEY_UPCARET));
	r.Add(keyToString(KEY_OVERBAR));
	r.Add(keyToString(KEY_DOWNTACK));
	r.Add(keyToString(KEY_UPSHOE));
	r.Add(keyToString(KEY_DOWNSTILE));
	r.Add(keyToString(KEY_UNDERBAR));
	r.Add(keyToString(KEY_JOT));
	r.Add(keyToString(KEY_QUAD));
	r.Add(keyToString(KEY_UPTACK));
	r.Add(keyToString(KEY_CIRCLE));
	r.Add(keyToString(KEY_UPSTILE));
	r.Add(keyToString(KEY_DOWNSHOE));
	r.Add(keyToString(KEY_RIGHTSHOE));
	r.Add(keyToString(KEY_LEFTSHOE));
	r.Add(keyToString(KEY_LEFTTACK));
	r.Add(keyToString(KEY_RIGHTTACK));
	#endif
	#ifdef XK_ARABIC
	r.Add(keyToString(KEY_FARSI_0));
	r.Add(keyToString(KEY_FARSI_1));
	r.Add(keyToString(KEY_FARSI_2));
	r.Add(keyToString(KEY_FARSI_3));
	r.Add(keyToString(KEY_FARSI_4));
	r.Add(keyToString(KEY_FARSI_5));
	r.Add(keyToString(KEY_FARSI_6));
	r.Add(keyToString(KEY_FARSI_7));
	r.Add(keyToString(KEY_FARSI_8));
	r.Add(keyToString(KEY_FARSI_9));
	r.Add(keyToString(KEY_ARABIC_PERCENT));
	r.Add(keyToString(KEY_ARABIC_SUPERSCRIPT_ALEF));
	r.Add(keyToString(KEY_ARABIC_TTEH));
	r.Add(keyToString(KEY_ARABIC_PEH));
	r.Add(keyToString(KEY_ARABIC_TCHEH));
	r.Add(keyToString(KEY_ARABIC_DDAL));
	r.Add(keyToString(KEY_ARABIC_RREH));
	r.Add(keyToString(KEY_ARABIC_COMMA));
	r.Add(keyToString(KEY_ARABIC_FULLSTOP));
	r.Add(keyToString(KEY_ARABIC_0));
	r.Add(keyToString(KEY_ARABIC_1));
	r.Add(keyToString(KEY_ARABIC_2));
	r.Add(keyToString(KEY_ARABIC_3));
	r.Add(keyToString(KEY_ARABIC_4));
	r.Add(keyToString(KEY_ARABIC_5));
	r.Add(keyToString(KEY_ARABIC_6));
	r.Add(keyToString(KEY_ARABIC_7));
	r.Add(keyToString(KEY_ARABIC_8));
	r.Add(keyToString(KEY_ARABIC_9));
	r.Add(keyToString(KEY_ARABIC_SEMICOLON));
	r.Add(keyToString(KEY_ARABIC_QUESTION_MARK));
	r.Add(keyToString(KEY_ARABIC_HAMZA));
	r.Add(keyToString(KEY_ARABIC_MADDAONALEF));
	r.Add(keyToString(KEY_ARABIC_HAMZAONALEF));
	r.Add(keyToString(KEY_ARABIC_HAMZAONWAW));
	r.Add(keyToString(KEY_ARABIC_HAMZAUNDERALEF));
	r.Add(keyToString(KEY_ARABIC_HAMZAONYEH));
	r.Add(keyToString(KEY_ARABIC_ALEF));
	r.Add(keyToString(KEY_ARABIC_BEH));
	r.Add(keyToString(KEY_ARABIC_TEHMARBUTA));
	r.Add(keyToString(KEY_ARABIC_TEH));
	r.Add(keyToString(KEY_ARABIC_THEH));
	r.Add(keyToString(KEY_ARABIC_JEEM));
	r.Add(keyToString(KEY_ARABIC_HAH));
	r.Add(keyToString(KEY_ARABIC_KHAH));
	r.Add(keyToString(KEY_ARABIC_DAL));
	r.Add(keyToString(KEY_ARABIC_THAL));
	r.Add(keyToString(KEY_ARABIC_RA));
	r.Add(keyToString(KEY_ARABIC_ZAIN));
	r.Add(keyToString(KEY_ARABIC_SEEN));
	r.Add(keyToString(KEY_ARABIC_SHEEN));
	r.Add(keyToString(KEY_ARABIC_SAD));
	r.Add(keyToString(KEY_ARABIC_DAD));
	r.Add(keyToString(KEY_ARABIC_TAH));
	r.Add(keyToString(KEY_ARABIC_ZAH));
	r.Add(keyToString(KEY_ARABIC_AIN));
	r.Add(keyToString(KEY_ARABIC_GHAIN));
	r.Add(keyToString(KEY_ARABIC_TATWEEL));
	r.Add(keyToString(KEY_ARABIC_FEH));
	r.Add(keyToString(KEY_ARABIC_QAF));
	r.Add(keyToString(KEY_ARABIC_KAF));
	r.Add(keyToString(KEY_ARABIC_LAM));
	r.Add(keyToString(KEY_ARABIC_MEEM));
	r.Add(keyToString(KEY_ARABIC_NOON));
	r.Add(keyToString(KEY_ARABIC_HA));
	r.Add(keyToString(KEY_ARABIC_WAW));
	r.Add(keyToString(KEY_ARABIC_ALEFMAKSURA));
	r.Add(keyToString(KEY_ARABIC_YEH));
	r.Add(keyToString(KEY_ARABIC_FATHATAN));
	r.Add(keyToString(KEY_ARABIC_DAMMATAN));
	r.Add(keyToString(KEY_ARABIC_KASRATAN));
	r.Add(keyToString(KEY_ARABIC_FATHA));
	r.Add(keyToString(KEY_ARABIC_DAMMA));
	r.Add(keyToString(KEY_ARABIC_KASRA));
	r.Add(keyToString(KEY_ARABIC_SHADDA));
	r.Add(keyToString(KEY_ARABIC_SUKUN));
	r.Add(keyToString(KEY_ARABIC_MADDA_ABOVE));
	r.Add(keyToString(KEY_ARABIC_HAMZA_ABOVE));
	r.Add(keyToString(KEY_ARABIC_HAMZA_BELOW));
	r.Add(keyToString(KEY_ARABIC_JEH));
	r.Add(keyToString(KEY_ARABIC_VEH));
	r.Add(keyToString(KEY_ARABIC_KEHEH));
	r.Add(keyToString(KEY_ARABIC_GAF));
	r.Add(keyToString(KEY_ARABIC_NOON_GHUNNA));
	r.Add(keyToString(KEY_ARABIC_HEH_DOACHASHMEE));
	r.Add(keyToString(KEY_FARSI_YEH));
	r.Add(keyToString(KEY_ARABIC_FARSI_YEH));
	r.Add(keyToString(KEY_ARABIC_YEH_BAREE));
	r.Add(keyToString(KEY_ARABIC_HEH_GOAL));
	r.Add(keyToString(KEY_ARABIC_SWITCH));
	#endif
	#ifdef XK_ARMENIAN
	r.Add(keyToString(KEY_ARMENIAN_LIGATURE_EW));
	r.Add(keyToString(KEY_ARMENIAN_FULL_STOP));
	r.Add(keyToString(KEY_ARMENIAN_VERJAKET));
	r.Add(keyToString(KEY_ARMENIAN_SEPARATION_MARK));
	r.Add(keyToString(KEY_ARMENIAN_BUT));
	r.Add(keyToString(KEY_ARMENIAN_HYPHEN));
	r.Add(keyToString(KEY_ARMENIAN_YENTAMNA));
	r.Add(keyToString(KEY_ARMENIAN_EXCLAM));
	r.Add(keyToString(KEY_ARMENIAN_AMANAK));
	r.Add(keyToString(KEY_ARMENIAN_ACCENT));
	r.Add(keyToString(KEY_ARMENIAN_SHESHT));
	r.Add(keyToString(KEY_ARMENIAN_QUESTION));
	r.Add(keyToString(KEY_ARMENIAN_PARUYK));
	r.Add(keyToString(KEY_ARMENIAN_AYB));
	r.Add(keyToString(KEY_ARMENIAN_BEN));
	r.Add(keyToString(KEY_ARMENIAN_GIM));
	r.Add(keyToString(KEY_ARMENIAN_DA));
	r.Add(keyToString(KEY_ARMENIAN_YECH));
	r.Add(keyToString(KEY_ARMENIAN_ZA));
	r.Add(keyToString(KEY_ARMENIAN_E));
	r.Add(keyToString(KEY_ARMENIAN_AT));
	r.Add(keyToString(KEY_ARMENIAN_TO));
	r.Add(keyToString(KEY_ARMENIAN_ZHE));
	r.Add(keyToString(KEY_ARMENIAN_INI));
	r.Add(keyToString(KEY_ARMENIAN_LYUN));
	r.Add(keyToString(KEY_ARMENIAN_KHE));
	r.Add(keyToString(KEY_ARMENIAN_TSA));
	r.Add(keyToString(KEY_ARMENIAN_KEN));
	r.Add(keyToString(KEY_ARMENIAN_HO));
	r.Add(keyToString(KEY_ARMENIAN_DZA));
	r.Add(keyToString(KEY_ARMENIAN_GHAT));
	r.Add(keyToString(KEY_ARMENIAN_TCHE));
	r.Add(keyToString(KEY_ARMENIAN_MEN));
	r.Add(keyToString(KEY_ARMENIAN_HI));
	r.Add(keyToString(KEY_ARMENIAN_NU));
	r.Add(keyToString(KEY_ARMENIAN_SHA));
	r.Add(keyToString(KEY_ARMENIAN_VO));
	r.Add(keyToString(KEY_ARMENIAN_CHA));
	r.Add(keyToString(KEY_ARMENIAN_PE));
	r.Add(keyToString(KEY_ARMENIAN_JE));
	r.Add(keyToString(KEY_ARMENIAN_RA));
	r.Add(keyToString(KEY_ARMENIAN_SE));
	r.Add(keyToString(KEY_ARMENIAN_VEV));
	r.Add(keyToString(KEY_ARMENIAN_TYUN));
	r.Add(keyToString(KEY_ARMENIAN_RE));
	r.Add(keyToString(KEY_ARMENIAN_TSO));
	r.Add(keyToString(KEY_ARMENIAN_VYUN));
	r.Add(keyToString(KEY_ARMENIAN_PYUR));
	r.Add(keyToString(KEY_ARMENIAN_KE));
	r.Add(keyToString(KEY_ARMENIAN_O));
	r.Add(keyToString(KEY_ARMENIAN_FE));
	r.Add(keyToString(KEY_ARMENIAN_APOSTROPHE));
	#endif
	#ifdef XK_BRAILLE
	r.Add(keyToString(KEY_BRAILLE_DOT_1));
	r.Add(keyToString(KEY_BRAILLE_DOT_2));
	r.Add(keyToString(KEY_BRAILLE_DOT_3));
	r.Add(keyToString(KEY_BRAILLE_DOT_4));
	r.Add(keyToString(KEY_BRAILLE_DOT_5));
	r.Add(keyToString(KEY_BRAILLE_DOT_6));
	r.Add(keyToString(KEY_BRAILLE_DOT_7));
	r.Add(keyToString(KEY_BRAILLE_DOT_8));
	r.Add(keyToString(KEY_BRAILLE_DOT_9));
	r.Add(keyToString(KEY_BRAILLE_DOT_10));
	r.Add(keyToString(KEY_BRAILLE_BLANK));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123));
	r.Add(keyToString(KEY_BRAILLE_DOTS_4));
	r.Add(keyToString(KEY_BRAILLE_DOTS_14));
	r.Add(keyToString(KEY_BRAILLE_DOTS_24));
	r.Add(keyToString(KEY_BRAILLE_DOTS_124));
	r.Add(keyToString(KEY_BRAILLE_DOTS_34));
	r.Add(keyToString(KEY_BRAILLE_DOTS_134));
	r.Add(keyToString(KEY_BRAILLE_DOTS_234));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1234));
	r.Add(keyToString(KEY_BRAILLE_DOTS_5));
	r.Add(keyToString(KEY_BRAILLE_DOTS_15));
	r.Add(keyToString(KEY_BRAILLE_DOTS_25));
	r.Add(keyToString(KEY_BRAILLE_DOTS_125));
	r.Add(keyToString(KEY_BRAILLE_DOTS_35));
	r.Add(keyToString(KEY_BRAILLE_DOTS_135));
	r.Add(keyToString(KEY_BRAILLE_DOTS_235));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1235));
	r.Add(keyToString(KEY_BRAILLE_DOTS_45));
	r.Add(keyToString(KEY_BRAILLE_DOTS_145));
	r.Add(keyToString(KEY_BRAILLE_DOTS_245));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1245));
	r.Add(keyToString(KEY_BRAILLE_DOTS_345));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1345));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2345));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12345));
	r.Add(keyToString(KEY_BRAILLE_DOTS_6));
	r.Add(keyToString(KEY_BRAILLE_DOTS_16));
	r.Add(keyToString(KEY_BRAILLE_DOTS_26));
	r.Add(keyToString(KEY_BRAILLE_DOTS_126));
	r.Add(keyToString(KEY_BRAILLE_DOTS_36));
	r.Add(keyToString(KEY_BRAILLE_DOTS_136));
	r.Add(keyToString(KEY_BRAILLE_DOTS_236));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1236));
	r.Add(keyToString(KEY_BRAILLE_DOTS_46));
	r.Add(keyToString(KEY_BRAILLE_DOTS_146));
	r.Add(keyToString(KEY_BRAILLE_DOTS_246));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1246));
	r.Add(keyToString(KEY_BRAILLE_DOTS_346));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1346));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2346));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12346));
	r.Add(keyToString(KEY_BRAILLE_DOTS_56));
	r.Add(keyToString(KEY_BRAILLE_DOTS_156));
	r.Add(keyToString(KEY_BRAILLE_DOTS_256));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1256));
	r.Add(keyToString(KEY_BRAILLE_DOTS_356));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1356));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2356));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12356));
	r.Add(keyToString(KEY_BRAILLE_DOTS_456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123456));
	r.Add(keyToString(KEY_BRAILLE_DOTS_7));
	r.Add(keyToString(KEY_BRAILLE_DOTS_17));
	r.Add(keyToString(KEY_BRAILLE_DOTS_27));
	r.Add(keyToString(KEY_BRAILLE_DOTS_127));
	r.Add(keyToString(KEY_BRAILLE_DOTS_37));
	r.Add(keyToString(KEY_BRAILLE_DOTS_137));
	r.Add(keyToString(KEY_BRAILLE_DOTS_237));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1237));
	r.Add(keyToString(KEY_BRAILLE_DOTS_47));
	r.Add(keyToString(KEY_BRAILLE_DOTS_147));
	r.Add(keyToString(KEY_BRAILLE_DOTS_247));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1247));
	r.Add(keyToString(KEY_BRAILLE_DOTS_347));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1347));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2347));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12347));
	r.Add(keyToString(KEY_BRAILLE_DOTS_57));
	r.Add(keyToString(KEY_BRAILLE_DOTS_157));
	r.Add(keyToString(KEY_BRAILLE_DOTS_257));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1257));
	r.Add(keyToString(KEY_BRAILLE_DOTS_357));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1357));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2357));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12357));
	r.Add(keyToString(KEY_BRAILLE_DOTS_457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123457));
	r.Add(keyToString(KEY_BRAILLE_DOTS_67));
	r.Add(keyToString(KEY_BRAILLE_DOTS_167));
	r.Add(keyToString(KEY_BRAILLE_DOTS_267));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1267));
	r.Add(keyToString(KEY_BRAILLE_DOTS_367));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1367));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2367));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12367));
	r.Add(keyToString(KEY_BRAILLE_DOTS_467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123467));
	r.Add(keyToString(KEY_BRAILLE_DOTS_567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_4567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_14567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_24567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_124567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_34567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_134567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_234567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1234567));
	r.Add(keyToString(KEY_BRAILLE_DOTS_8));
	r.Add(keyToString(KEY_BRAILLE_DOTS_18));
	r.Add(keyToString(KEY_BRAILLE_DOTS_28));
	r.Add(keyToString(KEY_BRAILLE_DOTS_128));
	r.Add(keyToString(KEY_BRAILLE_DOTS_38));
	r.Add(keyToString(KEY_BRAILLE_DOTS_138));
	r.Add(keyToString(KEY_BRAILLE_DOTS_238));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1238));
	r.Add(keyToString(KEY_BRAILLE_DOTS_48));
	r.Add(keyToString(KEY_BRAILLE_DOTS_148));
	r.Add(keyToString(KEY_BRAILLE_DOTS_248));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1248));
	r.Add(keyToString(KEY_BRAILLE_DOTS_348));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1348));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2348));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12348));
	r.Add(keyToString(KEY_BRAILLE_DOTS_58));
	r.Add(keyToString(KEY_BRAILLE_DOTS_158));
	r.Add(keyToString(KEY_BRAILLE_DOTS_258));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1258));
	r.Add(keyToString(KEY_BRAILLE_DOTS_358));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1358));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2358));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12358));
	r.Add(keyToString(KEY_BRAILLE_DOTS_458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123458));
	r.Add(keyToString(KEY_BRAILLE_DOTS_68));
	r.Add(keyToString(KEY_BRAILLE_DOTS_168));
	r.Add(keyToString(KEY_BRAILLE_DOTS_268));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1268));
	r.Add(keyToString(KEY_BRAILLE_DOTS_368));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1368));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2368));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12368));
	r.Add(keyToString(KEY_BRAILLE_DOTS_468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123468));
	r.Add(keyToString(KEY_BRAILLE_DOTS_568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_4568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_14568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_24568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_124568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_34568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_134568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_234568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1234568));
	r.Add(keyToString(KEY_BRAILLE_DOTS_78));
	r.Add(keyToString(KEY_BRAILLE_DOTS_178));
	r.Add(keyToString(KEY_BRAILLE_DOTS_278));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1278));
	r.Add(keyToString(KEY_BRAILLE_DOTS_378));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1378));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2378));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12378));
	r.Add(keyToString(KEY_BRAILLE_DOTS_478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123478));
	r.Add(keyToString(KEY_BRAILLE_DOTS_578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_4578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_14578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_24578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_124578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_34578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_134578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_234578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1234578));
	r.Add(keyToString(KEY_BRAILLE_DOTS_678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_3678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_13678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_23678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_123678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_4678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_14678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_24678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_124678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_34678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_134678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_234678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1234678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_5678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_15678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_25678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_125678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_35678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_135678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_235678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1235678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_45678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_145678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_245678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1245678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_345678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_1345678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_2345678));
	r.Add(keyToString(KEY_BRAILLE_DOTS_12345678));
	#endif
	#ifdef XK_CAUCASUS
	r.Add(keyToString(KEY_XABOVEDOT));
	r.Add(keyToString(KEY_IBREVE));
	r.Add(keyToString(KEY_ZSTROKE));
	r.Add(keyToString(KEY_GCARON));
	r.Add(keyToString(KEY_OCARON));
	r.Add(keyToString(KEY_OBARRED));
	r.Add(keyToString(KEY_SCHWA));
	r.Add(keyToString(KEY_EZH));
	r.Add(keyToString(KEY_LBELOWDOT));
	#endif
	#ifdef XK_CURRENCY
	r.Add(keyToString(KEY_ECUSIGN));
	r.Add(keyToString(KEY_COLONSIGN));
	r.Add(keyToString(KEY_CRUZEIROSIGN));
	r.Add(keyToString(KEY_FFRANCSIGN));
	r.Add(keyToString(KEY_LIRASIGN));
	r.Add(keyToString(KEY_MILLSIGN));
	r.Add(keyToString(KEY_NAIRASIGN));
	r.Add(keyToString(KEY_PESETASIGN));
	r.Add(keyToString(KEY_RUPEESIGN));
	r.Add(keyToString(KEY_WONSIGN));
	r.Add(keyToString(KEY_NEWSHEQELSIGN));
	r.Add(keyToString(KEY_DONGSIGN));
	r.Add(keyToString(KEY_EUROSIGN));
	#endif
	#ifdef XK_CYRILLIC
	r.Add(keyToString(KEY_CYRILLIC_GHE_BAR));
	r.Add(keyToString(KEY_CYRILLIC_ZHE_DESCENDER));
	r.Add(keyToString(KEY_CYRILLIC_KA_DESCENDER));
	r.Add(keyToString(KEY_CYRILLIC_KA_VERTSTROKE));
	r.Add(keyToString(KEY_CYRILLIC_EN_DESCENDER));
	r.Add(keyToString(KEY_CYRILLIC_U_STRAIGHT));
	r.Add(keyToString(KEY_CYRILLIC_U_STRAIGHT_BAR));
	r.Add(keyToString(KEY_CYRILLIC_HA_DESCENDER));
	r.Add(keyToString(KEY_CYRILLIC_CHE_DESCENDER));
	r.Add(keyToString(KEY_CYRILLIC_CHE_VERTSTROKE));
	r.Add(keyToString(KEY_CYRILLIC_SHHA));
	r.Add(keyToString(KEY_CYRILLIC_SCHWA));
	r.Add(keyToString(KEY_CYRILLIC_I_MACRON));
	r.Add(keyToString(KEY_CYRILLIC_O_BAR));
	r.Add(keyToString(KEY_CYRILLIC_U_MACRON));
	r.Add(keyToString(KEY_SERBIAN_DJE));
	r.Add(keyToString(KEY_MACEDONIA_GJE));
	r.Add(keyToString(KEY_CYRILLIC_IO));
	r.Add(keyToString(KEY_UKRAINIAN_IE));
	r.Add(keyToString(KEY_MACEDONIA_DSE));
	r.Add(keyToString(KEY_UKRAINIAN_I));
	r.Add(keyToString(KEY_UKRAINIAN_YI));
	r.Add(keyToString(KEY_CYRILLIC_JE));
	r.Add(keyToString(KEY_CYRILLIC_LJE));
	r.Add(keyToString(KEY_CYRILLIC_NJE));
	r.Add(keyToString(KEY_SERBIAN_TSHE));
	r.Add(keyToString(KEY_MACEDONIA_KJE));
	r.Add(keyToString(KEY_UKRAINIAN_GHE_WITH_UPTURN));
	r.Add(keyToString(KEY_BYELORUSSIAN_SHORTU));
	r.Add(keyToString(KEY_CYRILLIC_DZHE));
	r.Add(keyToString(KEY_NUMEROSIGN));
	r.Add(keyToString(KEY_CYRILLIC_YU));
	r.Add(keyToString(KEY_CYRILLIC_A));
	r.Add(keyToString(KEY_CYRILLIC_BE));
	r.Add(keyToString(KEY_CYRILLIC_TSE));
	r.Add(keyToString(KEY_CYRILLIC_DE));
	r.Add(keyToString(KEY_CYRILLIC_IE));
	r.Add(keyToString(KEY_CYRILLIC_EF));
	r.Add(keyToString(KEY_CYRILLIC_GHE));
	r.Add(keyToString(KEY_CYRILLIC_HA));
	r.Add(keyToString(KEY_CYRILLIC_I));
	r.Add(keyToString(KEY_CYRILLIC_SHORTI));
	r.Add(keyToString(KEY_CYRILLIC_KA));
	r.Add(keyToString(KEY_CYRILLIC_EL));
	r.Add(keyToString(KEY_CYRILLIC_EM));
	r.Add(keyToString(KEY_CYRILLIC_EN));
	r.Add(keyToString(KEY_CYRILLIC_O));
	r.Add(keyToString(KEY_CYRILLIC_PE));
	r.Add(keyToString(KEY_CYRILLIC_YA));
	r.Add(keyToString(KEY_CYRILLIC_ER));
	r.Add(keyToString(KEY_CYRILLIC_ES));
	r.Add(keyToString(KEY_CYRILLIC_TE));
	r.Add(keyToString(KEY_CYRILLIC_U));
	r.Add(keyToString(KEY_CYRILLIC_ZHE));
	r.Add(keyToString(KEY_CYRILLIC_VE));
	r.Add(keyToString(KEY_CYRILLIC_SOFTSIGN));
	r.Add(keyToString(KEY_CYRILLIC_YERU));
	r.Add(keyToString(KEY_CYRILLIC_ZE));
	r.Add(keyToString(KEY_CYRILLIC_SHA));
	r.Add(keyToString(KEY_CYRILLIC_E));
	r.Add(keyToString(KEY_CYRILLIC_SHCHA));
	r.Add(keyToString(KEY_CYRILLIC_CHE));
	r.Add(keyToString(KEY_CYRILLIC_HARDSIGN));
	#endif
	#ifdef XK_GEORGIAN
	r.Add(keyToString(KEY_GEORGIAN_AN));
	r.Add(keyToString(KEY_GEORGIAN_BAN));
	r.Add(keyToString(KEY_GEORGIAN_GAN));
	r.Add(keyToString(KEY_GEORGIAN_DON));
	r.Add(keyToString(KEY_GEORGIAN_EN));
	r.Add(keyToString(KEY_GEORGIAN_VIN));
	r.Add(keyToString(KEY_GEORGIAN_ZEN));
	r.Add(keyToString(KEY_GEORGIAN_TAN));
	r.Add(keyToString(KEY_GEORGIAN_IN));
	r.Add(keyToString(KEY_GEORGIAN_KAN));
	r.Add(keyToString(KEY_GEORGIAN_LAS));
	r.Add(keyToString(KEY_GEORGIAN_MAN));
	r.Add(keyToString(KEY_GEORGIAN_NAR));
	r.Add(keyToString(KEY_GEORGIAN_ON));
	r.Add(keyToString(KEY_GEORGIAN_PAR));
	r.Add(keyToString(KEY_GEORGIAN_ZHAR));
	r.Add(keyToString(KEY_GEORGIAN_RAE));
	r.Add(keyToString(KEY_GEORGIAN_SAN));
	r.Add(keyToString(KEY_GEORGIAN_TAR));
	r.Add(keyToString(KEY_GEORGIAN_UN));
	r.Add(keyToString(KEY_GEORGIAN_PHAR));
	r.Add(keyToString(KEY_GEORGIAN_KHAR));
	r.Add(keyToString(KEY_GEORGIAN_GHAN));
	r.Add(keyToString(KEY_GEORGIAN_QAR));
	r.Add(keyToString(KEY_GEORGIAN_SHIN));
	r.Add(keyToString(KEY_GEORGIAN_CHIN));
	r.Add(keyToString(KEY_GEORGIAN_CAN));
	r.Add(keyToString(KEY_GEORGIAN_JIL));
	r.Add(keyToString(KEY_GEORGIAN_CIL));
	r.Add(keyToString(KEY_GEORGIAN_CHAR));
	r.Add(keyToString(KEY_GEORGIAN_XAN));
	r.Add(keyToString(KEY_GEORGIAN_JHAN));
	r.Add(keyToString(KEY_GEORGIAN_HAE));
	r.Add(keyToString(KEY_GEORGIAN_HE));
	r.Add(keyToString(KEY_GEORGIAN_HIE));
	r.Add(keyToString(KEY_GEORGIAN_WE));
	r.Add(keyToString(KEY_GEORGIAN_HAR));
	r.Add(keyToString(KEY_GEORGIAN_HOE));
	r.Add(keyToString(KEY_GEORGIAN_FI));
	#endif
	#ifdef XK_GREEK
	r.Add(keyToString(KEY_GREEK_ALPHAACCENT));
	r.Add(keyToString(KEY_GREEK_EPSILONACCENT));
	r.Add(keyToString(KEY_GREEK_ETAACCENT));
	r.Add(keyToString(KEY_GREEK_IOTAACCENT));
	r.Add(keyToString(KEY_GREEK_IOTADIERESIS));
	r.Add(keyToString(KEY_GREEK_IOTADIAERESIS));
	r.Add(keyToString(KEY_GREEK_OMICRONACCENT));
	r.Add(keyToString(KEY_GREEK_UPSILONACCENT));
	r.Add(keyToString(KEY_GREEK_UPSILONDIERESIS));
	r.Add(keyToString(KEY_GREEK_OMEGAACCENT));
	r.Add(keyToString(KEY_GREEK_ACCENTDIERESIS));
	r.Add(keyToString(KEY_GREEK_HORIZBAR));
	r.Add(keyToString(KEY_GREEK_IOTAACCENTDIERESIS));
	r.Add(keyToString(KEY_GREEK_UPSILONACCENTDIERESIS));
	r.Add(keyToString(KEY_GREEK_ALPHA));
	r.Add(keyToString(KEY_GREEK_BETA));
	r.Add(keyToString(KEY_GREEK_GAMMA));
	r.Add(keyToString(KEY_GREEK_DELTA));
	r.Add(keyToString(KEY_GREEK_EPSILON));
	r.Add(keyToString(KEY_GREEK_ZETA));
	r.Add(keyToString(KEY_GREEK_ETA));
	r.Add(keyToString(KEY_GREEK_THETA));
	r.Add(keyToString(KEY_GREEK_IOTA));
	r.Add(keyToString(KEY_GREEK_KAPPA));
	r.Add(keyToString(KEY_GREEK_LAMDA));
	r.Add(keyToString(KEY_GREEK_LAMBDA));
	r.Add(keyToString(KEY_GREEK_MU));
	r.Add(keyToString(KEY_GREEK_NU));
	r.Add(keyToString(KEY_GREEK_XI));
	r.Add(keyToString(KEY_GREEK_OMICRON));
	r.Add(keyToString(KEY_GREEK_PI));
	r.Add(keyToString(KEY_GREEK_RHO));
	r.Add(keyToString(KEY_GREEK_SIGMA));
	r.Add(keyToString(KEY_GREEK_TAU));
	r.Add(keyToString(KEY_GREEK_UPSILON));
	r.Add(keyToString(KEY_GREEK_PHI));
	r.Add(keyToString(KEY_GREEK_CHI));
	r.Add(keyToString(KEY_GREEK_PSI));
	r.Add(keyToString(KEY_GREEK_OMEGA));
	r.Add(keyToString(KEY_GREEK_FINALSMALLSIGMA));
	r.Add(keyToString(KEY_GREEK_SWITCH));
	#endif
	#ifdef XK_HEBREW
	r.Add(keyToString(KEY_HEBREW_DOUBLELOWLINE));
	r.Add(keyToString(KEY_HEBREW_ALEPH));
	r.Add(keyToString(KEY_HEBREW_BET));
	r.Add(keyToString(KEY_HEBREW_GIMEL));
	r.Add(keyToString(KEY_HEBREW_DALET));
	r.Add(keyToString(KEY_HEBREW_HE));
	r.Add(keyToString(KEY_HEBREW_WAW));
	r.Add(keyToString(KEY_HEBREW_ZAIN));
	r.Add(keyToString(KEY_HEBREW_CHET));
	r.Add(keyToString(KEY_HEBREW_TET));
	r.Add(keyToString(KEY_HEBREW_YOD));
	r.Add(keyToString(KEY_HEBREW_FINALKAPH));
	r.Add(keyToString(KEY_HEBREW_KAPH));
	r.Add(keyToString(KEY_HEBREW_LAMED));
	r.Add(keyToString(KEY_HEBREW_FINALMEM));
	r.Add(keyToString(KEY_HEBREW_MEM));
	r.Add(keyToString(KEY_HEBREW_FINALNUN));
	r.Add(keyToString(KEY_HEBREW_NUN));
	r.Add(keyToString(KEY_HEBREW_SAMECH));
	r.Add(keyToString(KEY_HEBREW_AYIN));
	r.Add(keyToString(KEY_HEBREW_FINALPE));
	r.Add(keyToString(KEY_HEBREW_PE));
	r.Add(keyToString(KEY_HEBREW_FINALZADE));
	r.Add(keyToString(KEY_HEBREW_ZADE));
	r.Add(keyToString(KEY_HEBREW_QOPH));
	r.Add(keyToString(KEY_HEBREW_RESH));
	r.Add(keyToString(KEY_HEBREW_SHIN));
	r.Add(keyToString(KEY_HEBREW_TAW));
	r.Add(keyToString(KEY_HEBREW_SWITCH));
	#endif
	#ifdef XK_KATAKANA
	r.Add(keyToString(KEY_OVERLINE));
	r.Add(keyToString(KEY_KANA_FULLSTOP));
	r.Add(keyToString(KEY_KANA_OPENINGBRACKET));
	r.Add(keyToString(KEY_KANA_CLOSINGBRACKET));
	r.Add(keyToString(KEY_KANA_COMMA));
	r.Add(keyToString(KEY_KANA_CONJUNCTIVE));
	r.Add(keyToString(KEY_KANA_WO));
	r.Add(keyToString(KEY_KANA_A));
	r.Add(keyToString(KEY_KANA_I));
	r.Add(keyToString(KEY_KANA_U));
	r.Add(keyToString(KEY_KANA_E));
	r.Add(keyToString(KEY_KANA_O));
	r.Add(keyToString(KEY_KANA_YA));
	r.Add(keyToString(KEY_KANA_YU));
	r.Add(keyToString(KEY_KANA_YO));
	r.Add(keyToString(KEY_KANA_TSU));
	r.Add(keyToString(KEY_PROLONGEDSOUND));
	r.Add(keyToString(KEY_KANA_KA));
	r.Add(keyToString(KEY_KANA_KI));
	r.Add(keyToString(KEY_KANA_KU));
	r.Add(keyToString(KEY_KANA_KE));
	r.Add(keyToString(KEY_KANA_KO));
	r.Add(keyToString(KEY_KANA_SA));
	r.Add(keyToString(KEY_KANA_SHI));
	r.Add(keyToString(KEY_KANA_SU));
	r.Add(keyToString(KEY_KANA_SE));
	r.Add(keyToString(KEY_KANA_SO));
	r.Add(keyToString(KEY_KANA_TA));
	r.Add(keyToString(KEY_KANA_CHI));
	r.Add(keyToString(KEY_KANA_TE));
	r.Add(keyToString(KEY_KANA_TO));
	r.Add(keyToString(KEY_KANA_NA));
	r.Add(keyToString(KEY_KANA_NI));
	r.Add(keyToString(KEY_KANA_NU));
	r.Add(keyToString(KEY_KANA_NE));
	r.Add(keyToString(KEY_KANA_NO));
	r.Add(keyToString(KEY_KANA_HA));
	r.Add(keyToString(KEY_KANA_HI));
	r.Add(keyToString(KEY_KANA_FU));
	r.Add(keyToString(KEY_KANA_HE));
	r.Add(keyToString(KEY_KANA_HO));
	r.Add(keyToString(KEY_KANA_MA));
	r.Add(keyToString(KEY_KANA_MI));
	r.Add(keyToString(KEY_KANA_MU));
	r.Add(keyToString(KEY_KANA_ME));
	r.Add(keyToString(KEY_KANA_MO));
	r.Add(keyToString(KEY_KANA_RA));
	r.Add(keyToString(KEY_KANA_RI));
	r.Add(keyToString(KEY_KANA_RU));
	r.Add(keyToString(KEY_KANA_RE));
	r.Add(keyToString(KEY_KANA_RO));
	r.Add(keyToString(KEY_KANA_WA));
	r.Add(keyToString(KEY_KANA_N));
	r.Add(keyToString(KEY_VOICEDSOUND));
	r.Add(keyToString(KEY_SEMIVOICEDSOUND));
	r.Add(keyToString(KEY_KANA_SWITCH));
	#endif
	#ifdef XK_KOREAN
	r.Add(keyToString(KEY_HANGUL));
	r.Add(keyToString(KEY_HANGUL_START));
	r.Add(keyToString(KEY_HANGUL_END));
	r.Add(keyToString(KEY_HANGUL_HANJA));
	r.Add(keyToString(KEY_HANGUL_JAMO));
	r.Add(keyToString(KEY_HANGUL_ROMAJA));
	r.Add(keyToString(KEY_HANGUL_CODEINPUT));
	r.Add(keyToString(KEY_HANGUL_JEONJA));
	r.Add(keyToString(KEY_HANGUL_BANJA));
	r.Add(keyToString(KEY_HANGUL_PREHANJA));
	r.Add(keyToString(KEY_HANGUL_POSTHANJA));
	r.Add(keyToString(KEY_HANGUL_SINGLECANDIDATE));
	r.Add(keyToString(KEY_HANGUL_MULTIPLECANDIDATE));
	r.Add(keyToString(KEY_HANGUL_PREVIOUSCANDIDATE));
	r.Add(keyToString(KEY_HANGUL_SPECIAL));
	r.Add(keyToString(KEY_HANGUL_SWITCH));
	r.Add(keyToString(KEY_HANGUL_KIYEOG));
	r.Add(keyToString(KEY_HANGUL_SSANGKIYEOG));
	r.Add(keyToString(KEY_HANGUL_KIYEOGSIOS));
	r.Add(keyToString(KEY_HANGUL_NIEUN));
	r.Add(keyToString(KEY_HANGUL_NIEUNJIEUJ));
	r.Add(keyToString(KEY_HANGUL_NIEUNHIEUH));
	r.Add(keyToString(KEY_HANGUL_DIKEUD));
	r.Add(keyToString(KEY_HANGUL_SSANGDIKEUD));
	r.Add(keyToString(KEY_HANGUL_RIEUL));
	r.Add(keyToString(KEY_HANGUL_RIEULKIYEOG));
	r.Add(keyToString(KEY_HANGUL_RIEULMIEUM));
	r.Add(keyToString(KEY_HANGUL_RIEULPIEUB));
	r.Add(keyToString(KEY_HANGUL_RIEULSIOS));
	r.Add(keyToString(KEY_HANGUL_RIEULTIEUT));
	r.Add(keyToString(KEY_HANGUL_RIEULPHIEUF));
	r.Add(keyToString(KEY_HANGUL_RIEULHIEUH));
	r.Add(keyToString(KEY_HANGUL_MIEUM));
	r.Add(keyToString(KEY_HANGUL_PIEUB));
	r.Add(keyToString(KEY_HANGUL_SSANGPIEUB));
	r.Add(keyToString(KEY_HANGUL_PIEUBSIOS));
	r.Add(keyToString(KEY_HANGUL_SIOS));
	r.Add(keyToString(KEY_HANGUL_SSANGSIOS));
	r.Add(keyToString(KEY_HANGUL_IEUNG));
	r.Add(keyToString(KEY_HANGUL_JIEUJ));
	r.Add(keyToString(KEY_HANGUL_SSANGJIEUJ));
	r.Add(keyToString(KEY_HANGUL_CIEUC));
	r.Add(keyToString(KEY_HANGUL_KHIEUQ));
	r.Add(keyToString(KEY_HANGUL_TIEUT));
	r.Add(keyToString(KEY_HANGUL_PHIEUF));
	r.Add(keyToString(KEY_HANGUL_HIEUH));
	r.Add(keyToString(KEY_HANGUL_A));
	r.Add(keyToString(KEY_HANGUL_AE));
	r.Add(keyToString(KEY_HANGUL_YA));
	r.Add(keyToString(KEY_HANGUL_YAE));
	r.Add(keyToString(KEY_HANGUL_EO));
	r.Add(keyToString(KEY_HANGUL_E));
	r.Add(keyToString(KEY_HANGUL_YEO));
	r.Add(keyToString(KEY_HANGUL_YE));
	r.Add(keyToString(KEY_HANGUL_O));
	r.Add(keyToString(KEY_HANGUL_WA));
	r.Add(keyToString(KEY_HANGUL_WAE));
	r.Add(keyToString(KEY_HANGUL_OE));
	r.Add(keyToString(KEY_HANGUL_YO));
	r.Add(keyToString(KEY_HANGUL_U));
	r.Add(keyToString(KEY_HANGUL_WEO));
	r.Add(keyToString(KEY_HANGUL_WE));
	r.Add(keyToString(KEY_HANGUL_WI));
	r.Add(keyToString(KEY_HANGUL_YU));
	r.Add(keyToString(KEY_HANGUL_EU));
	r.Add(keyToString(KEY_HANGUL_YI));
	r.Add(keyToString(KEY_HANGUL_I));
	r.Add(keyToString(KEY_HANGUL_J_KIYEOG));
	r.Add(keyToString(KEY_HANGUL_J_SSANGKIYEOG));
	r.Add(keyToString(KEY_HANGUL_J_KIYEOGSIOS));
	r.Add(keyToString(KEY_HANGUL_J_NIEUN));
	r.Add(keyToString(KEY_HANGUL_J_NIEUNJIEUJ));
	r.Add(keyToString(KEY_HANGUL_J_NIEUNHIEUH));
	r.Add(keyToString(KEY_HANGUL_J_DIKEUD));
	r.Add(keyToString(KEY_HANGUL_J_RIEUL));
	r.Add(keyToString(KEY_HANGUL_J_RIEULKIYEOG));
	r.Add(keyToString(KEY_HANGUL_J_RIEULMIEUM));
	r.Add(keyToString(KEY_HANGUL_J_RIEULPIEUB));
	r.Add(keyToString(KEY_HANGUL_J_RIEULSIOS));
	r.Add(keyToString(KEY_HANGUL_J_RIEULTIEUT));
	r.Add(keyToString(KEY_HANGUL_J_RIEULPHIEUF));
	r.Add(keyToString(KEY_HANGUL_J_RIEULHIEUH));
	r.Add(keyToString(KEY_HANGUL_J_MIEUM));
	r.Add(keyToString(KEY_HANGUL_J_PIEUB));
	r.Add(keyToString(KEY_HANGUL_J_PIEUBSIOS));
	r.Add(keyToString(KEY_HANGUL_J_SIOS));
	r.Add(keyToString(KEY_HANGUL_J_SSANGSIOS));
	r.Add(keyToString(KEY_HANGUL_J_IEUNG));
	r.Add(keyToString(KEY_HANGUL_J_JIEUJ));
	r.Add(keyToString(KEY_HANGUL_J_CIEUC));
	r.Add(keyToString(KEY_HANGUL_J_KHIEUQ));
	r.Add(keyToString(KEY_HANGUL_J_TIEUT));
	r.Add(keyToString(KEY_HANGUL_J_PHIEUF));
	r.Add(keyToString(KEY_HANGUL_J_HIEUH));
	r.Add(keyToString(KEY_HANGUL_RIEULYEORINHIEUH));
	r.Add(keyToString(KEY_HANGUL_SUNKYEONGEUMMIEUM));
	r.Add(keyToString(KEY_HANGUL_SUNKYEONGEUMPIEUB));
	r.Add(keyToString(KEY_HANGUL_PANSIOS));
	r.Add(keyToString(KEY_HANGUL_KKOGJIDALRINIEUNG));
	r.Add(keyToString(KEY_HANGUL_SUNKYEONGEUMPHIEUF));
	r.Add(keyToString(KEY_HANGUL_YEORINHIEUH));
	r.Add(keyToString(KEY_HANGUL_ARAEA));
	r.Add(keyToString(KEY_HANGUL_ARAEAE));
	r.Add(keyToString(KEY_HANGUL_J_PANSIOS));
	r.Add(keyToString(KEY_HANGUL_J_KKOGJIDALRINIEUNG));
	r.Add(keyToString(KEY_HANGUL_J_YEORINHIEUH));
	r.Add(keyToString(KEY_KOREAN_WON));
	#endif
	#ifdef XK_LATIN1
	r.Add(keyToString(KEY_SPACE));
	r.Add(keyToString(KEY_EXCLAM));
	r.Add(keyToString(KEY_QUOTEDBL));
	r.Add(keyToString(KEY_NUMBERSIGN));
	r.Add(keyToString(KEY_DOLLAR));
	r.Add(keyToString(KEY_PERCENT));
	r.Add(keyToString(KEY_AMPERSAND));
	r.Add(keyToString(KEY_APOSTROPHE));
	r.Add(keyToString(KEY_PARENLEFT));
	r.Add(keyToString(KEY_PARENRIGHT));
	r.Add(keyToString(KEY_ASTERISK));
	r.Add(keyToString(KEY_PLUS));
	r.Add(keyToString(KEY_COMMA));
	r.Add(keyToString(KEY_MINUS));
	r.Add(keyToString(KEY_PERIOD));
	r.Add(keyToString(KEY_SLASH));
	r.Add(keyToString(KEY_COLON));
	r.Add(keyToString(KEY_SEMICOLON));
	r.Add(keyToString(KEY_LESS));
	r.Add(keyToString(KEY_EQUAL));
	r.Add(keyToString(KEY_GREATER));
	r.Add(keyToString(KEY_QUESTION));
	r.Add(keyToString(KEY_AT));
	r.Add(keyToString(KEY_BRACKETLEFT));
	r.Add(keyToString(KEY_BACKSLASH));
	r.Add(keyToString(KEY_BRACKETRIGHT));
	r.Add(keyToString(KEY_ASCIICIRCUM));
	r.Add(keyToString(KEY_UNDERSCORE));
	r.Add(keyToString(KEY_GRAVE));
	r.Add(keyToString(KEY_BRACELEFT));
	r.Add(keyToString(KEY_BAR));
	r.Add(keyToString(KEY_BRACERIGHT));
	r.Add(keyToString(KEY_ASCIITILDE));
	r.Add(keyToString(KEY_NOBREAKSPACE));
	r.Add(keyToString(KEY_EXCLAMDOWN));
	r.Add(keyToString(KEY_CENT));
	r.Add(keyToString(KEY_STERLING));
	r.Add(keyToString(KEY_CURRENCY));
	r.Add(keyToString(KEY_YEN));
	r.Add(keyToString(KEY_BROKENBAR));
	r.Add(keyToString(KEY_SECTION));
	r.Add(keyToString(KEY_DIAERESIS));
	r.Add(keyToString(KEY_COPYRIGHT));
	r.Add(keyToString(KEY_ORDFEMININE));
	r.Add(keyToString(KEY_GUILLEMOTLEFT));
	r.Add(keyToString(KEY_NOTSIGN));
	r.Add(keyToString(KEY_HYPHEN));
	r.Add(keyToString(KEY_REGISTERED));
	r.Add(keyToString(KEY_MACRON));
	r.Add(keyToString(KEY_DEGREE));
	r.Add(keyToString(KEY_PLUSMINUS));
	r.Add(keyToString(KEY_TWOSUPERIOR));
	r.Add(keyToString(KEY_THREESUPERIOR));
	r.Add(keyToString(KEY_ACUTE));
	r.Add(keyToString(KEY_MU));
	r.Add(keyToString(KEY_PARAGRAPH));
	r.Add(keyToString(KEY_PERIODCENTERED));
	r.Add(keyToString(KEY_CEDILLA));
	r.Add(keyToString(KEY_ONESUPERIOR));
	r.Add(keyToString(KEY_MASCULINE));
	r.Add(keyToString(KEY_GUILLEMOTRIGHT));
	r.Add(keyToString(KEY_ONEQUARTER));
	r.Add(keyToString(KEY_ONEHALF));
	r.Add(keyToString(KEY_THREEQUARTERS));
	r.Add(keyToString(KEY_QUESTIONDOWN));
	r.Add(keyToString(KEY_AGRAVE));
	r.Add(keyToString(KEY_AACUTE));
	r.Add(keyToString(KEY_ACIRCUMFLEX));
	r.Add(keyToString(KEY_ATILDE));
	r.Add(keyToString(KEY_ADIAERESIS));
	r.Add(keyToString(KEY_ARING));
	r.Add(keyToString(KEY_AE));
	r.Add(keyToString(KEY_CCEDILLA));
	r.Add(keyToString(KEY_EGRAVE));
	r.Add(keyToString(KEY_EACUTE));
	r.Add(keyToString(KEY_ECIRCUMFLEX));
	r.Add(keyToString(KEY_EDIAERESIS));
	r.Add(keyToString(KEY_IGRAVE));
	r.Add(keyToString(KEY_IACUTE));
	r.Add(keyToString(KEY_ICIRCUMFLEX));
	r.Add(keyToString(KEY_IDIAERESIS));
	r.Add(keyToString(KEY_NTILDE));
	r.Add(keyToString(KEY_OGRAVE));
	r.Add(keyToString(KEY_OACUTE));
	r.Add(keyToString(KEY_OCIRCUMFLEX));
	r.Add(keyToString(KEY_OTILDE));
	r.Add(keyToString(KEY_ODIAERESIS));
	r.Add(keyToString(KEY_MULTIPLY));
	r.Add(keyToString(KEY_OSLASH));
	r.Add(keyToString(KEY_OOBLIQUE));
	r.Add(keyToString(KEY_UGRAVE));
	r.Add(keyToString(KEY_UACUTE));
	r.Add(keyToString(KEY_UCIRCUMFLEX));
	r.Add(keyToString(KEY_UDIAERESIS));
	r.Add(keyToString(KEY_YACUTE));
	r.Add(keyToString(KEY_SSHARP));
	r.Add(keyToString(KEY_ETH));
	r.Add(keyToString(KEY_DIVISION));
	r.Add(keyToString(KEY_THORN));
	r.Add(keyToString(KEY_YDIAERESIS));
	#endif
	#ifdef XK_LATIN2
	r.Add(keyToString(KEY_AOGONEK));
	r.Add(keyToString(KEY_BREVE));
	r.Add(keyToString(KEY_LSTROKE));
	r.Add(keyToString(KEY_LCARON));
	r.Add(keyToString(KEY_SACUTE));
	r.Add(keyToString(KEY_SCARON));
	r.Add(keyToString(KEY_SCEDILLA));
	r.Add(keyToString(KEY_TCARON));
	r.Add(keyToString(KEY_ZACUTE));
	r.Add(keyToString(KEY_ZCARON));
	r.Add(keyToString(KEY_ZABOVEDOT));
	r.Add(keyToString(KEY_OGONEK));
	r.Add(keyToString(KEY_CARON));
	r.Add(keyToString(KEY_DOUBLEACUTE));
	r.Add(keyToString(KEY_RACUTE));
	r.Add(keyToString(KEY_ABREVE));
	r.Add(keyToString(KEY_LACUTE));
	r.Add(keyToString(KEY_CACUTE));
	r.Add(keyToString(KEY_CCARON));
	r.Add(keyToString(KEY_EOGONEK));
	r.Add(keyToString(KEY_ECARON));
	r.Add(keyToString(KEY_DCARON));
	r.Add(keyToString(KEY_DSTROKE));
	r.Add(keyToString(KEY_NACUTE));
	r.Add(keyToString(KEY_NCARON));
	r.Add(keyToString(KEY_ODOUBLEACUTE));
	r.Add(keyToString(KEY_RCARON));
	r.Add(keyToString(KEY_URING));
	r.Add(keyToString(KEY_UDOUBLEACUTE));
	r.Add(keyToString(KEY_TCEDILLA));
	r.Add(keyToString(KEY_ABOVEDOT));
	#endif
	#ifdef XK_LATIN3
	r.Add(keyToString(KEY_HSTROKE));
	r.Add(keyToString(KEY_HCIRCUMFLEX));
	r.Add(keyToString(KEY_IABOVEDOT));
	r.Add(keyToString(KEY_GBREVE));
	r.Add(keyToString(KEY_JCIRCUMFLEX));
	r.Add(keyToString(KEY_IDOTLESS));
	r.Add(keyToString(KEY_CABOVEDOT));
	r.Add(keyToString(KEY_CCIRCUMFLEX));
	r.Add(keyToString(KEY_GABOVEDOT));
	r.Add(keyToString(KEY_GCIRCUMFLEX));
	r.Add(keyToString(KEY_UBREVE));
	r.Add(keyToString(KEY_SCIRCUMFLEX));
	#endif
	#ifdef XK_LATIN4
	r.Add(keyToString(KEY_KRA));
	r.Add(keyToString(KEY_RCEDILLA));
	r.Add(keyToString(KEY_ITILDE));
	r.Add(keyToString(KEY_LCEDILLA));
	r.Add(keyToString(KEY_EMACRON));
	r.Add(keyToString(KEY_GCEDILLA));
	r.Add(keyToString(KEY_TSLASH));
	r.Add(keyToString(KEY_ENG));
	r.Add(keyToString(KEY_AMACRON));
	r.Add(keyToString(KEY_IOGONEK));
	r.Add(keyToString(KEY_EABOVEDOT));
	r.Add(keyToString(KEY_IMACRON));
	r.Add(keyToString(KEY_NCEDILLA));
	r.Add(keyToString(KEY_OMACRON));
	r.Add(keyToString(KEY_KCEDILLA));
	r.Add(keyToString(KEY_UOGONEK));
	r.Add(keyToString(KEY_UTILDE));
	r.Add(keyToString(KEY_UMACRON));
	#endif
	#ifdef XK_LATIN8
	r.Add(keyToString(KEY_WCIRCUMFLEX));
	r.Add(keyToString(KEY_YCIRCUMFLEX));
	r.Add(keyToString(KEY_BABOVEDOT));
	r.Add(keyToString(KEY_DABOVEDOT));
	r.Add(keyToString(KEY_FABOVEDOT));
	r.Add(keyToString(KEY_MABOVEDOT));
	r.Add(keyToString(KEY_PABOVEDOT));
	r.Add(keyToString(KEY_SABOVEDOT));
	r.Add(keyToString(KEY_TABOVEDOT));
	r.Add(keyToString(KEY_WGRAVE));
	r.Add(keyToString(KEY_WACUTE));
	r.Add(keyToString(KEY_WDIAERESIS));
	r.Add(keyToString(KEY_YGRAVE));
	#endif
	#ifdef XK_LATIN9
	r.Add(keyToString(KEY_OE));
	#endif
	#ifdef XK_MATHEMATICAL
	r.Add(keyToString(KEY_ZEROSUPERIOR));
	r.Add(keyToString(KEY_FOURSUPERIOR));
	r.Add(keyToString(KEY_FIVESUPERIOR));
	r.Add(keyToString(KEY_SIXSUPERIOR));
	r.Add(keyToString(KEY_SEVENSUPERIOR));
	r.Add(keyToString(KEY_EIGHTSUPERIOR));
	r.Add(keyToString(KEY_NINESUPERIOR));
	r.Add(keyToString(KEY_ZEROSUBSCRIPT));
	r.Add(keyToString(KEY_ONESUBSCRIPT));
	r.Add(keyToString(KEY_TWOSUBSCRIPT));
	r.Add(keyToString(KEY_THREESUBSCRIPT));
	r.Add(keyToString(KEY_FOURSUBSCRIPT));
	r.Add(keyToString(KEY_FIVESUBSCRIPT));
	r.Add(keyToString(KEY_SIXSUBSCRIPT));
	r.Add(keyToString(KEY_SEVENSUBSCRIPT));
	r.Add(keyToString(KEY_EIGHTSUBSCRIPT));
	r.Add(keyToString(KEY_NINESUBSCRIPT));
	r.Add(keyToString(KEY_PARTDIFFERENTIAL));
	r.Add(keyToString(KEY_EMPTYSET));
	r.Add(keyToString(KEY_ELEMENTOF));
	r.Add(keyToString(KEY_NOTELEMENTOF));
	r.Add(keyToString(KEY_CONTAINSAS));
	r.Add(keyToString(KEY_SQUAREROOT));
	r.Add(keyToString(KEY_CUBEROOT));
	r.Add(keyToString(KEY_FOURTHROOT));
	r.Add(keyToString(KEY_DINTEGRAL));
	r.Add(keyToString(KEY_TINTEGRAL));
	r.Add(keyToString(KEY_BECAUSE));
	r.Add(keyToString(KEY_APPROXEQ));
	r.Add(keyToString(KEY_NOTAPPROXEQ));
	r.Add(keyToString(KEY_NOTIDENTICAL));
	r.Add(keyToString(KEY_STRICTEQ));
	#endif
	#ifdef XK_MISCELLANY
	r.Add(keyToString(KEY_BACKSPACE));
	r.Add(keyToString(KEY_TAB));
	r.Add(keyToString(KEY_LINEFEED));
	r.Add(keyToString(KEY_CLEAR));
	r.Add(keyToString(KEY_RETURN));
	r.Add(keyToString(KEY_PAUSE));
	r.Add(keyToString(KEY_SCROLL_LOCK));
	r.Add(keyToString(KEY_SYS_REQ));
	r.Add(keyToString(KEY_ESCAPE));
	r.Add(keyToString(KEY_DELETE));
	r.Add(keyToString(KEY_MULTI_KEY));
	r.Add(keyToString(KEY_CODEINPUT));
	r.Add(keyToString(KEY_SINGLECANDIDATE));
	r.Add(keyToString(KEY_MULTIPLECANDIDATE));
	r.Add(keyToString(KEY_PREVIOUSCANDIDATE));
	r.Add(keyToString(KEY_KANJI));
	r.Add(keyToString(KEY_MUHENKAN));
	r.Add(keyToString(KEY_HENKAN_MODE));
	r.Add(keyToString(KEY_HENKAN));
	r.Add(keyToString(KEY_ROMAJI));
	r.Add(keyToString(KEY_HIRAGANA));
	r.Add(keyToString(KEY_KATAKANA));
	r.Add(keyToString(KEY_HIRAGANA_KATAKANA));
	r.Add(keyToString(KEY_ZENKAKU));
	r.Add(keyToString(KEY_HANKAKU));
	r.Add(keyToString(KEY_ZENKAKU_HANKAKU));
	r.Add(keyToString(KEY_TOUROKU));
	r.Add(keyToString(KEY_MASSYO));
	r.Add(keyToString(KEY_KANA_LOCK));
	r.Add(keyToString(KEY_KANA_SHIFT));
	r.Add(keyToString(KEY_EISU_SHIFT));
	r.Add(keyToString(KEY_EISU_TOGGLE));
	r.Add(keyToString(KEY_KANJI_BANGOU));
	r.Add(keyToString(KEY_ZEN_KOHO));
	r.Add(keyToString(KEY_MAE_KOHO));
	r.Add(keyToString(KEY_HOME));
	r.Add(keyToString(KEY_LEFT));
	r.Add(keyToString(KEY_UP));
	r.Add(keyToString(KEY_RIGHT));
	r.Add(keyToString(KEY_DOWN));
	r.Add(keyToString(KEY_PRIOR));
	r.Add(keyToString(KEY_PAGE_UP));
	r.Add(keyToString(KEY_NEXT));
	r.Add(keyToString(KEY_PAGE_DOWN));
	r.Add(keyToString(KEY_END));
	r.Add(keyToString(KEY_BEGIN));
	r.Add(keyToString(KEY_SELECT));
	r.Add(keyToString(KEY_PRINT));
	r.Add(keyToString(KEY_EXECUTE));
	r.Add(keyToString(KEY_INSERT));
	r.Add(keyToString(KEY_UNDO));
	r.Add(keyToString(KEY_REDO));
	r.Add(keyToString(KEY_MENU));
	r.Add(keyToString(KEY_FIND));
	r.Add(keyToString(KEY_CANCEL));
	r.Add(keyToString(KEY_HELP));
	r.Add(keyToString(KEY_BREAK));
	r.Add(keyToString(KEY_MODE_SWITCH));
	r.Add(keyToString(KEY_SCRIPT_SWITCH));
	r.Add(keyToString(KEY_NUM_LOCK));
	r.Add(keyToString(KEY_KP_SPACE));
	r.Add(keyToString(KEY_KP_TAB));
	r.Add(keyToString(KEY_KP_ENTER));
	r.Add(keyToString(KEY_KP_F1));
	r.Add(keyToString(KEY_KP_F2));
	r.Add(keyToString(KEY_KP_F3));
	r.Add(keyToString(KEY_KP_F4));
	r.Add(keyToString(KEY_KP_HOME));
	r.Add(keyToString(KEY_KP_LEFT));
	r.Add(keyToString(KEY_KP_UP));
	r.Add(keyToString(KEY_KP_RIGHT));
	r.Add(keyToString(KEY_KP_DOWN));
	r.Add(keyToString(KEY_KP_PRIOR));
	r.Add(keyToString(KEY_KP_PAGE_UP));
	r.Add(keyToString(KEY_KP_NEXT));
	r.Add(keyToString(KEY_KP_PAGE_DOWN));
	r.Add(keyToString(KEY_KP_END));
	r.Add(keyToString(KEY_KP_BEGIN));
	r.Add(keyToString(KEY_KP_INSERT));
	r.Add(keyToString(KEY_KP_DELETE));
	r.Add(keyToString(KEY_KP_EQUAL));
	r.Add(keyToString(KEY_KP_MULTIPLY));
	r.Add(keyToString(KEY_KP_ADD));
	r.Add(keyToString(KEY_KP_SEPARATOR));
	r.Add(keyToString(KEY_KP_SUBTRACT));
	r.Add(keyToString(KEY_KP_DECIMAL));
	r.Add(keyToString(KEY_KP_DIVIDE));
	r.Add(keyToString(KEY_KP_0));
	r.Add(keyToString(KEY_KP_1));
	r.Add(keyToString(KEY_KP_2));
	r.Add(keyToString(KEY_KP_3));
	r.Add(keyToString(KEY_KP_4));
	r.Add(keyToString(KEY_KP_5));
	r.Add(keyToString(KEY_KP_6));
	r.Add(keyToString(KEY_KP_7));
	r.Add(keyToString(KEY_KP_8));
	r.Add(keyToString(KEY_KP_9));
	r.Add(keyToString(KEY_F1));
	r.Add(keyToString(KEY_F2));
	r.Add(keyToString(KEY_F3));
	r.Add(keyToString(KEY_F4));
	r.Add(keyToString(KEY_F5));
	r.Add(keyToString(KEY_F6));
	r.Add(keyToString(KEY_F7));
	r.Add(keyToString(KEY_F8));
	r.Add(keyToString(KEY_F9));
	r.Add(keyToString(KEY_F10));
	r.Add(keyToString(KEY_F11));
	r.Add(keyToString(KEY_L1));
	r.Add(keyToString(KEY_F12));
	r.Add(keyToString(KEY_L2));
	r.Add(keyToString(KEY_F13));
	r.Add(keyToString(KEY_L3));
	r.Add(keyToString(KEY_F14));
	r.Add(keyToString(KEY_L4));
	r.Add(keyToString(KEY_F15));
	r.Add(keyToString(KEY_L5));
	r.Add(keyToString(KEY_F16));
	r.Add(keyToString(KEY_L6));
	r.Add(keyToString(KEY_F17));
	r.Add(keyToString(KEY_L7));
	r.Add(keyToString(KEY_F18));
	r.Add(keyToString(KEY_L8));
	r.Add(keyToString(KEY_F19));
	r.Add(keyToString(KEY_L9));
	r.Add(keyToString(KEY_F20));
	r.Add(keyToString(KEY_L10));
	r.Add(keyToString(KEY_F21));
	r.Add(keyToString(KEY_R1));
	r.Add(keyToString(KEY_F22));
	r.Add(keyToString(KEY_R2));
	r.Add(keyToString(KEY_F23));
	r.Add(keyToString(KEY_R3));
	r.Add(keyToString(KEY_F24));
	r.Add(keyToString(KEY_R4));
	r.Add(keyToString(KEY_F25));
	r.Add(keyToString(KEY_R5));
	r.Add(keyToString(KEY_F26));
	r.Add(keyToString(KEY_R6));
	r.Add(keyToString(KEY_F27));
	r.Add(keyToString(KEY_R7));
	r.Add(keyToString(KEY_F28));
	r.Add(keyToString(KEY_R8));
	r.Add(keyToString(KEY_F29));
	r.Add(keyToString(KEY_R9));
	r.Add(keyToString(KEY_F30));
	r.Add(keyToString(KEY_R10));
	r.Add(keyToString(KEY_F31));
	r.Add(keyToString(KEY_R11));
	r.Add(keyToString(KEY_F32));
	r.Add(keyToString(KEY_R12));
	r.Add(keyToString(KEY_F33));
	r.Add(keyToString(KEY_R13));
	r.Add(keyToString(KEY_F34));
	r.Add(keyToString(KEY_R14));
	r.Add(keyToString(KEY_F35));
	r.Add(keyToString(KEY_R15));
	r.Add(keyToString(KEY_SHIFT_L));
	r.Add(keyToString(KEY_SHIFT_R));
	r.Add(keyToString(KEY_CONTROL_L));
	r.Add(keyToString(KEY_CONTROL_R));
	r.Add(keyToString(KEY_CAPS_LOCK));
	r.Add(keyToString(KEY_SHIFT_LOCK));
	r.Add(keyToString(KEY_META_L));
	r.Add(keyToString(KEY_META_R));
	r.Add(keyToString(KEY_ALT_L));
	r.Add(keyToString(KEY_ALT_R));
	r.Add(keyToString(KEY_SUPER_L));
	r.Add(keyToString(KEY_SUPER_R));
	r.Add(keyToString(KEY_HYPER_L));
	r.Add(keyToString(KEY_HYPER_R));
	#endif
	#ifdef XK_PUBLISHING
	r.Add(keyToString(KEY_EMSPACE));
	r.Add(keyToString(KEY_ENSPACE));
	r.Add(keyToString(KEY_EM3SPACE));
	r.Add(keyToString(KEY_EM4SPACE));
	r.Add(keyToString(KEY_DIGITSPACE));
	r.Add(keyToString(KEY_PUNCTSPACE));
	r.Add(keyToString(KEY_THINSPACE));
	r.Add(keyToString(KEY_HAIRSPACE));
	r.Add(keyToString(KEY_EMDASH));
	r.Add(keyToString(KEY_ENDASH));
	r.Add(keyToString(KEY_SIGNIFBLANK));
	r.Add(keyToString(KEY_ELLIPSIS));
	r.Add(keyToString(KEY_DOUBBASELINEDOT));
	r.Add(keyToString(KEY_ONETHIRD));
	r.Add(keyToString(KEY_TWOTHIRDS));
	r.Add(keyToString(KEY_ONEFIFTH));
	r.Add(keyToString(KEY_TWOFIFTHS));
	r.Add(keyToString(KEY_THREEFIFTHS));
	r.Add(keyToString(KEY_FOURFIFTHS));
	r.Add(keyToString(KEY_ONESIXTH));
	r.Add(keyToString(KEY_FIVESIXTHS));
	r.Add(keyToString(KEY_CAREOF));
	r.Add(keyToString(KEY_FIGDASH));
	r.Add(keyToString(KEY_LEFTANGLEBRACKET));
	r.Add(keyToString(KEY_DECIMALPOINT));
	r.Add(keyToString(KEY_RIGHTANGLEBRACKET));
	r.Add(keyToString(KEY_MARKER));
	r.Add(keyToString(KEY_ONEEIGHTH));
	r.Add(keyToString(KEY_THREEEIGHTHS));
	r.Add(keyToString(KEY_FIVEEIGHTHS));
	r.Add(keyToString(KEY_SEVENEIGHTHS));
	r.Add(keyToString(KEY_TRADEMARK));
	r.Add(keyToString(KEY_SIGNATUREMARK));
	r.Add(keyToString(KEY_TRADEMARKINCIRCLE));
	r.Add(keyToString(KEY_LEFTOPENTRIANGLE));
	r.Add(keyToString(KEY_RIGHTOPENTRIANGLE));
	r.Add(keyToString(KEY_EMOPENCIRCLE));
	r.Add(keyToString(KEY_EMOPENRECTANGLE));
	r.Add(keyToString(KEY_LEFTSINGLEQUOTEMARK));
	r.Add(keyToString(KEY_RIGHTSINGLEQUOTEMARK));
	r.Add(keyToString(KEY_LEFTDOUBLEQUOTEMARK));
	r.Add(keyToString(KEY_RIGHTDOUBLEQUOTEMARK));
	r.Add(keyToString(KEY_PRESCRIPTION));
	r.Add(keyToString(KEY_PERMILLE));
	r.Add(keyToString(KEY_MINUTES));
	r.Add(keyToString(KEY_SECONDS));
	r.Add(keyToString(KEY_LATINCROSS));
	r.Add(keyToString(KEY_HEXAGRAM));
	r.Add(keyToString(KEY_FILLEDRECTBULLET));
	r.Add(keyToString(KEY_FILLEDLEFTTRIBULLET));
	r.Add(keyToString(KEY_FILLEDRIGHTTRIBULLET));
	r.Add(keyToString(KEY_EMFILLEDCIRCLE));
	r.Add(keyToString(KEY_EMFILLEDRECT));
	r.Add(keyToString(KEY_ENOPENCIRCBULLET));
	r.Add(keyToString(KEY_ENOPENSQUAREBULLET));
	r.Add(keyToString(KEY_OPENRECTBULLET));
	r.Add(keyToString(KEY_OPENTRIBULLETUP));
	r.Add(keyToString(KEY_OPENTRIBULLETDOWN));
	r.Add(keyToString(KEY_OPENSTAR));
	r.Add(keyToString(KEY_ENFILLEDCIRCBULLET));
	r.Add(keyToString(KEY_ENFILLEDSQBULLET));
	r.Add(keyToString(KEY_FILLEDTRIBULLETUP));
	r.Add(keyToString(KEY_FILLEDTRIBULLETDOWN));
	r.Add(keyToString(KEY_LEFTPOINTER));
	r.Add(keyToString(KEY_RIGHTPOINTER));
	r.Add(keyToString(KEY_CLUB));
	r.Add(keyToString(KEY_DIAMOND));
	r.Add(keyToString(KEY_HEART));
	r.Add(keyToString(KEY_MALTESECROSS));
	r.Add(keyToString(KEY_DAGGER));
	r.Add(keyToString(KEY_DOUBLEDAGGER));
	r.Add(keyToString(KEY_CHECKMARK));
	r.Add(keyToString(KEY_BALLOTCROSS));
	r.Add(keyToString(KEY_MUSICALSHARP));
	r.Add(keyToString(KEY_MUSICALFLAT));
	r.Add(keyToString(KEY_MALESYMBOL));
	r.Add(keyToString(KEY_FEMALESYMBOL));
	r.Add(keyToString(KEY_TELEPHONE));
	r.Add(keyToString(KEY_TELEPHONERECORDER));
	r.Add(keyToString(KEY_PHONOGRAPHCOPYRIGHT));
	r.Add(keyToString(KEY_CARET));
	r.Add(keyToString(KEY_SINGLELOWQUOTEMARK));
	r.Add(keyToString(KEY_DOUBLELOWQUOTEMARK));
	r.Add(keyToString(KEY_CURSOR));
	#endif
	#ifdef XK_SINHALA
	r.Add(keyToString(KEY_SINH_NG));
	r.Add(keyToString(KEY_SINH_H2));
	r.Add(keyToString(KEY_SINH_A));
	r.Add(keyToString(KEY_SINH_AA));
	r.Add(keyToString(KEY_SINH_AE));
	r.Add(keyToString(KEY_SINH_AEE));
	r.Add(keyToString(KEY_SINH_I));
	r.Add(keyToString(KEY_SINH_II));
	r.Add(keyToString(KEY_SINH_U));
	r.Add(keyToString(KEY_SINH_UU));
	r.Add(keyToString(KEY_SINH_RI));
	r.Add(keyToString(KEY_SINH_RII));
	r.Add(keyToString(KEY_SINH_LU));
	r.Add(keyToString(KEY_SINH_LUU));
	r.Add(keyToString(KEY_SINH_E));
	r.Add(keyToString(KEY_SINH_EE));
	r.Add(keyToString(KEY_SINH_AI));
	r.Add(keyToString(KEY_SINH_O));
	r.Add(keyToString(KEY_SINH_OO));
	r.Add(keyToString(KEY_SINH_AU));
	r.Add(keyToString(KEY_SINH_KA));
	r.Add(keyToString(KEY_SINH_KHA));
	r.Add(keyToString(KEY_SINH_GA));
	r.Add(keyToString(KEY_SINH_GHA));
	r.Add(keyToString(KEY_SINH_NG2));
	r.Add(keyToString(KEY_SINH_NGA));
	r.Add(keyToString(KEY_SINH_CA));
	r.Add(keyToString(KEY_SINH_CHA));
	r.Add(keyToString(KEY_SINH_JA));
	r.Add(keyToString(KEY_SINH_JHA));
	r.Add(keyToString(KEY_SINH_NYA));
	r.Add(keyToString(KEY_SINH_JNYA));
	r.Add(keyToString(KEY_SINH_NJA));
	r.Add(keyToString(KEY_SINH_TTA));
	r.Add(keyToString(KEY_SINH_TTHA));
	r.Add(keyToString(KEY_SINH_DDA));
	r.Add(keyToString(KEY_SINH_DDHA));
	r.Add(keyToString(KEY_SINH_NNA));
	r.Add(keyToString(KEY_SINH_NDDA));
	r.Add(keyToString(KEY_SINH_THA));
	r.Add(keyToString(KEY_SINH_THHA));
	r.Add(keyToString(KEY_SINH_DHA));
	r.Add(keyToString(KEY_SINH_DHHA));
	r.Add(keyToString(KEY_SINH_NA));
	r.Add(keyToString(KEY_SINH_NDHA));
	r.Add(keyToString(KEY_SINH_PA));
	r.Add(keyToString(KEY_SINH_PHA));
	r.Add(keyToString(KEY_SINH_BA));
	r.Add(keyToString(KEY_SINH_BHA));
	r.Add(keyToString(KEY_SINH_MA));
	r.Add(keyToString(KEY_SINH_MBA));
	r.Add(keyToString(KEY_SINH_YA));
	r.Add(keyToString(KEY_SINH_RA));
	r.Add(keyToString(KEY_SINH_LA));
	r.Add(keyToString(KEY_SINH_VA));
	r.Add(keyToString(KEY_SINH_SHA));
	r.Add(keyToString(KEY_SINH_SSHA));
	r.Add(keyToString(KEY_SINH_SA));
	r.Add(keyToString(KEY_SINH_HA));
	r.Add(keyToString(KEY_SINH_LLA));
	r.Add(keyToString(KEY_SINH_FA));
	r.Add(keyToString(KEY_SINH_AL));
	r.Add(keyToString(KEY_SINH_AA2));
	r.Add(keyToString(KEY_SINH_AE2));
	r.Add(keyToString(KEY_SINH_AEE2));
	r.Add(keyToString(KEY_SINH_I2));
	r.Add(keyToString(KEY_SINH_II2));
	r.Add(keyToString(KEY_SINH_U2));
	r.Add(keyToString(KEY_SINH_UU2));
	r.Add(keyToString(KEY_SINH_RU2));
	r.Add(keyToString(KEY_SINH_E2));
	r.Add(keyToString(KEY_SINH_EE2));
	r.Add(keyToString(KEY_SINH_AI2));
	r.Add(keyToString(KEY_SINH_O2));
	r.Add(keyToString(KEY_SINH_OO2));
	r.Add(keyToString(KEY_SINH_AU2));
	r.Add(keyToString(KEY_SINH_LU2));
	r.Add(keyToString(KEY_SINH_RUU2));
	r.Add(keyToString(KEY_SINH_LUU2));
	r.Add(keyToString(KEY_SINH_KUNDDALIYA));
	#endif
	#ifdef XK_SPECIAL
	r.Add(keyToString(KEY_BLANK));
	r.Add(keyToString(KEY_SOLIDDIAMOND));
	r.Add(keyToString(KEY_CHECKERBOARD));
	r.Add(keyToString(KEY_HT));
	r.Add(keyToString(KEY_FF));
	r.Add(keyToString(KEY_CR));
	r.Add(keyToString(KEY_LF));
	r.Add(keyToString(KEY_NL));
	r.Add(keyToString(KEY_VT));
	r.Add(keyToString(KEY_LOWRIGHTCORNER));
	r.Add(keyToString(KEY_UPRIGHTCORNER));
	r.Add(keyToString(KEY_UPLEFTCORNER));
	r.Add(keyToString(KEY_LOWLEFTCORNER));
	r.Add(keyToString(KEY_CROSSINGLINES));
	r.Add(keyToString(KEY_HORIZLINESCAN1));
	r.Add(keyToString(KEY_HORIZLINESCAN3));
	r.Add(keyToString(KEY_HORIZLINESCAN5));
	r.Add(keyToString(KEY_HORIZLINESCAN7));
	r.Add(keyToString(KEY_HORIZLINESCAN9));
	r.Add(keyToString(KEY_LEFTT));
	r.Add(keyToString(KEY_RIGHTT));
	r.Add(keyToString(KEY_BOTT));
	r.Add(keyToString(KEY_TOPT));
	r.Add(keyToString(KEY_VERTBAR));
	#endif
	#ifdef XK_TECHNICAL
	r.Add(keyToString(KEY_LEFTRADICAL));
	r.Add(keyToString(KEY_TOPLEFTRADICAL));
	r.Add(keyToString(KEY_HORIZCONNECTOR));
	r.Add(keyToString(KEY_TOPINTEGRAL));
	r.Add(keyToString(KEY_BOTINTEGRAL));
	r.Add(keyToString(KEY_VERTCONNECTOR));
	r.Add(keyToString(KEY_TOPLEFTSQBRACKET));
	r.Add(keyToString(KEY_BOTLEFTSQBRACKET));
	r.Add(keyToString(KEY_TOPRIGHTSQBRACKET));
	r.Add(keyToString(KEY_BOTRIGHTSQBRACKET));
	r.Add(keyToString(KEY_TOPLEFTPARENS));
	r.Add(keyToString(KEY_BOTLEFTPARENS));
	r.Add(keyToString(KEY_TOPRIGHTPARENS));
	r.Add(keyToString(KEY_BOTRIGHTPARENS));
	r.Add(keyToString(KEY_LEFTMIDDLECURLYBRACE));
	r.Add(keyToString(KEY_RIGHTMIDDLECURLYBRACE));
	r.Add(keyToString(KEY_TOPLEFTSUMMATION));
	r.Add(keyToString(KEY_BOTLEFTSUMMATION));
	r.Add(keyToString(KEY_TOPVERTSUMMATIONCONNECTOR));
	r.Add(keyToString(KEY_BOTVERTSUMMATIONCONNECTOR));
	r.Add(keyToString(KEY_TOPRIGHTSUMMATION));
	r.Add(keyToString(KEY_BOTRIGHTSUMMATION));
	r.Add(keyToString(KEY_RIGHTMIDDLESUMMATION));
	r.Add(keyToString(KEY_LESSTHANEQUAL));
	r.Add(keyToString(KEY_NOTEQUAL));
	r.Add(keyToString(KEY_GREATERTHANEQUAL));
	r.Add(keyToString(KEY_INTEGRAL));
	r.Add(keyToString(KEY_THEREFORE));
	r.Add(keyToString(KEY_VARIATION));
	r.Add(keyToString(KEY_INFINITY));
	r.Add(keyToString(KEY_NABLA));
	r.Add(keyToString(KEY_APPROXIMATE));
	r.Add(keyToString(KEY_SIMILAREQUAL));
	r.Add(keyToString(KEY_IFONLYIF));
	r.Add(keyToString(KEY_IMPLIES));
	r.Add(keyToString(KEY_IDENTICAL));
	r.Add(keyToString(KEY_RADICAL));
	r.Add(keyToString(KEY_INCLUDEDIN));
	r.Add(keyToString(KEY_INCLUDES));
	r.Add(keyToString(KEY_INTERSECTION));
	r.Add(keyToString(KEY_UNION));
	r.Add(keyToString(KEY_LOGICALAND));
	r.Add(keyToString(KEY_LOGICALOR));
	r.Add(keyToString(KEY_PARTIALDERIVATIVE));
	r.Add(keyToString(KEY_FUNCTION));
	r.Add(keyToString(KEY_LEFTARROW));
	r.Add(keyToString(KEY_UPARROW));
	r.Add(keyToString(KEY_RIGHTARROW));
	r.Add(keyToString(KEY_DOWNARROW));
	#endif
	#ifdef XK_THAI
	r.Add(keyToString(KEY_THAI_KOKAI));
	r.Add(keyToString(KEY_THAI_KHOKHAI));
	r.Add(keyToString(KEY_THAI_KHOKHUAT));
	r.Add(keyToString(KEY_THAI_KHOKHWAI));
	r.Add(keyToString(KEY_THAI_KHOKHON));
	r.Add(keyToString(KEY_THAI_KHORAKHANG));
	r.Add(keyToString(KEY_THAI_NGONGU));
	r.Add(keyToString(KEY_THAI_CHOCHAN));
	r.Add(keyToString(KEY_THAI_CHOCHING));
	r.Add(keyToString(KEY_THAI_CHOCHANG));
	r.Add(keyToString(KEY_THAI_SOSO));
	r.Add(keyToString(KEY_THAI_CHOCHOE));
	r.Add(keyToString(KEY_THAI_YOYING));
	r.Add(keyToString(KEY_THAI_DOCHADA));
	r.Add(keyToString(KEY_THAI_TOPATAK));
	r.Add(keyToString(KEY_THAI_THOTHAN));
	r.Add(keyToString(KEY_THAI_THONANGMONTHO));
	r.Add(keyToString(KEY_THAI_THOPHUTHAO));
	r.Add(keyToString(KEY_THAI_NONEN));
	r.Add(keyToString(KEY_THAI_DODEK));
	r.Add(keyToString(KEY_THAI_TOTAO));
	r.Add(keyToString(KEY_THAI_THOTHUNG));
	r.Add(keyToString(KEY_THAI_THOTHAHAN));
	r.Add(keyToString(KEY_THAI_THOTHONG));
	r.Add(keyToString(KEY_THAI_NONU));
	r.Add(keyToString(KEY_THAI_BOBAIMAI));
	r.Add(keyToString(KEY_THAI_POPLA));
	r.Add(keyToString(KEY_THAI_PHOPHUNG));
	r.Add(keyToString(KEY_THAI_FOFA));
	r.Add(keyToString(KEY_THAI_PHOPHAN));
	r.Add(keyToString(KEY_THAI_FOFAN));
	r.Add(keyToString(KEY_THAI_PHOSAMPHAO));
	r.Add(keyToString(KEY_THAI_MOMA));
	r.Add(keyToString(KEY_THAI_YOYAK));
	r.Add(keyToString(KEY_THAI_RORUA));
	r.Add(keyToString(KEY_THAI_RU));
	r.Add(keyToString(KEY_THAI_LOLING));
	r.Add(keyToString(KEY_THAI_LU));
	r.Add(keyToString(KEY_THAI_WOWAEN));
	r.Add(keyToString(KEY_THAI_SOSALA));
	r.Add(keyToString(KEY_THAI_SORUSI));
	r.Add(keyToString(KEY_THAI_SOSUA));
	r.Add(keyToString(KEY_THAI_HOHIP));
	r.Add(keyToString(KEY_THAI_LOCHULA));
	r.Add(keyToString(KEY_THAI_OANG));
	r.Add(keyToString(KEY_THAI_HONOKHUK));
	r.Add(keyToString(KEY_THAI_PAIYANNOI));
	r.Add(keyToString(KEY_THAI_SARAA));
	r.Add(keyToString(KEY_THAI_MAIHANAKAT));
	r.Add(keyToString(KEY_THAI_SARAAA));
	r.Add(keyToString(KEY_THAI_SARAAM));
	r.Add(keyToString(KEY_THAI_SARAI));
	r.Add(keyToString(KEY_THAI_SARAII));
	r.Add(keyToString(KEY_THAI_SARAUE));
	r.Add(keyToString(KEY_THAI_SARAUEE));
	r.Add(keyToString(KEY_THAI_SARAU));
	r.Add(keyToString(KEY_THAI_SARAUU));
	r.Add(keyToString(KEY_THAI_PHINTHU));
	r.Add(keyToString(KEY_THAI_MAIHANAKAT_MAITHO));
	r.Add(keyToString(KEY_THAI_BAHT));
	r.Add(keyToString(KEY_THAI_SARAE));
	r.Add(keyToString(KEY_THAI_SARAAE));
	r.Add(keyToString(KEY_THAI_SARAO));
	r.Add(keyToString(KEY_THAI_SARAAIMAIMUAN));
	r.Add(keyToString(KEY_THAI_SARAAIMAIMALAI));
	r.Add(keyToString(KEY_THAI_LAKKHANGYAO));
	r.Add(keyToString(KEY_THAI_MAIYAMOK));
	r.Add(keyToString(KEY_THAI_MAITAIKHU));
	r.Add(keyToString(KEY_THAI_MAIEK));
	r.Add(keyToString(KEY_THAI_MAITHO));
	r.Add(keyToString(KEY_THAI_MAITRI));
	r.Add(keyToString(KEY_THAI_MAICHATTAWA));
	r.Add(keyToString(KEY_THAI_THANTHAKHAT));
	r.Add(keyToString(KEY_THAI_NIKHAHIT));
	r.Add(keyToString(KEY_THAI_LEKSUN));
	r.Add(keyToString(KEY_THAI_LEKNUNG));
	r.Add(keyToString(KEY_THAI_LEKSONG));
	r.Add(keyToString(KEY_THAI_LEKSAM));
	r.Add(keyToString(KEY_THAI_LEKSI));
	r.Add(keyToString(KEY_THAI_LEKHA));
	r.Add(keyToString(KEY_THAI_LEKHOK));
	r.Add(keyToString(KEY_THAI_LEKCHET));
	r.Add(keyToString(KEY_THAI_LEKPAET));
	r.Add(keyToString(KEY_THAI_LEKKAO));
	#endif
	#ifdef XK_VIETNAMESE
	r.Add(keyToString(KEY_ABELOWDOT));
	r.Add(keyToString(KEY_AHOOK));
	r.Add(keyToString(KEY_ACIRCUMFLEXACUTE));
	r.Add(keyToString(KEY_ACIRCUMFLEXGRAVE));
	r.Add(keyToString(KEY_ACIRCUMFLEXHOOK));
	r.Add(keyToString(KEY_ACIRCUMFLEXTILDE));
	r.Add(keyToString(KEY_ACIRCUMFLEXBELOWDOT));
	r.Add(keyToString(KEY_ABREVEACUTE));
	r.Add(keyToString(KEY_ABREVEGRAVE));
	r.Add(keyToString(KEY_ABREVEHOOK));
	r.Add(keyToString(KEY_ABREVETILDE));
	r.Add(keyToString(KEY_ABREVEBELOWDOT));
	r.Add(keyToString(KEY_EBELOWDOT));
	r.Add(keyToString(KEY_EHOOK));
	r.Add(keyToString(KEY_ETILDE));
	r.Add(keyToString(KEY_ECIRCUMFLEXACUTE));
	r.Add(keyToString(KEY_ECIRCUMFLEXGRAVE));
	r.Add(keyToString(KEY_ECIRCUMFLEXHOOK));
	r.Add(keyToString(KEY_ECIRCUMFLEXTILDE));
	r.Add(keyToString(KEY_ECIRCUMFLEXBELOWDOT));
	r.Add(keyToString(KEY_IHOOK));
	r.Add(keyToString(KEY_IBELOWDOT));
	r.Add(keyToString(KEY_OBELOWDOT));
	r.Add(keyToString(KEY_OHOOK));
	r.Add(keyToString(KEY_OCIRCUMFLEXACUTE));
	r.Add(keyToString(KEY_OCIRCUMFLEXGRAVE));
	r.Add(keyToString(KEY_OCIRCUMFLEXHOOK));
	r.Add(keyToString(KEY_OCIRCUMFLEXTILDE));
	r.Add(keyToString(KEY_OCIRCUMFLEXBELOWDOT));
	r.Add(keyToString(KEY_OHORNACUTE));
	r.Add(keyToString(KEY_OHORNGRAVE));
	r.Add(keyToString(KEY_OHORNHOOK));
	r.Add(keyToString(KEY_OHORNTILDE));
	r.Add(keyToString(KEY_OHORNBELOWDOT));
	r.Add(keyToString(KEY_UBELOWDOT));
	r.Add(keyToString(KEY_UHOOK));
	r.Add(keyToString(KEY_UHORNACUTE));
	r.Add(keyToString(KEY_UHORNGRAVE));
	r.Add(keyToString(KEY_UHORNHOOK));
	r.Add(keyToString(KEY_UHORNTILDE));
	r.Add(keyToString(KEY_UHORNBELOWDOT));
	r.Add(keyToString(KEY_YBELOWDOT));
	r.Add(keyToString(KEY_YHOOK));
	r.Add(keyToString(KEY_YTILDE));
	r.Add(keyToString(KEY_OHORN));
	r.Add(keyToString(KEY_UHORN));
	#endif
	#ifdef XK_XKB_KEYS
	r.Add(keyToString(KEY_ISO_LOCK));
	r.Add(keyToString(KEY_ISO_LEVEL2_LATCH));
	r.Add(keyToString(KEY_ISO_LEVEL3_SHIFT));
	r.Add(keyToString(KEY_ISO_LEVEL3_LATCH));
	r.Add(keyToString(KEY_ISO_LEVEL3_LOCK));
	r.Add(keyToString(KEY_ISO_LEVEL5_SHIFT));
	r.Add(keyToString(KEY_ISO_LEVEL5_LATCH));
	r.Add(keyToString(KEY_ISO_LEVEL5_LOCK));
	r.Add(keyToString(KEY_ISO_GROUP_SHIFT));
	r.Add(keyToString(KEY_ISO_GROUP_LATCH));
	r.Add(keyToString(KEY_ISO_GROUP_LOCK));
	r.Add(keyToString(KEY_ISO_NEXT_GROUP));
	r.Add(keyToString(KEY_ISO_NEXT_GROUP_LOCK));
	r.Add(keyToString(KEY_ISO_PREV_GROUP));
	r.Add(keyToString(KEY_ISO_PREV_GROUP_LOCK));
	r.Add(keyToString(KEY_ISO_FIRST_GROUP));
	r.Add(keyToString(KEY_ISO_FIRST_GROUP_LOCK));
	r.Add(keyToString(KEY_ISO_LAST_GROUP));
	r.Add(keyToString(KEY_ISO_LAST_GROUP_LOCK));
	r.Add(keyToString(KEY_ISO_LEFT_TAB));
	r.Add(keyToString(KEY_ISO_MOVE_LINE_UP));
	r.Add(keyToString(KEY_ISO_MOVE_LINE_DOWN));
	r.Add(keyToString(KEY_ISO_PARTIAL_LINE_UP));
	r.Add(keyToString(KEY_ISO_PARTIAL_LINE_DOWN));
	r.Add(keyToString(KEY_ISO_PARTIAL_SPACE_LEFT));
	r.Add(keyToString(KEY_ISO_PARTIAL_SPACE_RIGHT));
	r.Add(keyToString(KEY_ISO_SET_MARGIN_LEFT));
	r.Add(keyToString(KEY_ISO_SET_MARGIN_RIGHT));
	r.Add(keyToString(KEY_ISO_RELEASE_MARGIN_LEFT));
	r.Add(keyToString(KEY_ISO_RELEASE_MARGIN_RIGHT));
	r.Add(keyToString(KEY_ISO_RELEASE_BOTH_MARGINS));
	r.Add(keyToString(KEY_ISO_FAST_CURSOR_LEFT));
	r.Add(keyToString(KEY_ISO_FAST_CURSOR_RIGHT));
	r.Add(keyToString(KEY_ISO_FAST_CURSOR_UP));
	r.Add(keyToString(KEY_ISO_FAST_CURSOR_DOWN));
	r.Add(keyToString(KEY_ISO_CONTINUOUS_UNDERLINE));
	r.Add(keyToString(KEY_ISO_DISCONTINUOUS_UNDERLINE));
	r.Add(keyToString(KEY_ISO_EMPHASIZE));
	r.Add(keyToString(KEY_ISO_CENTER_OBJECT));
	r.Add(keyToString(KEY_ISO_ENTER));
	r.Add(keyToString(KEY_DEAD_GRAVE));
	r.Add(keyToString(KEY_DEAD_ACUTE));
	r.Add(keyToString(KEY_DEAD_CIRCUMFLEX));
	r.Add(keyToString(KEY_DEAD_TILDE));
	r.Add(keyToString(KEY_DEAD_PERISPOMENI));
	r.Add(keyToString(KEY_DEAD_MACRON));
	r.Add(keyToString(KEY_DEAD_BREVE));
	r.Add(keyToString(KEY_DEAD_ABOVEDOT));
	r.Add(keyToString(KEY_DEAD_DIAERESIS));
	r.Add(keyToString(KEY_DEAD_ABOVERING));
	r.Add(keyToString(KEY_DEAD_DOUBLEACUTE));
	r.Add(keyToString(KEY_DEAD_CARON));
	r.Add(keyToString(KEY_DEAD_CEDILLA));
	r.Add(keyToString(KEY_DEAD_OGONEK));
	r.Add(keyToString(KEY_DEAD_IOTA));
	r.Add(keyToString(KEY_DEAD_VOICED_SOUND));
	r.Add(keyToString(KEY_DEAD_SEMIVOICED_SOUND));
	r.Add(keyToString(KEY_DEAD_BELOWDOT));
	r.Add(keyToString(KEY_DEAD_HOOK));
	r.Add(keyToString(KEY_DEAD_HORN));
	r.Add(keyToString(KEY_DEAD_STROKE));
	r.Add(keyToString(KEY_DEAD_ABOVECOMMA));
	r.Add(keyToString(KEY_DEAD_PSILI));
	r.Add(keyToString(KEY_DEAD_ABOVEREVERSEDCOMMA));
	r.Add(keyToString(KEY_DEAD_DASIA));
	r.Add(keyToString(KEY_DEAD_DOUBLEGRAVE));
	r.Add(keyToString(KEY_DEAD_BELOWRING));
	r.Add(keyToString(KEY_DEAD_BELOWMACRON));
	r.Add(keyToString(KEY_DEAD_BELOWCIRCUMFLEX));
	r.Add(keyToString(KEY_DEAD_BELOWTILDE));
	r.Add(keyToString(KEY_DEAD_BELOWBREVE));
	r.Add(keyToString(KEY_DEAD_BELOWDIAERESIS));
	r.Add(keyToString(KEY_DEAD_INVERTEDBREVE));
	r.Add(keyToString(KEY_DEAD_BELOWCOMMA));
	r.Add(keyToString(KEY_DEAD_CURRENCY));
	r.Add(keyToString(KEY_DEAD_LOWLINE));
	r.Add(keyToString(KEY_DEAD_ABOVEVERTICALLINE));
	r.Add(keyToString(KEY_DEAD_BELOWVERTICALLINE));
	r.Add(keyToString(KEY_DEAD_LONGSOLIDUSOVERLAY));
	r.Add(keyToString(KEY_DEAD_A));
	r.Add(keyToString(KEY_DEAD_E));
	r.Add(keyToString(KEY_DEAD_I));
	r.Add(keyToString(KEY_DEAD_O));
	r.Add(keyToString(KEY_DEAD_U));
	r.Add(keyToString(KEY_DEAD_SMALL_SCHWA));
	r.Add(keyToString(KEY_DEAD_CAPITAL_SCHWA));
	r.Add(keyToString(KEY_DEAD_GREEK));
	r.Add(keyToString(KEY_FIRST_VIRTUAL_SCREEN));
	r.Add(keyToString(KEY_PREV_VIRTUAL_SCREEN));
	r.Add(keyToString(KEY_NEXT_VIRTUAL_SCREEN));
	r.Add(keyToString(KEY_LAST_VIRTUAL_SCREEN));
	r.Add(keyToString(KEY_TERMINATE_SERVER));
	r.Add(keyToString(KEY_ACCESSX_ENABLE));
	r.Add(keyToString(KEY_ACCESSX_FEEDBACK_ENABLE));
	r.Add(keyToString(KEY_REPEATKEYS_ENABLE));
	r.Add(keyToString(KEY_SLOWKEYS_ENABLE));
	r.Add(keyToString(KEY_BOUNCEKEYS_ENABLE));
	r.Add(keyToString(KEY_STICKYKEYS_ENABLE));
	r.Add(keyToString(KEY_MOUSEKEYS_ENABLE));
	r.Add(keyToString(KEY_MOUSEKEYS_ACCEL_ENABLE));
	r.Add(keyToString(KEY_OVERLAY1_ENABLE));
	r.Add(keyToString(KEY_OVERLAY2_ENABLE));
	r.Add(keyToString(KEY_AUDIBLEBELL_ENABLE));
	r.Add(keyToString(KEY_POINTER_LEFT));
	r.Add(keyToString(KEY_POINTER_RIGHT));
	r.Add(keyToString(KEY_POINTER_UP));
	r.Add(keyToString(KEY_POINTER_DOWN));
	r.Add(keyToString(KEY_POINTER_UPLEFT));
	r.Add(keyToString(KEY_POINTER_UPRIGHT));
	r.Add(keyToString(KEY_POINTER_DOWNLEFT));
	r.Add(keyToString(KEY_POINTER_DOWNRIGHT));
	r.Add(keyToString(KEY_POINTER_BUTTON_DFLT));
	r.Add(keyToString(KEY_POINTER_BUTTON1));
	r.Add(keyToString(KEY_POINTER_BUTTON2));
	r.Add(keyToString(KEY_POINTER_BUTTON3));
	r.Add(keyToString(KEY_POINTER_BUTTON4));
	r.Add(keyToString(KEY_POINTER_BUTTON5));
	r.Add(keyToString(KEY_POINTER_DBLCLICK_DFLT));
	r.Add(keyToString(KEY_POINTER_DBLCLICK1));
	r.Add(keyToString(KEY_POINTER_DBLCLICK2));
	r.Add(keyToString(KEY_POINTER_DBLCLICK3));
	r.Add(keyToString(KEY_POINTER_DBLCLICK4));
	r.Add(keyToString(KEY_POINTER_DBLCLICK5));
	r.Add(keyToString(KEY_POINTER_DRAG_DFLT));
	r.Add(keyToString(KEY_POINTER_DRAG1));
	r.Add(keyToString(KEY_POINTER_DRAG2));
	r.Add(keyToString(KEY_POINTER_DRAG3));
	r.Add(keyToString(KEY_POINTER_DRAG4));
	r.Add(keyToString(KEY_POINTER_DRAG5));
	r.Add(keyToString(KEY_POINTER_ENABLEKEYS));
	r.Add(keyToString(KEY_POINTER_ACCELERATE));
	r.Add(keyToString(KEY_POINTER_DFLTBTNNEXT));
	r.Add(keyToString(KEY_POINTER_DFLTBTNPREV));
	r.Add(keyToString(KEY_CH));
	r.Add(keyToString(KEY_C_H));
	#endif
	#elif __WXMSW__
	r.Alloc(155);
	r.Add(keyToString(KEY_CANCEL));
	r.Add(keyToString(KEY_BACK));
	r.Add(keyToString(KEY_TAB));
	r.Add(keyToString(KEY_CLEAR));
	r.Add(keyToString(KEY_RETURN));
	r.Add(keyToString(KEY_SHIFT));
	r.Add(keyToString(KEY_CONTROL));
	r.Add(keyToString(KEY_MENU));
	r.Add(keyToString(KEY_PAUSE));
	r.Add(keyToString(KEY_CAPITAL));
	r.Add(keyToString(KEY_KANA));
	r.Add(keyToString(KEY_HANGEUL));
	r.Add(keyToString(KEY_HANGUL));
	r.Add(keyToString(KEY_JUNJA));
	r.Add(keyToString(KEY_FINAL));
	r.Add(keyToString(KEY_HANJA));
	r.Add(keyToString(KEY_KANJI));
	r.Add(keyToString(KEY_ESCAPE));
	r.Add(keyToString(KEY_CONVERT));
	r.Add(keyToString(KEY_NONCONVERT));
	r.Add(keyToString(KEY_ACCEPT));
	r.Add(keyToString(KEY_MODECHANGE));
	r.Add(keyToString(KEY_SPACE));
	r.Add(keyToString(KEY_PRIOR));
	r.Add(keyToString(KEY_NEXT));
	r.Add(keyToString(KEY_END));
	r.Add(keyToString(KEY_HOME));
	r.Add(keyToString(KEY_LEFT));
	r.Add(keyToString(KEY_UP));
	r.Add(keyToString(KEY_RIGHT));
	r.Add(keyToString(KEY_DOWN));
	r.Add(keyToString(KEY_SELECT));
	r.Add(keyToString(KEY_PRINT));
	r.Add(keyToString(KEY_EXECUTE));
	r.Add(keyToString(KEY_SNAPSHOT));
	r.Add(keyToString(KEY_INSERT));
	r.Add(keyToString(KEY_DELETE));
	r.Add(keyToString(KEY_HELP));
	r.Add(keyToString(KEY_LWIN));
	r.Add(keyToString(KEY_RWIN));
	r.Add(keyToString(KEY_APPS));
	r.Add(keyToString(KEY_SLEEP));
	r.Add(keyToString(KEY_NUMPAD0));
	r.Add(keyToString(KEY_NUMPAD1));
	r.Add(keyToString(KEY_NUMPAD2));
	r.Add(keyToString(KEY_NUMPAD3));
	r.Add(keyToString(KEY_NUMPAD4));
	r.Add(keyToString(KEY_NUMPAD5));
	r.Add(keyToString(KEY_NUMPAD6));
	r.Add(keyToString(KEY_NUMPAD7));
	r.Add(keyToString(KEY_NUMPAD8));
	r.Add(keyToString(KEY_NUMPAD9));
	r.Add(keyToString(KEY_MULTIPLY));
	r.Add(keyToString(KEY_ADD));
	r.Add(keyToString(KEY_SEPARATOR));
	r.Add(keyToString(KEY_SUBTRACT));
	r.Add(keyToString(KEY_DECIMAL));
	r.Add(keyToString(KEY_DIVIDE));
	r.Add(keyToString(KEY_F1));
	r.Add(keyToString(KEY_F2));
	r.Add(keyToString(KEY_F3));
	r.Add(keyToString(KEY_F4));
	r.Add(keyToString(KEY_F5));
	r.Add(keyToString(KEY_F6));
	r.Add(keyToString(KEY_F7));
	r.Add(keyToString(KEY_F8));
	r.Add(keyToString(KEY_F9));
	r.Add(keyToString(KEY_F10));
	r.Add(keyToString(KEY_F11));
	r.Add(keyToString(KEY_F12));
	r.Add(keyToString(KEY_F13));
	r.Add(keyToString(KEY_F14));
	r.Add(keyToString(KEY_F15));
	r.Add(keyToString(KEY_F16));
	r.Add(keyToString(KEY_F17));
	r.Add(keyToString(KEY_F18));
	r.Add(keyToString(KEY_F19));
	r.Add(keyToString(KEY_F20));
	r.Add(keyToString(KEY_F21));
	r.Add(keyToString(KEY_F22));
	r.Add(keyToString(KEY_F23));
	r.Add(keyToString(KEY_F24));
	r.Add(keyToString(KEY_NUMLOCK));
	r.Add(keyToString(KEY_SCROLL));
	r.Add(keyToString(KEY_OEM_NEC_EQUAL));
	r.Add(keyToString(KEY_OEM_FJ_JISHO));
	r.Add(keyToString(KEY_OEM_FJ_MASSHOU));
	r.Add(keyToString(KEY_OEM_FJ_TOUROKU));
	r.Add(keyToString(KEY_OEM_FJ_LOYA));
	r.Add(keyToString(KEY_OEM_FJ_ROYA));
	r.Add(keyToString(KEY_LSHIFT));
	r.Add(keyToString(KEY_RSHIFT));
	r.Add(keyToString(KEY_LCONTROL));
	r.Add(keyToString(KEY_RCONTROL));
	r.Add(keyToString(KEY_LMENU));
	r.Add(keyToString(KEY_RMENU));
	r.Add(keyToString(KEY_BROWSER_BACK));
	r.Add(keyToString(KEY_BROWSER_FORWARD));
	r.Add(keyToString(KEY_BROWSER_REFRESH));
	r.Add(keyToString(KEY_BROWSER_STOP));
	r.Add(keyToString(KEY_BROWSER_SEARCH));
	r.Add(keyToString(KEY_BROWSER_FAVORITES));
	r.Add(keyToString(KEY_BROWSER_HOME));
	r.Add(keyToString(KEY_VOLUME_MUTE));
	r.Add(keyToString(KEY_VOLUME_DOWN));
	r.Add(keyToString(KEY_VOLUME_UP));
	r.Add(keyToString(KEY_MEDIA_NEXT_TRACK));
	r.Add(keyToString(KEY_MEDIA_PREV_TRACK));
	r.Add(keyToString(KEY_MEDIA_STOP));
	r.Add(keyToString(KEY_MEDIA_PLAY_PAUSE));
	r.Add(keyToString(KEY_LAUNCH_MAIL));
	r.Add(keyToString(KEY_LAUNCH_MEDIA_SELECT));
	r.Add(keyToString(KEY_LAUNCH_APP1));
	r.Add(keyToString(KEY_LAUNCH_APP2));
	r.Add(keyToString(KEY_OEM_1));
	r.Add(keyToString(KEY_OEM_PLUS));
	r.Add(keyToString(KEY_OEM_COMMA));
	r.Add(keyToString(KEY_OEM_MINUS));
	r.Add(keyToString(KEY_OEM_PERIOD));
	r.Add(keyToString(KEY_OEM_2));
	r.Add(keyToString(KEY_OEM_3));
	r.Add(keyToString(KEY_OEM_4));
	r.Add(keyToString(KEY_OEM_5));
	r.Add(keyToString(KEY_OEM_6));
	r.Add(keyToString(KEY_OEM_7));
	r.Add(keyToString(KEY_OEM_8));
	r.Add(keyToString(KEY_OEM_AX));
	r.Add(keyToString(KEY_OEM_102));
	r.Add(keyToString(KEY_ICO_HELP));
	r.Add(keyToString(KEY_ICO_00));
	r.Add(keyToString(KEY_PROCESSKEY));
	r.Add(keyToString(KEY_ICO_CLEAR));
	r.Add(keyToString(KEY_PACKET));
	r.Add(keyToString(KEY_OEM_RESET));
	r.Add(keyToString(KEY_OEM_JUMP));
	r.Add(keyToString(KEY_OEM_PA1));
	r.Add(keyToString(KEY_OEM_PA2));
	r.Add(keyToString(KEY_OEM_PA3));
	r.Add(keyToString(KEY_OEM_WSCTRL));
	r.Add(keyToString(KEY_OEM_CUSEL));
	r.Add(keyToString(KEY_OEM_ATTN));
	r.Add(keyToString(KEY_OEM_FINISH));
	r.Add(keyToString(KEY_OEM_COPY));
	r.Add(keyToString(KEY_OEM_AUTO));
	r.Add(keyToString(KEY_OEM_ENLW));
	r.Add(keyToString(KEY_OEM_BACKTAB));
	r.Add(keyToString(KEY_ATTN));
	r.Add(keyToString(KEY_CRSEL));
	r.Add(keyToString(KEY_EXSEL));
	r.Add(keyToString(KEY_EREOF));
	r.Add(keyToString(KEY_PLAY));
	r.Add(keyToString(KEY_ZOOM));
	r.Add(keyToString(KEY_NONAME));
	r.Add(keyToString(KEY_PA1));
	r.Add(keyToString(KEY_OEM_CLEAR));
	#endif
	r.Add(keyToString(KEY_A));
	r.Add(keyToString(KEY_B));
	r.Add(keyToString(KEY_C));
	r.Add(keyToString(KEY_D));
	r.Add(keyToString(KEY_E));
	r.Add(keyToString(KEY_F));
	r.Add(keyToString(KEY_G));
	r.Add(keyToString(KEY_H));
	r.Add(keyToString(KEY_I));
	r.Add(keyToString(KEY_J));
	r.Add(keyToString(KEY_K));
	r.Add(keyToString(KEY_L));
	r.Add(keyToString(KEY_M));
	r.Add(keyToString(KEY_N));
	r.Add(keyToString(KEY_O));
	r.Add(keyToString(KEY_P));
	r.Add(keyToString(KEY_Q));
	r.Add(keyToString(KEY_R));
	r.Add(keyToString(KEY_S));
	r.Add(keyToString(KEY_T));
	r.Add(keyToString(KEY_U));
	r.Add(keyToString(KEY_V));
	r.Add(keyToString(KEY_W));
	r.Add(keyToString(KEY_X));
	r.Add(keyToString(KEY_Y));
	r.Add(keyToString(KEY_Z));

	return r;
}

// *****************************************************************************
// Class ShortcutEvent
// *****************************************************************************
		
ShortcutEvent::ShortcutEvent(wxEventType eventType, Modifier_e modifiers, Key_e key)
    : wxEvent(wxID_ANY, eventType), _shortcutKey(modifiers, key)
{
}

ShortcutEvent::ShortcutEvent(wxEventType eventType, ShortcutKey const& shortcutKey)
	: wxEvent(wxID_ANY, eventType), _shortcutKey(shortcutKey)
{
}

wxEvent* ShortcutEvent::Clone()const
{
    return new ShortcutEvent(*this);
}

Key_e ShortcutEvent::getKey()const
{
    return _shortcutKey.getKey();
}

Modifier_e ShortcutEvent::getModifiers()const
{
    return _shortcutKey.getModifiers();
}

ShortcutKey const& ShortcutEvent::getShortcutKey()const
{
	return _shortcutKey;
}

wxDEFINE_EVENT(EVT_SHORTCUT, ShortcutEvent);

// *****************************************************************************
// Class ShortcutThread
// *****************************************************************************

//! \todo a modifier pour prendre en compte tout les Displays
#ifdef __WXMSW__
ShortcutThread::ShortcutThread(wxEvtHandler *owner, std::vector<ShortcutKey>const& shortcutKeys)
: 	wxThread(wxTHREAD_JOINABLE), _owner(owner),
	_mutexCommunicationThread(false), _shortcutKeyCommunicationThread(nullptr),
	_communicationThread(CUMMUNICATION_THREAD_NONE),
	_shortcutKeys(shortcutKeys)
#else
ShortcutThread::ShortcutThread(wxEvtHandler *owner)
: 	wxThread(wxTHREAD_JOINABLE), _owner(owner),
	_mutexCommunicationThread(false), _shortcutKeyCommunicationThread(nullptr),
	_communicationThread(CUMMUNICATION_THREAD_NONE)
#endif
{
    #if defined(__UNIX__)
    static bool isXInitThreads = false;
    if(!isXInitThreads)
    {
		XInitThreads();
		isXInitThreads = true;
	}
    
    _display = XOpenDisplay(0);
    _root = XDefaultRootWindow(_display);
	_interCommunication = XCreateSimpleWindow(_display, _root, 0, 0, 1, 1, 0, 0, 0);
	XSelectInput(_display, _interCommunication, StructureNotifyMask);
    #endif
    
    //Run le thread
    Create();
	Run();
}

ShortcutThread::~ShortcutThread()
{
	if(IsRunning())
		halt();
		
    #if defined(__UNIX__)
    XCloseDisplay(_display);
    #endif
}

void ShortcutThread::registerShortcut(ShortcutKey const& shortcutKey)
{
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=CUMMUNICATION_THREAD_REGISTER;
	_shortcutKeyCommunicationThread=&shortcutKey;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	while(!PostThreadMessage(GetId(), WM_APP, 0, 0));
	#endif
	
	//On attend la fin d'utilisation des données.
	while(_mutexCommunicationThread);
}

void ShortcutThread::unregisterShortcut(ShortcutKey const& shortcutKey)
{
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=CUMMUNICATION_THREAD_UNREGISTER;
	_shortcutKeyCommunicationThread=&shortcutKey;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	while(!PostThreadMessage(GetId(), WM_APP, 0, 0));
	#endif
	
	//On attend la fin d'utilisation des données.
	while(_mutexCommunicationThread);
}

void ShortcutThread::halt()
{	
	//Si les données de communication avec le thread sont utiliser,
	//alors on attente.
	while(_mutexCommunicationThread);
	_mutexCommunicationThread=true;
	
	//Indique les valeurs à communiquer au thread.
	_communicationThread=CUMMUNICATION_THREAD_QUIT;
	_shortcutKeyCommunicationThread=nullptr;
	
	#if defined(__UNIX__)
	//Déverrouille le XNextEvent.
	XClientMessageEvent sendEvent;
	memset(&sendEvent, 0, sizeof(XClientMessageEvent));
	sendEvent.type = ClientMessage;
	sendEvent.window = _interCommunication;
	sendEvent.format = 32;
	
	XSendEvent(_display, _interCommunication, 0, 0, (XEvent*)&sendEvent);
	XFlush(_display);
	#elif defined(__WXMSW__)
	PostThreadMessage(GetId(), WM_APP, 0, 0);
	#endif
	
	//Attend la fin du thread.
	while(IsRunning());
}

//! \todo utiliser wxMutex
wxThread::ExitCode ShortcutThread::Entry()
{
	bool run = true;

	#if defined(__UNIX__)
	while(run)
	{
		//Si un événement est présent on le récupère.
		XNextEvent(_display, &_event);
		if(_event.type == KeyPress)
		{ 
			//Convertie le KeyCode en Key_e.
			Key_e key = (Key_e)XkbKeycodeToKeysym(_display, _event.xkey.keycode, 0, 0);
			//Mise en forme du raccourci.
			ShortcutKey shortcutKey((Modifier_e)_event.xkey.state, key);
			//Envoi de l'événement.
			ShortcutEvent *event = new ShortcutEvent(EVT_SHORTCUT, shortcutKey);
			wxQueueEvent(_owner, event);
		}
		else if(_event.type == ClientMessage)
		{
			switch(_communicationThread)
			{
				//Enregistre le raccourci.
				case CUMMUNICATION_THREAD_REGISTER:
					XGrabKey(_display, XKeysymToKeycode(_display, _shortcutKeyCommunicationThread->getKey()), _shortcutKeyCommunicationThread->getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
				break;
				
				//Désenregistrer le raccourci.
				case CUMMUNICATION_THREAD_UNREGISTER:
					XUngrabKey(_display, _shortcutKeyCommunicationThread->getKey(), _shortcutKeyCommunicationThread->getModifiers(), _root);
				break;
				
				//Quit le thread.
				case CUMMUNICATION_THREAD_QUIT:
					run = false;
				break;
				
				case CUMMUNICATION_THREAD_NONE:
				default:
				break;
			}

			//Fin d'utilisation des données de communication.
			_shortcutKeyCommunicationThread = nullptr;
			_mutexCommunicationThread = false;
		}
	}
	#elif defined(__WXMSW__)		
	while(run)
	{
		//Si un événement est présent.
		GetMessage(&_msgEvent, nullptr, 0, 0);
		//On le récupère.
		if(_msgEvent.message == WM_HOTKEY)
		{
			//Envoi de l'événement.
			ShortcutEvent *event = new ShortcutEvent(EVT_SHORTCUT, _shortcutKeys[(int)_msgEvent.wParam]);
			wxQueueEvent(_owner, event);
		}
		else if(_msgEvent.message == WM_APP)
		{
			switch(_communicationThread)
			{
				//Enregistre le raccourci.
				case CUMMUNICATION_THREAD_REGISTER:					
					for(unsigned int i = 0; i < _shortcutKeys.size(); i++)
					{
						if(_shortcutKeys[i] == *_shortcutKeyCommunicationThread)
						{
							RegisterHotKey(nullptr, i, _shortcutKeyCommunicationThread->getModifiers(), _shortcutKeyCommunicationThread->getKey());
							break;
						}
					}
				break;
				
				//Désenregistrer le raccourci.
				case CUMMUNICATION_THREAD_UNREGISTER:
					for(unsigned int i = 0; i < _shortcutKeys.size(); i++)
					{
						if(_shortcutKeys[i] == *_shortcutKeyCommunicationThread)
						{
							UnregisterHotKey(nullptr, i);
							break;
						}
					}
				break;
				
				//Quit le thread.
				case CUMMUNICATION_THREAD_QUIT:
					run = false;
				break;
				
				case CUMMUNICATION_THREAD_NONE:
				default:
				break;
			}
			
			//Fin d'utilisation des données de communication.
			_shortcutKeyCommunicationThread = nullptr;
			_mutexCommunicationThread = false;
		}
	}
	#endif

	return (wxThread::ExitCode)0;
}

// *****************************************************************************
// Class Shortcut
// *****************************************************************************

Shortcut::Shortcut(wxEvtHandler *owner)
: _thread(nullptr), _owner(owner), _enable(true)
{
	#ifdef __WXMSW__
	_thread = new ShortcutThread(_owner, _shortcutKeys);
	#else
	_thread = new ShortcutThread(_owner);
	#endif
}

Shortcut::~Shortcut()
{
	removeAll();
	if(_thread != nullptr)
		delete _thread;
}

void Shortcut::creat(Modifier_e modifiers, Key_e key)
{
    creat(ShortcutKey(modifiers, key));
}

void Shortcut::creat(ShortcutKey const& shortcutKey)
{   
    //Mémorise le raccourcie.
    _shortcutKeys.push_back(shortcutKey);
    
    //Si les raccourcis sont activés, on active le raccourci au prés du thread.
    if(_enable)
		_thread->registerShortcut(shortcutKey);
}

void Shortcut::remove(Modifier_e modifiers, Key_e key)
{
	remove(ShortcutKey(modifiers, key));
}

void Shortcut::remove(ShortcutKey const& shortcutKey)
{
	//Si les raccourcis sont activés, on désactive le raccourci au prés du thread.
    if(_enable)
		_thread->unregisterShortcut(shortcutKey);
		
    //Supprime le lien.
    for(unsigned int i = 0; i < _shortcutKeys.size(); i++)
    {
		if(_shortcutKeys[i] == shortcutKey)
		{
			_shortcutKeys.erase(_shortcutKeys.begin()+i);
			break;
		}
	}
}

void Shortcut::removeAll()
{
	//Si les raccourcis sont activés, on désactive tout les raccourcis au prés du thread.
    if(_enable)
    {
		for(auto it: _shortcutKeys)
			_thread->unregisterShortcut(it);
	}
		
	//Supprime raccourcis.
	_shortcutKeys.clear();
}

void Shortcut::enable(bool val)
{		
	//Si on doit désactiver.
	if(_enable == true && val == false)
	{
		//Désactive tout les raccourcis au prés du thread.
		for(auto it: _shortcutKeys)
			_thread->unregisterShortcut(it);
			
		delete _thread;
		_thread = nullptr;
	}
	//Si on doit activer.
	else if(_enable == false && val == true)
	{	
		//On relance le thread.
		#ifdef __WXMSW__
		_thread = new ShortcutThread(_owner, _shortcutKeys);
		#else
		_thread = new ShortcutThread(_owner);
		#endif

		//Active les raccourcis au prés du thread.
		for(auto &it: _shortcutKeys)			
			_thread->registerShortcut(it);
	}
	
	_enable = val;
}

bool Shortcut::isEnable()
{
	return _enable;
}
