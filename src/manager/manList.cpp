//! \file **********************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ****************************************************************************

//App
#include "manager/manList.hpp"

// *****************************************************************************
// Class ManList
// *****************************************************************************

ManList::ManList()
{
}

ManList::~ManList()
{
}

IMPLEMENT_MANAGER(ManList);

wxWindow* ManList::newEditWindow(wxWindow* parent)
{
	wxWindow* tmp = new wxWindow(	parent,
									wxID_ANY,
									wxDefaultPosition,
									wxDefaultSize,
									0,
									_("Lists"));
	return tmp;
}

void ManList::manLoad(wxFileConfig&)
{
}

void ManList::manSave(wxFileConfig&)const
{
}
