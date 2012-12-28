//! \file **********************************************************************
//! Gestion des raccourcis globaux.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Maleyrie Antoine
//! \version 0.1
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2011 - Antoine Maleyrie.
*/

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <wx/thread.h>
#include <wx/event.h>
#include <map>

#if defined(__UNIX__)
#include <X11/Xlib.h>
#endif

//! \brief Les modificateurs de touche.
enum KeyModifier
{
	#if defined(__DOXYGEN__)
	ALT,		//!< Touche Alt
	CONTROL,	//!< Touche Ctrl
	ALTGR,		//!< Touche Alt Gr
	SHIFT,		//!< Touche Shift
	WIN			//!< Touche Win
	#elif defined(__UNIX__)
	ALT 	= Mod1Mask,
	CONTROL = ControlMask,
	ALTGR 	= Mod5Mask,
	SHIFT 	= ShiftMask,
	WIN 	= Mod4Mask
	#endif
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
		
		//! \brief Clone.
		//! \return une nouvelle instance.
		virtual wxEvent* Clone()const;
		
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

//! \brief Déclaration de l'événement EVT_SHORTCUT.
wxDECLARE_EVENT(EVT_SHORTCUT, ShortcutEvent);


//! \brief Permet de générais des événements à partir de raccourcies globaux.
//!
//! Voici un exemple d'utilisation. La classe App hérite de la class wxApp.
//! \code
//! bool App::OnInit()
//! {
//! 	//Création et lancement du thread.
//! 	_shortcut = new Shortcut(this);	
//! 	_shortcut->Create();
//! 	_shortcut->Run();
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

class Shortcut : public wxThread
{
	public:
		//! \brief Constructeur.
		//! \param owner est un wxEvtHandler qui est utiliser pour générer les événements.
		Shortcut(wxEvtHandler *owner);
		
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
		
		//! \brief Supprimer un raccourci.
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier.
		//! \param charKey la touche (un caractère ASCII) du raccourci.
		void remove(KeyModifier modifiers, char charKey);
		
		//! \brief Obtenir l'id d'un raccourci.
		//! \param modifiers Le modificateur lier au raccourci, peut être une combinaison de \ref KeyModifier.
		//! \param charKey la touche (un caractère ASCII) du raccourci.
		//! \return id
		int getId(KeyModifier modifiers, char charKey);
		
	protected:
		//! \brief Surcharge, code du thread.
		wxThread::ExitCode Entry();

	private:
	
		//! \brief utiliser pour générer les événements.
		wxEvtHandler *_owner; 
		
		//! \brief Table de lien entre les modifiers le charKey est l'id du raccourci.
		//! 
		//! - Le premier chant (long int) est consacrée aux modifiers et au charKey.
		//! La représentation mémoire peut ce faire comme suit (sur un système 64 bit par exemple) :\n
		//! <table> 
		//! <tr> <td>8bit</td><td>3*8bit</td><td>4*8bit</td> </tr> 
		//! <tr> <td>charKey</td><td>3*8bit</td><td>modifiers</td> </tr> 
		//! </table>
		//!
		//! - Le deuxième chant est l'id du raccourci.
		//!
		//! - Exemple pour ajouter une élément:
		//! \code
		//! //création d'un nouveau id
		//! int id = wxNewId();
		//! 
		//! //Création d'un lien et ajout de l'id
		//! _bind[((long int)charKey<<(sizeof(long int)*7))|(long int)modifiers] = id;
		//! \endcode		
		std::map<long int, int> _bind;

		
		#if defined(__UNIX__)
		Display *_display;
		Window _root;
		XEvent _event;
		#endif
};

#endif //SHORTCUT_H
