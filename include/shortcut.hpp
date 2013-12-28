//! \file **********************************************************************
//! \brief Header Gestion des raccourcis globaux.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie.
//! \version 1.5
//! \date 13.12.12
//!
//! ****************************************************************************

#ifndef SHORTCUT_H
#define SHORTCUT_H

//WxWidgets
#include <wx/app.h>
#include <wx/thread.h>

//Stl
#include <vector>

#if defined(__UNIX__)
#include <X11/Xlib.h>
#elif defined(__WXMSW__)
#include <windows.h>
#endif

#if defined(__UNIX__)
#define NB_KEY_MODIFIER 5
#elif defined(__WXMSW__)
#define NB_KEY_MODIFIER 4
#endif

// *****************************************************************************
// Enum KeyModifier_e
// *****************************************************************************

//! \brief Les modificateurs de touche.
enum KeyModifier_e
{
	#if defined(__DOXYGEN__)
	KEY_MODIFIER_CONTROL,	//!< Touche Ctrl, (version string : "ctrl").
	KEY_MODIFIER_ALT,		//!< Touche Alt, (version string : "alt").
	KEY_MODIFIER_ALTGR,		//!< Touche Alt Gr, (version string : "altgr"). \note Seulement sous unix.
	KEY_MODIFIER_SHIFT,		//!< Touche Shift, (version string : "shift").
	KEY_MODIFIER_SUPER,		//!< Touche Super(Win), (version string : "super").
	KEY_MODIFIER_NONE  		//!< Le raccourci est probablement no valide.
	#elif defined(__UNIX__)
	KEY_MODIFIER_CONTROL = ControlMask,
	KEY_MODIFIER_ALT 	= Mod1Mask,
	KEY_MODIFIER_ALTGR 	= Mod5Mask,
	KEY_MODIFIER_SHIFT 	= ShiftMask,
	KEY_MODIFIER_SUPER 	= Mod4Mask,
	KEY_MODIFIER_NONE 	= 0 
	#elif defined(__WXMSW__)
	KEY_MODIFIER_CONTROL = MOD_CONTROL,
	KEY_MODIFIER_ALT 	= MOD_ALT,
	KEY_MODIFIER_SHIFT 	= MOD_SHIFT,
	KEY_MODIFIER_SUPER 	= MOD_WIN,
	KEY_MODIFIER_NONE 	= 0 
	#endif
};

inline KeyModifier_e operator|(KeyModifier_e val1, KeyModifier_e val2)
{
	unsigned int val = (unsigned int)val1|(unsigned int)val2;
	return static_cast<KeyModifier_e>(val);
}

// *****************************************************************************
// Class ShortcutKey
// *****************************************************************************

//! \brief Représente un raccourci clavier constituer d'un modificateur et d'une touche.
class ShortcutKey
{
	public:
		//! \brief Constructeur.
		//! Ce Constructeur ne construis pas un raccourcis valide. \ref isOk() renverra false.
		ShortcutKey();
		
		//! \brief Constructeur.
		//! \param modifiers peut être combiner avec tout les valeurs de \ref KeyModifier_e ex:KEY_MODIFIER_SUPER|KEY_MODIFIER_CONTROL)
		//! \param charKey le caractère, c'est une valeur ASCII.
		ShortcutKey(KeyModifier_e modifiers, char charKey);
		
		bool operator<(ShortcutKey const& ins)const;
		bool operator==(ShortcutKey const& ins)const;
		bool operator!=(ShortcutKey const& ins)const;
		
		//! \brief Obtenir la valeur ASCII.
		//! \return La valeur ASCII.
		char getCharKey()const;
		
		//! \brief Obtenir le modificateur.
		//! \return C'est une valeur combiner de \ref KeyModifier_e.
		KeyModifier_e getModifiers()const;
		
		//! \brief Vérifie la validité du raccourcie.
		bool isOk()const;
		
		//! \brief Converti un \ref ShortcutKey en string.
		//! \param shortcut le raccourci en version \ref ShortcutKey.
		//! \return Le raccourci en version string.
		static wxString shortcutKeyToString(ShortcutKey const& shortcut);
		
