//! \file **************************************************************
//! \brief Header Gestion notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 12.04.2013
//!
//! ********************************************************************

#ifndef MAN_NOTIFICATION_H
#define MAN_NOTIFICATION_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManNotification
// *****************************************************************************

//! \ingroup manager
//! \brief ManNotification
class ManNotification : public Manager
{
	DECLARE_MANAGER(ManNotification);
	
	public:
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_NOTIFICATION_H
