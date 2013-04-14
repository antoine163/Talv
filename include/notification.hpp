//! \file **************************************************************
//! \brief Header notification.
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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "singleton.hpp"

#include <wx/string.h>

// *********************************************************************
// Class Notification
// *********************************************************************

//! \brief .
class Notification : public Singleton<Notification>
{	
	friend class Singleton<Notification>;
	
	public:
		void notify(wxString const& title,
					wxString const& message=wxEmptyString,
					int timeout = 5);
	
	private:
		Notification();
		~Notification();
};

#endif //NOTIFICATION_H
