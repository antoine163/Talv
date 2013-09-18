//! \file **************************************************************
//! \brief Source notification.
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
	#else
	_positionScreenForNotify = POSITION_SCREEN_TOP_RIGHT;
	_displaySize = wxGetDisplaySize();
	_offsetPositionYFinalForNotify = 0;
	
	_offsetPositionOriginForNotify.x = 0;
	_offsetPositionOriginForNotify.y = 0;
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
		//Création de la fenêtre de notification.
		FrameNotification *newFrameNotify = new FrameNotification(title, message);
		
		//Récupère la tille de la nouvelle fenêtre.
		wxSize newNotifySize = newFrameNotify->GetSize();
		
		//Variable pour la nouvelle position.
		wxPoint newNotifyPosition;
		
		//Position et tille de la dernière fenêtre.
		//Si il y en a pas, tous est a 0.
		wxPoint lastNotifyPosition;
		wxSize lastNotifySize;
		
		//Si il y a déjà d'autre notification présent.
		if(_framesNotify.size() != 0)
		{						
			//Récupération de la dernière notification.
			FrameNotification *lastFrameNotify = _framesNotify.back();
		
			//Récupère la position et la tille de la dernière fenêtre.
			lastNotifyPosition = lastFrameNotify->GetPosition();
			lastNotifySize = lastFrameNotify->GetSize();
			
			//Calcul de la position de la notification.
			switch(_positionScreenForNotify)
			{
				case POSITION_SCREEN_TOP_LEFT:
				newNotifyPosition.x = 	_offsetPositionOriginForNotify.x;
				newNotifyPosition.y = 	lastNotifyPosition.y+
										lastNotifySize.y;
				break;
				
				case POSITION_SCREEN_TOP_RIGHT:
				newNotifyPosition.x = 	_displaySize.x-2-
										_offsetPositionOriginForNotify.x-
										newNotifySize.x;
				newNotifyPosition.y = 	lastNotifyPosition.y+
										lastNotifySize.y;
				break;
				
				case POSITION_SCREEN_BOTTOM_LEFT:
				newNotifyPosition.x = 	_offsetPositionOriginForNotify.x;
				newNotifyPosition.y = 	lastNotifyPosition.y-
										newNotifySize.y;
				break;
				
				case POSITION_SCREEN_BOTTOM_RIGHT:
				newNotifyPosition.x = 	_displaySize.x-2-
										_offsetPositionOriginForNotify.x-
										newNotifySize.x;
				newNotifyPosition.y = 	lastNotifyPosition.y-
										newNotifySize.y;
				break;
			}
			
			//Affecte la positionne calculé à la nouvelle notification.
			newFrameNotify->SetPosition(newNotifyPosition);
		}
		//Pas de notification présente.
		else
		{
			//Calcul de la position de la notification.
			switch(_positionScreenForNotify)
			{
				case POSITION_SCREEN_TOP_LEFT:
				newNotifyPosition.x = 	_offsetPositionOriginForNotify.x;
				newNotifyPosition.y = 	_offsetPositionOriginForNotify.y;
				break;
				
				case POSITION_SCREEN_TOP_RIGHT:
				newNotifyPosition.x = 	_displaySize.x-2-
										_offsetPositionOriginForNotify.x-
										newNotifySize.x;
				newNotifyPosition.y = 	_offsetPositionOriginForNotify.y;
				break;
				
				case POSITION_SCREEN_BOTTOM_LEFT:
				newNotifyPosition.x = 	_offsetPositionOriginForNotify.x;
				newNotifyPosition.y = 	_displaySize.y-2-
										_offsetPositionOriginForNotify.y-
										newNotifySize.y;
				break;
				
				case POSITION_SCREEN_BOTTOM_RIGHT:
				newNotifyPosition.x = 	_displaySize.x-2-
										_offsetPositionOriginForNotify.x-
										newNotifySize.x;
				newNotifyPosition.y = 	_displaySize.y-2-
										_offsetPositionOriginForNotify.y-
										newNotifySize.y;
				break;
			}
			
			//Affecte la positionne calculé à la nouvelle notification.
			newFrameNotify->SetPosition(newNotifyPosition); 
		}

		//Ajout de la notification à la pile.
		_framesNotify.push_back(newFrameNotify);
		//Lier l'évènement de fermeture de la notification
		newFrameNotify->Bind(EVT_EXIT_FRAME_NOTIFICATION, &Notification::OnExitFrameNotification, this);
		//Enfin, affiche la notification.
		newFrameNotify->show(timeout);
		
		//Si cette nouvelle notification est la seule on quitte la méthode.
		if(_framesNotify.size() <= 1)
			return;
		
		//Vérifie si la notification dépasse de l'écran.
		switch(_positionScreenForNotify)
		{
			case POSITION_SCREEN_TOP_LEFT:
			case POSITION_SCREEN_TOP_RIGHT:
			{
				//Calcul de la postions finale de la nouvelle notification.										
				int posYFinal = newNotifyPosition.y+newNotifySize.y;
				//Calcul de la position limite.
				int posYLimit = _displaySize.y-_offsetPositionYFinalForNotify;
								
				//On supprime des notifications pour que la nouvelle rentre dans l'écran.
				while(	posYFinal > posYLimit &&
						_framesNotify[0] != newFrameNotify)
				{
					//Suppression de la plus vielle notification.
					ExitFrameNotification(_framesNotify[0]);
					
					wxSize size = _framesNotify[0]->GetSize();
					posYFinal -= size.y;
				}
			}break;
			
			case POSITION_SCREEN_BOTTOM_LEFT:
			case POSITION_SCREEN_BOTTOM_RIGHT:
			{
				//Calcul de la postions finale de la nouvelle notification.										
				int posYFinal = newNotifyPosition.y;
				//Calcul de la position limite.
				int posYLimit = _offsetPositionYFinalForNotify;
								
				//On supprime des notifications pour que la nouvelle rentre dans l'écran.
				while(	posYFinal < posYLimit &&
						_framesNotify[0] != newFrameNotify)
				{
					//Suppression de la plus vielle notification.
					ExitFrameNotification(_framesNotify[0]);
					
					wxSize size = _framesNotify[0]->GetSize();
					posYFinal += size.y;
				}
			}break;
		}
	#endif
}

