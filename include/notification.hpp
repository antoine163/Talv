//! \file **************************************************************
//! \brief Header notification.
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

//! \brief .
class FrameNotification : public GuiFrameNotification
{	
	public:
		FrameNotification(	wxString const& title,
							wxString const& message);
		~FrameNotification();
		
		void show(int timeout);
		void exit();
	
	protected:
		void OnClose(wxCloseEvent&);
		void OnLeftDown(wxMouseEvent&);
		void OnTimeout(wxTimerEvent&);
	
	private:
		wxTimer _timeout;

};

wxDECLARE_EVENT(EVT_EXIT_FRAME_NOTIFICATION, wxCommandEvent);

#endif

// *********************************************************************
// Class Notification
// *********************************************************************

//! \brief .
class Notification : public Singleton<Notification>
{	
	friend class Singleton<Notification>;
	
	public:
		void notify(wxString const& title,
					wxString const& message=wxEmptyString);
		
	#ifdef USE_EMULATE_NOTIFICATION
		void OnExitFrameNotification(wxCommandEvent& event);
	#endif
	
	private:
		Notification();
		~Notification();
		
	#ifdef USE_EMULATE_NOTIFICATION
		std::vector<FrameNotification*> _framesNotify;
	#endif
};

#endif //NOTIFICATION_H
