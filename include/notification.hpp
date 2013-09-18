//! \file **************************************************************
//! \brief Header notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.5
//! \date 12.04.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "singleton.hpp"
#include <wx/string.h>

#ifdef USE_EMULATE_NOTIFICATION
	#include "guiFrameNotification.h"
	#include <wx/frame.h>
	#include <wx/event.h>
	#include <wx/timer.h>
	#include <vector>
#endif


// *********************************************************************
// Class DialogNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

//! \brief Fenêtre de notification.
class FrameNotification : public GuiFrameNotification
{	
	public:
		//! \brief constructeur.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		FrameNotification(	wxString const& title,
							wxString const& message);
		//! \brief Destructeur.
		~FrameNotification();
		
		//! \brief Afficher la notification.
		//! \param timeout est le temps d'affichage de la notification en second.
		void show(int timeout);
		
		//! \brief Envois l'éventent pour indiquer que la notification
		//! veux être quitter.
		void exit();
	
	protected:
		//! \brief Appeler quand la fenêtre reçois l'ordre de fermeture.
		void OnClose(wxCloseEvent&);
		//! \brief Appeler l'ordre d'un clique gauche sur la fenêtre.
		void OnLeftDown(wxMouseEvent&);
		//! \brief Appeler a la fin du temps écouler par le timer.
		void OnTimeout(wxTimerEvent&);
	
	private:
		//! \brief Timer de la notification.
		wxTimer _timeout;

};

//! \brief Évènement produit par les notification pour être fermer.
wxDECLARE_EVENT(EVT_EXIT_FRAME_NOTIFICATION, wxCommandEvent);

#endif

// *********************************************************************
// Class Notification
// *********************************************************************

//! \brief Gestionnaire des notifications.
class Notification : public Singleton<Notification>
{	
	friend class Singleton<Notification>;
	
	public:
		//! \brief Pour générai une notification.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		void notify(wxString const& title,
					wxString const& message=wxEmptyString);
		
	#ifdef USE_EMULATE_NOTIFICATION
		//! \brief Fermeture des notifications.
		//!
		//! Cette méthode est appelée l'ors que une notification veux est fermer.
		//! Soi par un clique de l'utilisateur sur celle ci ou par la fin du timer.
		//! \param event est l'évènement que produit la notification.
		void OnExitFrameNotification(wxCommandEvent& event);
	#endif
	
	private:
		Notification();
		~Notification();
		
	#ifdef USE_EMULATE_NOTIFICATION
		//! \brief Toutes les notifications active.
		std::vector<FrameNotification*> _framesNotify;
	#endif
};

#endif //NOTIFICATION_H
