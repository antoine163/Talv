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
}

void ListManager::load(wxFileConfig& fileConfig)
{
	//wxString tmpNameList;
	//long lIndex;
	
	////Avent de charger quoi que se soi on supprime tout les instance des liste.
	//for(auto &it: _lists)
		//delete it;
		
	//_lists.clear();
	
	////On positionne le path.
	//fileConfig.SetPath("/ListManager");
	
	////On récupère la première list.
	//if(!fileConfig.GetFirstGroup(tmpNameList, lIndex))
		//return;
		
	//do
	//{
		////On positionne le path.
		//fileConfig.SetPath(tmpNameList);
		
		////Récupération des paramètres de la liste.
		//wxString tmplgsrc;
		//wxString tmplgto;
		//fileConfig.Read("lgsrc", &tmplgsrc);
		//fileConfig.Read("lgto", &tmplgto);
		
		////Création de la liste.
		//create(tmpNameList, tmplgsrc, tmplgto);
		
		////On positionne le path.
		//fileConfig.SetPath("../");
		
	//}//Puis toutes les autres.
	//while(fileConfig.GetNextGroup(tmpNameList, lIndex));
	
	////On positionne le path a la racine.
	//fileConfig.SetPath("/");
}

void ListManager::save(wxFileConfig& fileConfig)const
{
	////Parcoure tout les lites.
	//for(auto it: _lists)
	//{
		////Crée un groupe pour cette liste.
		//fileConfig.SetPath("/ListManager/"+it->getName());
		
		////Sauvegarde des paramètres de la liste.
		//fileConfig.Write("lgsrc", it->_lgsrc);
		//fileConfig.Write("lgto", it->_lgto);
	//}
}

// *********************************************************************
// Class EditListManager
// *********************************************************************

void EditListManager::init()
{
}

void EditListManager::apply()
{
}

wxArrayString EditListManager::getNameLists()const
{
	wxArrayString tmpArrayString;
	
	//Parcoure des lites.
	//for(auto it: _data)
	//{
		////Ajout de la liste au wxArrayString.
		//tmpArrayString.Add(it.first);
	//}
	
	return tmpArrayString;
}

wxArrayString EditListManager::getNameListsByLanguages(	wxString const& lgsrc,
													wxString const& lgto)const
{
	wxArrayString tmpArrayString;
	
	////Parcoure des lites.
	//for(auto it: _lists)
	//{
		////Si les lange son équivalente.
		//if(it->_lgsrc == lgsrc && it->_lgto == lgto)
		//{
			////Ajout de la liste au wxArrayString.
			//tmpArrayString.Add(it->getName());
		//}
	//}
	
	return tmpArrayString;
}
