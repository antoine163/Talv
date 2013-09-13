//! \file **************************************************************
//! \brief Source notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 12.04.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "notification.hpp"
 
#include <wx/log.h>
#include <wx/intl.h> 

#ifndef USE_EMULATE_NOTIFICATION
	//Sous unix on utilise la libnotify
	#if defined(__UNIX__)
		#include <libnotify/notify.h>
	//Pour les autres os on utilise les notifications de wxWidgets
	#else
		#include <wx/notifmsg.h>
	#endif
#else
	#include <wx/gdicmn.h>
#endif

//TEST
#include <iostream>

// *********************************************************************
// Class FrameNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

FrameNotification::FrameNotification(	wxString const& title,
										wxString const& message)
: GuiFrameNotification(nullptr), _timeout(this) 
{
	//Affiche le titre et le message.
	_staticTextTitle->SetLabelMarkup("<b>"+title+"</b>");
	_staticTextMessage->SetLabel(message);
	
	//Recalcule de la tille de la fenêtre.
	this->Layout();
	GetSizer()->Fit(this);
	
	//Pour ne pas redimensionner la fenêtre.
	this->SetSizeHints(GetSize(), GetSize());
	
	//Bind du timer pour le timeout
	Bind(wxEVT_TIMER, &FrameNotification::OnTimeout, this);
}

FrameNotification::~FrameNotification()
{
	//Unbind du timer pour le timeout
	Unbind(wxEVT_TIMER, &FrameNotification::OnTimeout, this);
}

void FrameNotification::show(int timeout)
{
	ShowWithoutActivating();
	_timeout.Start(timeout*1000, wxTIMER_ONE_SHOT);
}

void FrameNotification::OnClose(wxCloseEvent&)
{
	//Qui la notification
	exit();
}

void FrameNotification::OnLeftDown(wxMouseEvent&)
{
	//Qui la notification
	exit();
}

void FrameNotification::OnTimeout(wxTimerEvent&)
{
	//Qui la notification
	exit();
}

void FrameNotification::exit()
{
	//Envoi de l'événement.
	wxCommandEvent event(EVT_EXIT_FRAME_NOTIFICATION, GetId());
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}

wxDEFINE_EVENT(EVT_EXIT_FRAME_NOTIFICATION, wxCommandEvent);

#endif

// *********************************************************************
// Class Notification
// *********************************************************************
//! \todo a instenser/supprimer dans main.cpp
Notification::Notification()
{
	#ifndef USE_EMULATE_NOTIFICATION
		//Sous unix on utilise la libnotify
		#ifdef __UNIX__
			if(!notify_init(PROJECT_NAME))
			{
				wxLogError(_("Libnotify could not be initialized."));
			}
		#endif
	#endif
}

Notification::~Notification()
{
	#ifndef USE_EMULATE_NOTIFICATION
		//Sous unix on utilise la libnotify
		#ifdef __UNIX__
			notify_uninit();
		#endif
	#else
		//On détruis les fenêtres de notification
		for(auto it : _framesNotify)
		{
			it->Destroy();
			delete it;
		}
	#endif
}

void Notification::notify(	wxString const& title,
							wxString const& message)
{
	//3s par défaut + 1s de plus tout les 10 caractères.
	int timeout = 3+message.Length()/10;
	
	#ifndef USE_EMULATE_NOTIFICATION
		#ifdef __UNIX__
			//Préparation de la notification.
			NotifyNotification * notify = notify_notification_new(title.mb_str(wxConvUTF8), message.fn_str(), nullptr);
			notify_notification_set_timeout(notify, timeout*1000);
			
			//Affichage de la notification
			if(!notify_notification_show(notify, nullptr))
			{
				//Si problème
				wxLogError(_("The notify could not be show."));
			}
		#else
			//Préparation de la notification.
			wxNotificationMessage notify(title, message);
			//Affichage de la notification
			notify.Show(timeout);
		#endif
	#else
		FrameNotification *frameNotify = new FrameNotification(title, message);
		
		if(_framesNotify.size() != 0)
		{			
			int positionY = 0;
			int sizeY = 0;
			FrameNotification *lastFrameNotify = _framesNotify.back();
		
			lastFrameNotify->GetPosition(nullptr, &positionY);
			lastFrameNotify->GetSize(nullptr, &sizeY);
			
			frameNotify->SetPosition(wxPoint(0, positionY+sizeY));
		}
		else
		{
			frameNotify->SetPosition(wxPoint(0, 0));
		}

		_framesNotify.push_back(frameNotify);
		frameNotify->Bind(EVT_EXIT_FRAME_NOTIFICATION, &Notification::OnExitFrameNotification, this);
		frameNotify->show(timeout);
		
		if(_framesNotify.size() != 0)
		{
			int positionY = 0;
			int sizeY = 0;
			int displayY = 0;
			
			wxDisplaySize(nullptr, &displayY);
			frameNotify->GetPosition(nullptr, &positionY);
			frameNotify->GetSize(nullptr, &sizeY);
			
			if(positionY+sizeY > displayY)
			{
				_framesNotify[0]->exit();
			}
		}
	#endif
}

#ifdef USE_EMULATE_NOTIFICATION

void Notification::OnExitFrameNotification(wxCommandEvent& event)
{
	//Obtenir la (frame) notification qui a provoquer l'événement.
	FrameNotification* frameNotify = static_cast<FrameNotification*>(event.GetEventObject());
	
	//Unbind la notification
	frameNotify->Unbind(EVT_EXIT_FRAME_NOTIFICATION, &Notification::OnExitFrameNotification, this);

	int iFrameNotify = -1;
	int sizeY = 0;
	
	//On sauvegarde le décalage que l'on doit affecter au notification qui doive être décaler.
	frameNotify->GetSize(nullptr, &sizeY);
	
	//Parcoure tout les notification actifs
	for(unsigned int i = 0; i<_framesNotify.size(); i++)
	{
		//Si un notification a été trouver
		if(iFrameNotify != -1)
		{
			//On décale les notifications qui doive changer de position
			wxPoint pos = _framesNotify[i]->GetPosition();
			pos.y -= sizeY;
			_framesNotify[i]->SetPosition(pos);
		}
		//c'est la notification que l'on cherche ?
		else if(_framesNotify[i] == frameNotify)
		{
			//On retiens sont index dans le vector
			iFrameNotify = i;
		}
	}
	
	//On détruis la (frame) notification
	_framesNotify[iFrameNotify]->Destroy();
	delete _framesNotify[iFrameNotify];
	//Et on l'enlève du vector
	_framesNotify.erase(_framesNotify.begin()+iFrameNotify);
}

#endif
