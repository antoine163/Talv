//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 1.0.0
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2012 - Antoine Maleyrie.
*/

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <wx/app.h>
#include <wx/thread.h>

#include <map>

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

//! \brief Les modificateurs de touche.
enum KeyModifier
{
	#if defined(__DOXYGEN__)
	CONTROL,	//!< Touche Ctrl, (version string : "ctrl").
	ALT,		//!< Touche Alt, (version string : "alt").
	ALTGR,		//!< Touche Alt Gr, (version string : "altgr"). \note Pas definie sou windows.
	SHIFT,		//!< Touche Shift, (version string : "shift").
	SUPER		//!< Touche Super(Win), (version string : "super").
	#elif defined(__UNIX__)
	CONTROL = ControlMask,
	ALT 	= Mod1Mask,
	ALTGR 	= Mod5Mask,
	SHIFT 	= ShiftMask,
	SUPER 	= Mod4Mask,
	#elif defined(__WXMSW__)
	CONTROL = MOD_CONTROL,
	ALT 	= MOD_ALT,
	SHIFT 	= MOD_SHIFT,
	SUPER 	= MOD_WIN,
	#endif
	#if !defined(__DOXYGEN__)
	//Valeur utile pour ShortcutKey::shortcutKeyToString() et ShortcutKey::stringToShortcutKey()
	//Ne devrai pas être utiliser autre par !
	NONE 	= 0 
	#endif
};

//! \brief représente un raccourci clavier.
class ShortcutKey
{
	public:
		//! \brief Constructeur.
		//! \param modifiers peut être combiner avec tout les valeur de \ref KeyModifier ex:(KeyModifier)(KeyModifier::SUPER|KeyModifier::CONTROL)
		//! \param charKey le caractère, c'est une valeur ASCII.
		ShortcutKey(KeyModifier modifiers, char charKey);
		
		bool operator<(ShortcutKey const& ins)const;
		bool operator==(ShortcutKey const& ins)const;
		bool operator!=(ShortcutKey const& ins)const;
		
		//! \brief Obtenir la valeur ASCII.
		//! \return La valeur ASCII.
		char getCharKey()const;
		
		//! \brief Obtenir le modificateur.
		//! \return C'est une valeur combiner de \ref KeyModifier.
		KeyModifier getModifiers()const;
		
		//! \brief Converti un \ref ShortcutKey en string.
		//! \param shortcut le raccourci en version \ref ShortcutKey.
		//! \return Le raccourci en version string.
		static wxString shortcutKeyToString(ShortcutKey const& shortcut);
		
		//! \brief Converti un raccourci, de sa version string en \ref ShortcutKey.
		//! Cette méthode ne vérifie pas la valider du raccourci, il devra être de la forme (ex:"alt+shift+f").
		//! \param shortcut le raccourci en version string.
		//! \return Le raccourci en version \ref ShortcutKey.
		static ShortcutKey stringToShortcutKey(wxString const& shortcut);
		
	private:
		//! \brief Le modificateur.
		KeyModifier _modifiers;
		//! \brief La valeur ASCII.
		char _charKey;
};

//! \brief Événement lier au raccourci clavier.
//! \see Shortcut
class ShortcutEvent: public wxEvent
{
	public:
		//! \brief Constructeur.
		//! \param id l'identifiant de l'objet.
		//! \param eventType le type de l'événement. Si vous en crée pas de nouveau, \a EVT_SHORTCUT devait être passer.
		//! \param modifiers peut être combiner avec tout les valeur de \ref KeyModifier ex:(KeyModifier)(KeyModifier::SUPER|KeyModifier::CONTROL)
		//! \param charKey le caractère, c'est une valeur ASCII.
		ShortcutEvent(int id, wxEventType eventType, KeyModifier modifiers, char charKey);
		
		//! \brief Constructeur.
		//! \param id l'identifiant de l'objet.
		//! \param eventType le type de l'événement. Si vous en crée pas de nouveau, \a EVT_SHORTCUT devait être passer.
		//! \param shortcutKey le raccourci.
		ShortcutEvent(int id, wxEventType eventType, ShortcutKey const& shortcutKey);
		
		//! \brief Clone.
		//! \return une nouvelle instance.
		virtual wxEvent* Clone()const;
		
		//! \brief Obtenir la valeur ASCII.
		//! \return La valeur ASCII.
		char getCharKey()const;
		
		//! \brief Obtenir le modificateur.
		//! \return C'est une valeur combiner de \ref KeyModifier.
		KeyModifier getModifiers()const;
		
		//! \brief Obtenir le raccourci.
		//! \return Le raccourci.
		ShortcutKey const& getShortcutKey()const;
		
	private:
		//! \brief Le raccourci.
		ShortcutKey _shortcutKey;
};

//! \brief Déclaration de l'événement EVT_SHORTCUT.
wxDECLARE_EVENT(EVT_SHORTCUT, ShortcutEvent);

class ShortcutThread : public wxThread
{
	public:
		//! \brief Constructeur.
		//! \param owner est un wxEvtHandler qui est utiliser pour générer les événements.
		ShortcutThread(wxEvtHandler *owner, std::map<ShortcutKey, int> & bind);
		
