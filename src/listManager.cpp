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
	//Suppression des listes
	for(auto it: _lists)
	{
		delete it;
	}
}

void ListManager::load(wxFileConfig & fileConfig)
{
}

void ListManager::save(wxFileConfig & fileConfig)const
{
	
}

List* ListManager::getList(wxString const& name)
{
	//Recherche de la liste.
	for(auto it: _lists)
	{
		//La liste a été trouvée ?
		if(it->getName() == name)
			return it;
	}
	
	//La liste n'a pas été trouvée.
	return nullptr;
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
	
	//_lists
}
