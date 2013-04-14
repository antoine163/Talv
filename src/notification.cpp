//! \file **************************************************************
//! \brief Source notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
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
// Class Notification
// *********************************************************************
//! \todo a instenser/supprimer dans main.cpp
Notification::Notification()
{
	#ifdef __UNIX__
		if(!notify_init(PROJECT_NAME))
		{
			wxLogError(_("Libnotify could not be initialized."));
		}
	#endif
}

Notification::~Notification()
{
	#ifdef __UNIX__
		notify_uninit();
	#endif
}

void Notification::notify(	wxString const& title,
							wxString const& message,
							int timeout)
{
	#ifdef __UNIX__
		NotifyNotification * notify = notify_notification_new(title.mb_str(wxConvUTF8), message.fn_str(), "dialog-information");
		notify_notification_set_timeout(notify, timeout*1000);
		if(!notify_notification_show(notify, nullptr))
		{
			wxLogError(_("The notify could not be show."));
		}
	#else
		wxNotificationMessage notify(title, message);
		notify.Show(timeout);
	#endif
}
