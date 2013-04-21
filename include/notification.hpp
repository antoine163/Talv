//! \file **************************************************************
//! \brief Header notification.
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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "singleton.hpp"
#include <wx/string.h>

#ifdef USE_EMULATE_NOTIFICATION
	#include "guiDialogNotification.h"
	#include <wx/frame.h>
	#include <wx/event.h>
	#include <vector>
#endif


// *********************************************************************
// Class DialogNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

//! \brief .
class DialogNotification : public GuiDialogNotification
{	

	public:
		DialogNotification(	wxString const& title,
							wxString const& message);
		~DialogNotification();
		
		void show(int timeout);
		void exit();
	
	protected:
		void OnClose(wxCloseEvent&);
		void OnLeftDown(wxMouseEvent&);
	
	private:

};

wxDECLARE_EVENT(EVT_EXIT_DIALG_NOTIFICATION, wxCommandEvent);

#endif

// *********************************************************************
// Class Notification
// *********************************************************************

//! \brief .
class Notification : public wxEvtHandler, public Singleton<Notification>
{	
	friend class Singleton<Notification>;
	
	public:
		void notify(wxString const& title,
					wxString const& message=wxEmptyString);
		
	#ifdef USE_EMULATE_NOTIFICATION
		void OnExitDialogNotification(wxCommandEvent& event);
	#endif
	
	private:
		Notification();
		~Notification();
		
	#ifdef USE_EMULATE_NOTIFICATION
		std::vector<DialogNotification*> _dialogs;
	#endif
};

#endif //NOTIFICATION_H
