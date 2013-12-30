//! \file **********************************************************************
//! \brief Source Gestion des raccourcis globaux.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie.
//! \version 1.5
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
: _modifiers(KEY_MODIFIER_NONE), _charKey('\0')
{
}

ShortcutKey::ShortcutKey(KeyModifier_e modifiers, char charKey)
: _modifiers(modifiers), _charKey(charKey)
{
}

bool ShortcutKey::operator<(ShortcutKey const& ins)const
{
	if(_charKey < ins._charKey)
		return true;
	else if(_charKey == ins._charKey)
	{
		if(_modifiers < ins._modifiers)
			return true;
	}
	
	return false;
}

bool ShortcutKey::operator==(ShortcutKey const& ins)const
{
	if((_modifiers == ins._modifiers) && (_charKey == ins._charKey))
		return true;
		
	return false;
}

bool ShortcutKey::operator!=(ShortcutKey const& ins)const
{
	if((_modifiers != ins._modifiers) || (_charKey != ins._charKey))
		return true;
		
	return false;
}

char ShortcutKey::getCharKey()const
{
	return _charKey;
}

KeyModifier_e ShortcutKey::getModifiers()const
{
	return _modifiers;
}

bool ShortcutKey::isOk()const
{
	if(_modifiers == KEY_MODIFIER_NONE || _charKey == '\0')
		return false;
		
	return true;
}

wxString ShortcutKey::shortcutKeyToString(ShortcutKey const& shortcut)
{
	wxString ret;
	
	// ShortcutKey valide ?
	if(!(	shortcut._modifiers  &KEY_MODIFIER_ALT ||
			shortcut._modifiers & KEY_MODIFIER_CONTROL ||
			#if defined(__UNIX__)
			shortcut._modifiers & KEY_MODIFIER_ALTGR ||
			#endif
			shortcut._modifiers & KEY_MODIFIER_SHIFT ||
			shortcut._modifiers & KEY_MODIFIER_SUPER) &&
			shortcut._charKey == '\0')
	{
		return wxEmptyString;
	}
	
	//Conversion du modificateur.
	KeyModifier_e statut = KEY_MODIFIER_CONTROL;
	for(unsigned int i = 0; i < NB_KEY_MODIFIER; i++)
	{
		switch(statut)
		{
			case KEY_MODIFIER_CONTROL:
			{
				if(shortcut._modifiers & KEY_MODIFIER_CONTROL)
					ret << "ctrl+";
				
				statut = KEY_MODIFIER_ALT;
			}break;
			
			case KEY_MODIFIER_ALT:
			{
				if(shortcut._modifiers & KEY_MODIFIER_ALT)
					ret << "alt+";
				
				#if defined(__UNIX__)
				statut = KEY_MODIFIER_ALTGR;
				#elif defined(__WXMSW__)
				statut = KEY_MODIFIER_SHIFT;
				#endif
			}break;
			
			#if defined(__UNIX__)
			case KEY_MODIFIER_ALTGR:
			{
				if(shortcut._modifiers & KEY_MODIFIER_ALTGR)
					ret << "altgr+";
				
				statut = KEY_MODIFIER_SHIFT;
			}break;
			#endif
			
			case KEY_MODIFIER_SHIFT:
			{
				if(shortcut._modifiers & KEY_MODIFIER_SHIFT)
					ret << "shift+";
				
				statut = KEY_MODIFIER_SUPER;
			}break;
			
			case KEY_MODIFIER_SUPER:
			{
				if(shortcut._modifiers & KEY_MODIFIER_SUPER)
					ret << "super+";
				
				statut = KEY_MODIFIER_NONE;
			}break;
			
			default:
			return wxEmptyString;
			break;
		}
	}
	
	//Ajout du charKey.
	ret << shortcut._charKey;
	
	//Minimalise
	ret.MakeLower();
	
	return ret;
}

