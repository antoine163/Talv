//! \file **************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "listManager.hpp"
#include <wx/utils.h> 
#include <wx/debug.h> 

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
	wxString tmpNameList;
	long lIndex;
	
	//Avent de charger quoi que se soi on supprime tout les instance des liste.
	for(auto &it: _lists)
		delete it;
		
	_lists.clear();
	
	//On positionne le path.
	fileConfig.SetPath("/ListManager");
	
	//On récupère la première list.
	if(!fileConfig.GetFirstGroup(tmpNameList, lIndex))
		return;
		
	do
	{
		//On positionne le path.
		fileConfig.SetPath(tmpNameList);
		
		//Récupération des paramètres de la liste.
		wxString tmplgsrc;
		wxString tmplgto;
		fileConfig.Read("lgsrc", &tmplgsrc);
		fileConfig.Read("lgto", &tmplgto);
		
		//Création de la liste.
		create(tmpNameList, tmplgsrc, tmplgto);
		
		//On positionne le path.
		fileConfig.SetPath("../");
		
	}//Puis toutes les autres.
	while(fileConfig.GetNextGroup(tmpNameList, lIndex));
	
	//On positionne le path a la racine.
	fileConfig.SetPath("/");
}

void ListManager::save(wxFileConfig & fileConfig)const
{
	//Parcoure tout les lites.
	for(auto it: _lists)
	{
		//Crée un groupe pour cette liste.
		fileConfig.SetPath("/ListManager/"+it->getName());
		
		//Sauvegarde des paramètres de la liste.
		fileConfig.Write("lgsrc", it->_lgsrc);
		fileConfig.Write("lgto", it->_lgto);
	}
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

wxArrayString ListManager::getNameListsByLanguages(
	wxString const& lgsrc,
	wxString const& lgto)const
{
	wxArrayString tmpArrayString;
	
	//Parcoure des lites.
	for(auto it: _lists)
	{
		//Si les lange son équivalente.
		if(it->_lgsrc == lgsrc && it->_lgto == lgto)
		{
			//Ajout de la liste au wxArrayString.
			tmpArrayString.Add(it->getName());
		}
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
	List* tmpList = new List(wxGetUserHome()+"/"+PROJECT_NAME+"List/"+name, lgsrc, lgto);
	if(tmpList != nullptr)
		_lists.push_back(tmpList);
	
	return tmpList;
}

bool ListManager::remove(wxString const& name)
{
	//Recherche de la liste.
	for(size_t i = 0; _lists.size(); i++)
	{
		//La liste a été trouvée ?
		if(_lists[i]->getName() == name)
		{
			//Suppression de la liste
			_lists[i]->removeFile();
			delete _lists[i];
			_lists.erase(_lists.begin()+i);
			
			return true;
		}
	}
	
	//La liste n'a pas été trouvée.
	return false;
}
