//! \file **********************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.0
//! \date 20.03.2013
//!
//! ****************************************************************************

//App
#include "manager/manAction.hpp"

// *****************************************************************************
// Class ManAction
// *****************************************************************************

ManAction::ManAction()
{
}

ManAction::~ManAction()
{
}

IMPLEMENT_MANAGER(ManAction);

wxWindow* ManAction::newEditWindow(wxWindow* parent)
{
	wxWindow* tmp = new wxWindow(	parent,
									wxID_ANY,
									wxDefaultPosition,
									wxDefaultSize,
									0,
									_("Actions"));
	return tmp;
}

void ManAction::manLoad(wxFileConfig&)
{
}

void ManAction::manSave(wxFileConfig&)const
{
}
