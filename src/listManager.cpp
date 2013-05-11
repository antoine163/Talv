//! \file **************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "listManager.hpp"

#include <wx/stdpaths.h>
#include <wx/utils.h> 

//TEST
#include <iostream>

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
	wxString tmpNameList;
	long lIndex;
		
	//Avent de charger quoi que se soit, on supprime tout les listes.
	removeAll();
	
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
		
		//Création et initialisation d'une nouvelle liste.
		List* tmpList = new List();
		if(tmpList->init(getPath()+tmpNameList, tmplgsrc, tmplgto))
		{
			//Si l'init est ok, on l'ajout.
			add(tmpNameList, tmpList);
		}
		else
			delete tmpList;
		
		//On positionne le path.
		fileConfig.SetPath("../");
		
	}//Puis toutes les autres.
	while(fileConfig.GetNextGroup(tmpNameList, lIndex));
	
	//On positionne le path a la racine.
	fileConfig.SetPath("/");
}

void ListManager::save(wxFileConfig& fileConfig)const
{
	//Parcoure tout les lites.
	for(auto it: _data)
	{
		//Crée un groupe pour cette liste.
		fileConfig.SetPath("/ListManager/"+it.first);
		
		//Sauvegarde des paramètres de la liste.
		wxString lgsrc;
		wxString lgto;
		it.second->getlanguages(&lgsrc, &lgto);
		fileConfig.Write("lgsrc", lgsrc);
		fileConfig.Write("lgto", lgto);
	}
}

//! \todo à modifier
wxString ListManager::getPath()const
{
	return wxStandardPaths::Get().GetUserDataDir();
}

// *********************************************************************
// Class EditListManager
// *********************************************************************

EditListManager::EditListManager()
{
}

EditListManager::~EditListManager()
{
}

void EditListManager::init()
{
	std::cout << "GetAppDocumentsDir : " << wxStandardPaths::Get().GetAppDocumentsDir() << std::endl;
	std::cout << "GetConfigDir : " << wxStandardPaths::Get().GetConfigDir() << std::endl;
	std::cout << "GetDataDir : " << wxStandardPaths::Get().GetDataDir() << std::endl;
	std::cout << "GetDocumentsDir : " << wxStandardPaths::Get().GetDocumentsDir() << std::endl;
	std::cout << "GetExecutablePath : " << wxStandardPaths::Get().GetExecutablePath() << std::endl;
	std::cout << "GetInstallPrefix : " << wxStandardPaths::Get().GetInstallPrefix() << std::endl;
	std::cout << "GetLocalDataDir : " << wxStandardPaths::Get().GetLocalDataDir() << std::endl;
	std::cout << "GetPluginsDir : " << wxStandardPaths::Get().GetPluginsDir() << std::endl;
	std::cout << "GetResourcesDir : " << wxStandardPaths::Get().GetResourcesDir() << std::endl;
	std::cout << "GetTempDir : " << wxStandardPaths::Get().GetTempDir() << std::endl;
	std::cout << "GetUserConfigDir : " << wxStandardPaths::Get().GetUserConfigDir() << std::endl;
	std::cout << "GetUserDataDir : " << wxStandardPaths::Get().GetUserDataDir() << std::endl;
	std::cout << "GetUserLocalDataDir : " << wxStandardPaths::Get().GetUserLocalDataDir() << std::endl;
	
	
	//auto lists = ListManager::getInstance()->getData();
	
	////Copie de tout les listes.
	//for(auto it : lists)
	//{
		//add(it.first, it.second);
	//}
	
	
}

void EditListManager::apply()
{
}

wxString EditListManager::getPath()const
{
	return wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME;
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
