//! \file **************************************************************
//! \brief Source Gestion notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 12.04.2013
//!
//! ********************************************************************

//App
#include "manager/manNotification.hpp"

// *****************************************************************************
// Class ManTts
// *****************************************************************************

ManNotification::ManNotification()
{
}

ManNotification::~ManNotification()
{
}

IMPLEMENT_MANAGER(ManNotification);

WinManager* ManNotification::newEditWindow(wxWindow* parent)
{
	//wxWindow* tmp = new wxWindow(	parent,
									//wxID_ANY,
									//wxDefaultPosition,
									//wxDefaultSize,
									//0,
									//_("Notification"));
	//return tmp;
	return nullptr;
}

void ManNotification::manLoad(wxFileConfig&)
{
}

void ManNotification::manSave(wxFileConfig&)const
{
}
