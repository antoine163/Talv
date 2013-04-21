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

// *********************************************************************
// Class FrameNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

FrameNotification::FrameNotification(	wxString const& title,
										wxString const& message)
: GuiDialogNotification(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFRAME_NO_TASKBAR|wxDIALOG_NO_PARENT|wxSTAY_ON_TOP|wxNO_BORDER)
{
	//Affiche le titre et le message.
	_staticTextTitle->SetLabelMarkup("<b>"+title+"</b>");
	_staticTextMessage->SetLabel(message);
	
	//Recalcule de la tille de la fenêtre.
	this->Layout();
	GetSizer()->Fit(this);
}

FrameNotification::~FrameNotification()
{
}

void FrameNotification::show(int timeout)
{
	ShowWithoutActivating();
}

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
	FrameNotification *frame = new FrameNotification(title, message);
	frame->show(timeout);
	#endif
}
