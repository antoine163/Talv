//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 0.3
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2012 - Antoine Maleyrie.
*/

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <wx/app.h>
#include <map>

#if defined(__UNIX__)
#include <X11/Xlib.h>
#elif defined(__WXMSW__)
#include <windows.h>
#endif

//! \brief Les modificateurs de touche.
enum KeyModifier
{
	#if defined(__DOXYGEN__)
	ALT,		//!< Touche Alt
	CONTROL,	//!< Touche Ctrl
	ALTGR,		//!< Touche Alt Gr (Pas definie sou windows)
	SHIFT,		//!< Touche Shift
	WIN			//!< Touche Win
	#elif defined(__UNIX__)
	ALT 	= Mod1Mask,
	CONTROL = ControlMask,
	ALTGR 	= Mod5Mask,
	SHIFT 	= ShiftMask,
	WIN 	= Mod4Mask
	#elif defined(__WXMSW__)
	ALT 	= MOD_ALT,
	CONTROL = MOD_CONTROL,
	SHIFT 	= MOD_SHIFT,
	WIN 	= MOD_WIN
	#endif
};

//! \brief représente un raccourci clavier.
class ShortcutKey
{
	public:
		//! \brief Constructeur.
		//! \param modifiers peut être combiner avec tout les valeur de \ref KeyModifier ex:(KeyModifier)(KeyModifier::WIN|KeyModifier::CONTROL)
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
		//! \param modifiers peut être combiner avec tout les valeur de \ref KeyModifier ex:(KeyModifier)(KeyModifier::WIN|KeyModifier::CONTROL)
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


//! \brief Permet de générais des événements à partir de raccourcies globaux.
//!
//! Voici un exemple d'utilisation. La classe App hérite de la class wxApp.
//! \code
//! bool App::OnInit()
//! {
//! 	//Création d'un objet Shortcut.
//! 	_shortcut = new Shortcut(this);	
//! 	
//! 	//Création d'un raccourci, touche win+a 
//! 	int id = _shortcut->creat(KeyModifier::WIN, 'a');
//! 	//lie lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//! 	
//! 	//Création d'un raccourci, touche win+b
//! 	id = _shortcut->creat(KeyModifier::WIN, 'b');
//! 	//lie lie l'événement à la méthode de callBack.
//! 	Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
//! 	
//! 	//Création d'un raccourci, touche win+Ctrl+a 
//! 	id = _shortcut->creat((KeyModifier)(KeyModifier::WIN|KeyModifier::CONTROL), 'a');
//! 	//lie lie l'événement à la méthode de callBack.
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
		Shortcut(wxApp *owner);
		
		//! \brief Destructeur.
		~Shortcut();
		
		//! \brief Créé un nouveau raccourci.
		//! \code
		//! //Création d'un raccourci, touche win+Ctrl+a 
		//! 	id = _shortcut->creat((KeyModifier)(KeyModifier::WIN|KeyModifier::CONTROL), 'a');
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
		//! \param vale true pour activer et false pour désactiver.
		void enable(bool vale);
		
	protected:
		//! \brief Méthode traitent les événement lier au raccourci 
		void OnIdle(wxIdleEvent& event);

		//! \brief enregistre le raccourci clavier auprès du système.
		//! \param shortcutKey Le raccourci.
		void registerShortcut(ShortcutKey const& shortcutKey);
		
		//! \brief supprime le raccourci clavier auprès du système.
		//! \param shortcutKey Le raccourci.
		void unRegisterShortcut(ShortcutKey const& shortcutKey);
		
	private:
		//! \brief utiliser pour générer les événements.
		wxEvtHandler *_owner; 
		
		//! \brief Table de lien entre les raccourci est les id.
		std::map<ShortcutKey, int> _bind;
		
		//! \brief Raccourci activer ou pas.
		//! \see creat()
		bool _enable;

		
		#if defined(__UNIX__)
		Display *_display;
		Window _root;
		XEvent _event;
		#elif defined(__WXMSW__)
		MSG _msgEvent;
		#endif
};

#endif //SHORTCUT_H