		//! \brief Converti un raccourci, de sa version string en \ref ShortcutKey.
		//!
		//! Le raccourci doit être de la forme modificateur+caractère (ex:"alt+shift+f").
		//! \param shortcut le raccourci en version string.
		//! \return Le raccourci en version \ref ShortcutKey. Vous pouver verifier la validiter du racoursen
		//! en appeler \ref getCharKey() et \ref getModifiers(). Si  getCharKey() retourne '\n' ou/et si \ref getModifiers() retourne \b KEY_MODIFIER_NONE
		//! votre raccourcis n'est pas valide. Sinon vous pouver appeler \ref isOk() qui fais sa pour vous.
		//! \see KeyModifier_e
		static ShortcutKey stringToShortcutKey(wxString const& shortcut);
		
	private:
		//! \brief Le modificateur.
		KeyModifier_e _modifiers;
		//! \brief La valeur ASCII.
		char _charKey;
};

// *****************************************************************************
// Class ShortcutEvent
// *****************************************************************************

//! \brief Événement lier au raccourci clavier.
//! \see Shortcut
class ShortcutEvent: public wxEvent
{
	public:
		//! \brief Constructeur.
		//! \param eventType le type de l'événement. Si vous en crée pas de nouveau, \a EVT_SHORTCUT devait être passer.
		//! \param modifiers peut être combiner avec tout les valeurs de \ref KeyModifier_e ex:KEY_MODIFIER_UPER|KEY_MODIFIER_CONTROL)
		//! \param charKey le caractère, c'est une valeur ASCII.
		ShortcutEvent(wxEventType eventType, KeyModifier_e modifiers, char charKey);
		
		//! \brief Constructeur.
		//! \param eventType le type de l'événement. Si vous en crée pas de nouveau, \a EVT_SHORTCUT devait être passer.
		//! \param shortcutKey le raccourci.
		ShortcutEvent(wxEventType eventType, ShortcutKey const& shortcutKey);
		
		//! \brief Clone.
		//! \return une nouvelle instance.
		virtual wxEvent* Clone()const;
		
		//! \brief Obtenir la valeur ASCII.
		//! \return La valeur ASCII.
		char getCharKey()const;
		
		//! \brief Obtenir le modificateur.
		//! \return C'est une valeur combiner de \ref KeyModifier_e.
		KeyModifier_e getModifiers()const;
		
		//! \brief Obtenir le raccourci.
		//! \return Le raccourci.
		ShortcutKey const& getShortcutKey()const;
		
	private:
		//! \brief Le raccourci.
		ShortcutKey _shortcutKey;
};

//! \brief Déclaration de l'événement EVT_SHORTCUT.
wxDECLARE_EVENT(EVT_SHORTCUT, ShortcutEvent);

// *****************************************************************************
// Class ShortcutThread
// *****************************************************************************

//! \brief C'est le thread qui installe/désinstalle les raccourcis au-prés
//! de l'os et qui lève un événement de type \ref ShortcutEvent lorsque
//! qu'un raccourci est détecter presser sur le clavier.
//!
//! \note Avant de supprimer une instances de cette classe assurez vous de bien
//! avoir unregister touts les raccourcis avec \ref unregisterShortcut().
class ShortcutThread : protected wxThread
{
	public:
		#ifdef __WXMSW__
		ShortcutThread(wxEvtHandler *owner, std::vector<ShortcutKey>const& shortcutKeys);
		#else
		//! \brief Constructeur.
		//! \param owner est un wxEvtHandler qui est utiliser pour générer les événements.
		ShortcutThread(wxEvtHandler *owner);
		#endif
		
		//! \brief Destructeur.
		~ShortcutThread();
		
		//! \brief Active un raccourci.
		//! \param shortcutKey est le raccourci à activer.
		void registerShortcut(ShortcutKey const& shortcutKey);
		
		//! \brief Désactive un raccourci.
		//! \param shortcutKey est le raccourci à Désactive.
		void unregisterShortcut(ShortcutKey const& shortcutKey);
		
	protected:
		wxThread::ExitCode Entry();
		void halt();
    
	private:
		//! \brief Utiliser pour générer les événements.
		wxEvtHandler *_owner; 
		
		//! \brief Mutex pour protéger les variable de communication avec le thread.
		volatile bool _mutexCommunicationThread;
		