#ifdef USE_EMULATE_NOTIFICATION

void Notification::OnExitFrameNotification(wxCommandEvent& event)
{
	//Obtenir la (frame) notification qui a provoquer l'événement.
	FrameNotification* frameNotify = static_cast<FrameNotification*>(event.GetEventObject());
	
	//Ferme la notification.
	ExitFrameNotification(frameNotify);
}

void Notification::ExitFrameNotification(FrameNotification* frameNotify)
{
	//Délier l'évènement de la notification.
	frameNotify->Unbind(EVT_EXIT_FRAME_NOTIFICATION, &Notification::OnExitFrameNotification, this);

	int iFrameNotify = -1;
	
	//Récupération de la tiller de la notification.
	wxSize frameNotifySize = frameNotify->GetSize();
	
	//Parcoure tout les notification actifs
	for(unsigned int i = 0; i<_framesNotify.size(); i++)
	{
		//Si la notification a été trouver.
		if(iFrameNotify != -1)
		{
			//On décale les notifications qui se trouve après.
			wxPoint pos = _framesNotify[i]->GetPosition();
			
			//Calcul de la nouvelle position.
			switch(_positionScreenForNotify)
			{
				case POSITION_SCREEN_TOP_LEFT:
				case POSITION_SCREEN_TOP_RIGHT:
				pos.y -= frameNotifySize.y;
				break;
				
				case POSITION_SCREEN_BOTTOM_LEFT:
				case POSITION_SCREEN_BOTTOM_RIGHT:
				pos.y += frameNotifySize.y;
				break;
			}
			
			//Applique la nouvelle position.
			_framesNotify[i]->SetPosition(pos);
		}
		//c'est la notification que l'on cherche ?
		else if(_framesNotify[i] == frameNotify)
		{
			//On retiens sont index dans le vector
			iFrameNotify = i;
		}
	}
	
	//On détruis la notification
	_framesNotify[iFrameNotify]->Destroy();
	delete _framesNotify[iFrameNotify];
	//Et on l'enlève du vector
	_framesNotify.erase(_framesNotify.begin()+iFrameNotify);
}

#endif
