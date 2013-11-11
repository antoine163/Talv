//! \file **************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "managerList.hpp"

// *********************************************************************
// Class ManagerList
// *********************************************************************

ManagerList::ManagerList() :
EditableByPanel(_("Lits"))
{
}

ManagerList::~ManagerList()
{
}

void ManagerList::load(wxFileConfig& fileConfig)
{
}

void ManagerList::save(wxFileConfig& fileConfig)const
{
}


wxPanel* ManagerList::newEditPanel(wxWindow *parent)
{
	return nullptr;
}

bool ManagerList::panelCheck()const
{
	return true;
}

bool ManagerList::panelApply()
{
	return true;
}
