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
	//Avent de charger quoi que se soi on supprime tout les instance des liste.
	for(auto &it: _lists)
		delete it;
		
	_lists.clear();
	
	
}

void ListManager::save(wxFileConfig & fileConfig)const
{
	//int iList = 0;
	
	//for(auto &it: _lists)
	//{
		////Crée un groupe pour cette liste.
		//fileConfig.SetPath("/list"+i);
		
		////Sauvegarde de la liste dans le fichier de config.
		//it->save(fileConfig);
		
		//i++;
	//}
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
	wxArrayString tmpArrayString;
	
	//Parcoure des lites.
	for(auto it: _lists)
	{
		//Ajout de la liste au wxArrayString.
		tmpArrayString.Add(it->getName());
	}
	
	return tmpArrayString;
}

bool ListManager::exist(wxString const& name)const
{
	//Recherche de la liste.
	for(auto it: _lists)
	{
		//La liste a été trouvée ?
		if(it->getName() == name)
			return true;
	}
	
	//La liste n'a pas été trouvée.
	return false;
}

List* ListManager::create(	wxString const& name,
							wxString const& lgsrc,
							wxString const& lgto)
{
	//Versification si la liste est déjà existent.
	if(exist(name))
		return nullptr;
		
	//Création et ajout de la liste.
	List* tmpList = new List(name, lgsrc, lgto);
	if(tmpList != nullptr)
		_lists.push_back(tmpList);
	
	return tmpList;
}

//! \todo supprimer le fichier
bool ListManager::remove(wxString const& name)
{
	//Recherche de la liste.
	for(auto it: _lists)
	{
		//La liste a été trouvée ?
		if(it->getName() == name)
		{
			//Suppression de la liste
			//it->removeFile();
			//it=_lists.erase(it);
			delete it;
			return true;
		}
	}
	
	//La liste n'a pas été trouvée.
	return false;
}
