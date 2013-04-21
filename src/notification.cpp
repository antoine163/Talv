//! \file **************************************************************
//! \brief Source notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
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
#endif

//TEST
#include <iostream>

// *********************************************************************
// Class FrameNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

DialogNotification::DialogNotification(	wxString const& title,
										wxString const& message)
: GuiDialogNotification(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFRAME_NO_TASKBAR|wxDIALOG_NO_PARENT|wxSTAY_ON_TOP|wxNO_BORDER)
{
	//Affiche le titre et le message.
	_staticTextTitle->SetLabelMarkup("<b>"+title+"</b>");
	_staticTextMessage->SetLabel(message);
	
	//Recalcule de la tille de la fenêtre.
	this->Layout();
	GetSizer()->Fit(this);
	
	//Pour ne pas redimensionner la fenêtre.
	this->SetSizeHints(GetSize(), GetSize());
}

DialogNotification::~DialogNotification()
{
}

void DialogNotification::show(int timeout)
{
	ShowWithoutActivating();
}

void DialogNotification::OnClose(wxCloseEvent&)
{
	//Qui la notification
	exit();
}

void DialogNotification::OnLeftDown(wxMouseEvent&)
{
	//Qui la notification
	exit();
}

void DialogNotification::exit()
{
	//Envoi de l'événement.
	wxCommandEvent event(EVT_EXIT_DIALG_NOTIFICATION, GetId());
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}

wxDEFINE_EVENT(EVT_EXIT_DIALG_NOTIFICATION, wxCommandEvent);

#endif

// *********************************************************************
// Class Notification
// *********************************************************************
//! \todo a instenser/supprimer dans main.cpp
Notification::Notification()
{
	#ifndef USE_EMULATE_NOTIFICATION
		//Sous unix on utilise la libnotify
		#if defined(__UNIX__)
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
		#if defined(__UNIX__)
			notify_uninit();
		#endif
	#endif
}

void Notification::notify(	wxString const& title,
							wxString const& message)
{
	//3s par défaut + 1s de plus tout les 10 caractères.
	int timeout = 3+message.Length()/10;
	
	#ifndef USE_EMULATE_NOTIFICATION
		#if define(__UNIX__)
			//Préparation de la notification.
			NotifyNotification * notify = notify_notification_new(title.mb_str(wxConvUTF8), message.fn_str(), "dialog-information");
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
		DialogNotification *dialog = new DialogNotification(title, message);
		
		if(_dialogs.size() != 0)
		{
			int positionY = 0;
			int sizeY = 0;
			DialogNotification *lastDialog = _dialogs.back();
		
			lastDialog->GetPosition(nullptr, &positionY);
			lastDialog->GetSize(nullptr, &sizeY);
			
			dialog->SetPosition(wxPoint(0, positionY+sizeY));
		}
		else
		{
			dialog->SetPosition(wxPoint(0, 0));
		}


		_dialogs.push_back(dialog);
		dialog->Bind(EVT_EXIT_DIALG_NOTIFICATION, &Notification::OnExitDialogNotification, this);
		dialog->show(timeout);
	#endif
}

#ifdef USE_EMULATE_NOTIFICATION

void Notification::OnExitDialogNotification(wxCommandEvent& event)
{
	DialogNotification* dialog = static_cast<DialogNotification*>(event.GetEventObject());
	
	int iDialog = -1;
	int sizeY = 0;
	
	//On sauvegarde le décalage que l'on doit affecter au dialogue qui doive être décaler.
	dialog->GetSize(nullptr, &sizeY);
	
	for(unsigned int i = 0; i<_dialogs.size(); i++)
	{
		//Si le dialogue a été trouver
		if(iDialog != -1)
		{
			//On décale les dialogue qui doive changer de position
			wxPoint pos = _dialogs[i]->GetPosition();
			pos.y -= sizeY;
			_dialogs[i]->SetPosition(pos);
		}
		//c'est le dialogue que l'on cherche ?
		else if(_dialogs[i] == dialog)
		{
			//On retiens sont index dans le vector
			iDialog = i;
		}
	}
	
	//Cette condition ne devrai jamais être fausse
	if(iDialog != -1)
	{
		//On détruis le dialogue
		_dialogs[iDialog]->Destroy();
		delete _dialogs[iDialog];
		//Et on l'enlève du vector
		_dialogs.erase(_dialogs.begin()+iDialog);
	}
}

#endif