ShortcutKey ShortcutKey::stringToShortcutKey(wxString const& shortcut)
{
	KeyModifier_e modifiers = KEY_MODIFIER_NONE;
	//char charKey = '\0';
	
	//Avent ou après le premier '+'.
	wxString before;
	wxString after;
	
	//Minimalise
	wxString tmp = shortcut;
	tmp.MakeLower();
	
	//Obtenir avent ou après le premier '+'.
	before = tmp.BeforeFirst('+', &after);
	
	//Conversion du modificateur.
	while(!before.IsEmpty())
	{		
		if(before == "ctrl")
			modifiers = modifiers|KEY_MODIFIER_CONTROL;
		else if(before == "alt")
			modifiers = modifiers|KEY_MODIFIER_ALT;
		#if defined(__UNIX__)
		else if(before == "altgr")
			modifiers = modifiers|KEY_MODIFIER_ALTGR;
		#endif
		else if(before == "shift")
			modifiers = modifiers|KEY_MODIFIER_SHIFT;
		else if(before == "super")
		modifiers = modifiers|KEY_MODIFIER_SUPER;
		else//Raccourci erronée.
			return ShortcutKey(KEY_MODIFIER_NONE, '\0');
		
		if(after.Len() == 1)
			return ShortcutKey(modifiers, *after.fn_str());
			
		
		//Obtenir le nouveau avent ou après le premier '+'
		tmp = after;
		before = tmp.BeforeFirst('+', &after);
	}
	
	//Raccourci erronée.
	return ShortcutKey(KEY_MODIFIER_NONE, '\0');
}

// *****************************************************************************
// Class ShortcutEvent
// *****************************************************************************
		
ShortcutEvent::ShortcutEvent(wxEventType eventType, KeyModifier_e modifiers, char charKey)
    : wxEvent(wxID_ANY, eventType), _shortcutKey(modifiers, charKey)
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

char ShortcutEvent::getCharKey()const
{
    return _shortcutKey.getCharKey();
}

KeyModifier_e ShortcutEvent::getModifiers()const
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
			//Convertie le KeyCode en char.
			const char charKey = *(XKeysymToString(XkbKeycodeToKeysym(_display, _event.xkey.keycode, 0, 0)));
			//Mise en forme du raccourci.
			ShortcutKey shortcutKey((KeyModifier_e)_event.xkey.state, charKey);
			//Envoi de l'événement.
			ShortcutEvent *event = new ShortcutEvent(EVT_SHORTCUT, shortcutKey);
			wxQueueEvent(_owner, event);
		}
		else if(_event.type == ClientMessage)
		{
			char charKey[2] = {'\0', '\0'};
			KeyCode key;
			switch(_communicationThread)
			{
				//Enregistre le raccourci.
				case CUMMUNICATION_THREAD_REGISTER:
					charKey[0]=_shortcutKeyCommunicationThread->getCharKey();
					key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
					XGrabKey(_display, key, (unsigned int)_shortcutKeyCommunicationThread->getModifiers(), _root, True, GrabModeAsync, GrabModeAsync);
				break;
				
				//Désenregistrer le raccourci.
				case CUMMUNICATION_THREAD_UNREGISTER:
					charKey[0]=_shortcutKeyCommunicationThread->getCharKey();
					key = XKeysymToKeycode(_display, XStringToKeysym(charKey));
					XUngrabKey(_display, key, (unsigned int)_shortcutKeyCommunicationThread->getModifiers(), _root);
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
			ShortcutEvent *event = new ShortcutEvent(EVT_SHORTCUT, _shortcutKeys[(int)_msgEvent.wParam];);
			wxQueueEvent(_owner, event);
		}
		else if(_msgEvent.message == WM_APP)
		{
			char charKey[2] = {'\0', '\0'};
			wxString charKeyCapital;
			switch(_communicationThread)
			{
				//Enregistre le raccourci.
				case CUMMUNICATION_THREAD_REGISTER:
					charKey[0]=_shortcutKeyCommunicationThread->getCharKey();
					
					//Capitalise le charKey
					charKeyCapital = charKey;
					charKeyCapital.MakeCapitalized();
					
					for(unsigned int i = 0; i < _shortcutKeys.size(); i++)
					{
						if(_shortcutKeys[i] == *_shortcutKeyCommunicationThread)
						{
							RegisterHotKey(nullptr, i, (UINT)_shortcutKeyCommunicationThread->getModifiers(), *charKeyCapital.fn_str());
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

void Shortcut::creat(KeyModifier_e modifiers, char charKey)
{
    creat(ShortcutKey(modifiers, charKey));
}

void Shortcut::creat(ShortcutKey const& shortcutKey)
{   
    //Mémorise le raccourcie.
    _shortcutKeys.push_back(shortcutKey);
    
    //Si les raccourcis sont activés, on active le raccourci au prés du thread.
    if(_enable)
		_thread->registerShortcut(shortcutKey);
}

void Shortcut::remove(KeyModifier_e modifiers, char charKey)
{
	remove(ShortcutKey(modifiers, charKey));
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
