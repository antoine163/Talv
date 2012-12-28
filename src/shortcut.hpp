//! \file **********************************************************************
//! - Compilateur : GCC
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
	ALT 	= Mod1Mask,
	CONTROL = ControlMask,
	ALTGR 	= Mod5Mask,
	SHIFT 	= ShiftMask,
	WIN 	= Mod4Mask
};

//! \brief Événement lier au raccourci clavier.
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
		
		//! \brief Obtenir la valeur ASCI.
		//! \return La valeur ASCI.
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

wxDECLARE_EVENT(EVT_SHORTCUT, ShortcutEvent);

class Shortcut : public wxThread
{
	public:
		Shortcut(wxEvtHandler *owner);
		~Shortcut();
		
		int creat(KeyModifier modifiers, char charKey);
		void remove(KeyModifier modifiers, char charKey);
		int getId(KeyModifier modifiers, char charKey);
		
	protected:
		wxThread::ExitCode Entry();

	private:
		wxEvtHandler *_owner;
		
		#if defined(__UNIX__)
		Display *_display;
		Window _root;
		XEvent _event;
		#endif
		
		std::map<long int, int> _bind;

};

#endif //SHORTCUT_H