		//! \brief Comunique le ShortcutKey au thread.
		ShortcutKey const* _shortcutKeyCommunicationThread;
		enum CommunicationThread
		{
			CUMMUNICATION_THREAD_REGISTER,
			CUMMUNICATION_THREAD_UNREGISTER,
			CUMMUNICATION_THREAD_QUIT,
			CUMMUNICATION_THREAD_NONE
		};
		//! \brief Action à communiquer au thread.
		volatile CommunicationThread _communicationThread;
		
		
		#if defined(__UNIX__)
		Display *_display;
		Window _root;
		Window _interCommunication;
		XEvent _event;
		#elif defined(__WXMSW__)
		MSG _msgEvent;
		std::vector<ShortcutKey>const& _shortcutKeys;
		#endif
};

// *****************************************************************************
// Class Shortcut
// *****************************************************************************

//! \brief Interface utilisateur pour les gestions des raccourci clavier globaux.
//!
//! Voici un exemple d'utilisation. Dans cette exemple la classe App hérite de
//! la class wxApp.
//! \code
//! bool App::OnInit()
//! {
//! 	//Création d'un objet Shortcut.
//! 	_shortcut = new Shortcut(this);	
//! 	
//! 	//Création d'un raccourci, touche super+a 
//! 	_shortcut->creat(KEY_MODIFIER_SUPER, 'a');
//! 	
//! 	//Création d'un raccourci, touche super+b
//! 	_shortcut->creat(KEY_MODIFIER_SUPER, 'b');
//!
//! 	//Création d'un raccourci, touche shift+super+a
//! 	ShortcutKey shortcutKey(ShortcutKey::stringToShortcutKey("shift+super+a"));
//! 	_shortcut->creat(shortcutKey);
//! 	
//! 	//Création d'un raccourci, touche super+ctrl+a 
//! 	_shortcut->creat(KEY_MODIFIER_SUPER|KEY_MODIFIER_CONTROL, 'a');
//! 
//! 	return true;
//! }
//! 
//! void App::OnShortcut(ShortcutEvent& event)
//! {
//! 	std::cout << "OnShortcut -> " << event.getCharKey() << " : ";
//! 						std::cout << event.getModifiers() << std::endl;		
//! }
//! \endcode
class Shortcut
{
	public:
		//! \brief Constructeur.
		//! \param owner est un wxEvtHandler qui est utiliser pour générer les événements.
		//! \note Par défaut les raccourcis sont activés. Il n'est donc pas nécessaire d'appeler la méthode \ref enable().
		Shortcut(wxEvtHandler* owner);
		
		//! \brief Destructeur.
		~Shortcut();
		
		//! \brief Créé un nouveau raccourci.
		//! \code
		//! //Création d'un raccourci, touche "super+ctrl+a" 
		//! 	id = _shortcut->creat(KEY_MODIFIER_SUPER|KEY_MODIFIER_CONTROL), 'a');
		//! \endcode
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier_e.
		//! \param charKey la touche (un caractère ASCII) du racourci.
		//! \return un nouveau id lier au raccourci. L'id est générer avec wxNewId().
		void creat(KeyModifier_e modifiers, char charKey);
		
		//! \brief Créé un nouveau raccourci.
		//! \param shortcutKey Le raccourci.
		//! \return un nouveau id lier au raccourci. L'id est générer avec wxNewId().
		void creat(ShortcutKey const& shortcutKey);
		
		//! \brief Supprimer un raccourci.
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier_e.
		//! \param charKey la touche (un caractère ASCII) du raccourci.
		void remove(KeyModifier_e modifiers, char charKey);
		
		//! \brief Supprimer un raccourci.
		//! \param shortcutKey Le raccourci à supprimer.
		void remove(ShortcutKey const& shortcutKey);
		
		//! \brief Supprimer touts les raccourcis.
		void removeAll();
		
		//! \brief Active ou désactive les raccourcis.
		//! Par défaut les raccourcis sont activés.
		//! \param val true pour activer et false pour désactiver.
		void enable(bool val = true);
		
		//! \brief Pour savoir si les raccourcis son activer ou pas.
		bool isEnable();
		
	private:
		//! \brief Les raccourcis qui on été crée.
		//! \see creat()
		std::vector<ShortcutKey> _shortcutKeys;
		
		ShortcutThread* _thread;
		
		//! \brief utiliser pour générer les événements.
		wxEvtHandler *_owner;
		
		//! \brief Raccourci activer ou pas.
		//! \see enable()
		bool _enable;
};

#endif //SHORTCUT_H