		//! \brief Destructeur.
		~ShortcutThread();
		
		//! \brief Active un raccourci.
		//! \param shortcutKey est le raccourci à activer.
		void registerShortcut(ShortcutKey const& shortcutKey);
		
		//! \brief Désactive un raccourci.
		//! \param shortcutKey est le raccourci à Désactive.
		void unregisterShortcut(ShortcutKey const& shortcutKey);
		
		//! \brief Désactive tout les raccourcis.
		void unregisterAllShortcut();
		
	protected:
		wxThread::ExitCode Entry();
		void halt();
    
	private:
		//! \brief utiliser pour générer les événements.
		wxEvtHandler *_owner; 
		
		//! \brief Table de lien entre les raccourci est les id.
		std::map<ShortcutKey, int>& _bind;
		
		//! \brief Mutex pour protéger les variable de communication avec le thread.
		volatile bool _mutexCommunicationThread;
		
		//! \brief Comunique le ShortcutKey au thread.
		ShortcutKey const* _shortcutKeyCommunicationThread;
		enum CommunicationThread
		{
			REGISTER,
			UNREGISTER,
			QUIT,
			NONE
		};
		//! \brief Action a communiquer au thread.
		volatile CommunicationThread _communicationThread;
		
		
		#if defined(__UNIX__)
		Display *_display;
		Window _root;
		Window _interCommunication;
		XEvent _event;
		#elif defined(__WXMSW__)
		MSG _msgEvent;
		#endif
};

//! \brief Permet de générais des événements à partir de raccourcies globaux.
//!
//! Voici un exemple d'utilisation. La classe App hérite de la class wxApp.
//! \code
//! bool App::OnInit()
//! {
//! 	//Création d'un objet Shortcut.
//! 	_shortcut = new Shortcut(this);	
//! 	
//! 	//Création d'un raccourci, touche super+a 
//! 	int id = _shortcut->creat(KeyModifier::SUPER, 'a');
//! 	//lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//! 	
//! 	//Création d'un raccourci, touche super+b
//! 	id = _shortcut->creat(KeyModifier::SUPER, 'b');
//! 	//lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//!
//! 	//Création d'un raccourci, touche shift+super+a
//! 	ShortcutKey shortcutKey(ShortcutKey::stringToShortcutKey("shift+super+a"));
//! 	id = _shortcut->creat(shortcutKey);
//! 	//lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//! 	
//! 	//Création d'un raccourci, touche super+ctrl+a 
//! 	id = _shortcut->creat((KeyModifier)(KeyModifier::SUPER|KeyModifier::CONTROL), 'a');
//! 	//lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//! 
//! 	return true;
//! }
//! 
//! void App::OnShortcut(ShortcutEvent& event)
//! {
//! 	std::cout << "OnShortcut -> " << event.GetId() << " : ";
//! 						std::cout << event.getCharKey() << " : ";
//! 						std::cout << event.getModifiers() << std::endl;		
//! }
//! \endcode
class Shortcut
{
	public:
		//! \brief Constructeur.
		//! \param owner est un wxEvtHandler qui est utiliser pour générer les événements.
		Shortcut(wxEvtHandler *owner);
		
		//! \brief Destructeur.
		~Shortcut();
		
		//! \brief Créé un nouveau raccourci.
		//! \code
		//! //Création d'un raccourci, touche super+Ctrl+a 
		//! 	id = _shortcut->creat((KeyModifier)(KeyModifier::SUPER|KeyModifier::CONTROL), 'a');
		//! \endcode
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier.
		//! \param charKey la touche (un caractère ASCII) du racourci.
		//! \return un nouveau id lier au raccourci. L'id est générer avec wxNewId().
		int creat(KeyModifier modifiers, char charKey);
		
		//! \brief Créé un nouveau raccourci.
		//! \param shortcutKey Le raccourci.
		//! \return un nouveau id lier au raccourci. L'id est générer avec wxNewId().
		int creat(ShortcutKey const& shortcutKey);
		
		//! \brief Supprimer un raccourci.
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier.
		//! \param charKey la touche (un caractère ASCII) du raccourci.
		void remove(KeyModifier modifiers, char charKey);
		
		//! \brief Supprimer un raccourci.
		//! \param shortcutKey Le raccourci a supprimer
		void remove(ShortcutKey const& shortcutKey);
		
		//! \brief Supprimer touts les raccourcis.
		void removeAll();
		
		//! \brief Obtenir l'id d'un raccourci.
		//! \param shortcutKey Le raccourci.
		//! \return id
		int getId(ShortcutKey const& shortcutKey);
		
		//! \brief Active ou désactive les raccourcis.
		//! \param val true pour activer et false pour désactiver.
		void enable(bool val = true);
		
	private:
		//! \brief Table de lien entre les raccourci est les id.
		std::map<ShortcutKey, int> _bind;
		
		ShortcutThread* _thread;
		
		//! \brief utiliser pour générer les événements.
		wxEvtHandler *_owner;
		
		//! \brief Raccourci activer ou pas.
		//! \see enable()
		bool _enable;
};

#endif //SHORTCUT_H
