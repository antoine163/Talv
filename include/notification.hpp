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
#endif


// *********************************************************************
// Class FrameNotification
// *********************************************************************

#if defined(USE_EMULATE_NOTIFICATION) || defined(__DOXYGEN__)

//! \brief .
class FrameNotification : public GuiDialogNotification
{	

	public:
		FrameNotification(	wxString const& title,
							wxString const& message=wxEmptyString);
		~FrameNotification();
		
		void show(int timeout);
	
	private:

};

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
	#endif
	
	private:
		Notification();
		~Notification();
		
	#ifdef USE_EMULATE_NOTIFICATION
	#endif
};

#endif //NOTIFICATION_H
