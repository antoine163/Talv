//! \file **************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "listManager.hpp"

// *********************************************************************
// Class ListManager
// *********************************************************************

ListManager::ListManager()
{
}

ListManager::~ListManager()
{
}

void ListManager::load(wxFileConfig & fileConfig)
{
}

void ListManager::save(wxFileConfig & fileConfig)const
{
}

List* ListManager::getList(wxString const& name)
{
}

wxArrayString ListManager::getNameLists()const
{
}

bool ListManager::exist(wxString const& name)const
{
}

List* ListManager::add(	wxString const& name,
						wxString const& lgsrc,
						wxString const& lgto)
{
}

bool ListManager::remove(wxString const& name)
{
}
