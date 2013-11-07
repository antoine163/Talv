//! \file **************************************************************
//! \brief Source Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.16
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "listManager.hpp"

#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include <wx/utils.h> 
#include <wx/dir.h>

//TEST
#include <iostream>

// *********************************************************************
// Class PanelListLists
// *********************************************************************

PanelListLists::PanelListLists(wxWindow* parent)
: PanelList(parent, _("list"))
{
	_listCtrl->AppendColumn(_("Name"), wxLIST_FORMAT_LEFT, 158);
	_listCtrl->AppendColumn(_("Language source"), wxLIST_FORMAT_LEFT, 158);
	_listCtrl->AppendColumn(_("Language of translation"), wxLIST_FORMAT_LEFT, 158);
}

PanelListLists::~PanelListLists()
{
}

void PanelListLists::Update()
{
	std::cout << "PanelListLists::Update" << std::endl;
	////Vide la liste.
	//clear();
	
	//wxString tmplgsrc;
	//wxString tmplgto;
	
	////Rempli la liste.
	//auto lists = EditListManager::getInstance()->getData();
	//for(auto it: lists)
	//{		
		////Récupération des langues
		//it.second->getlanguages(&tmplgsrc, &tmplgto);
		
		////Préparation d'un wxArrayString pour l'ajout d'un item.
		//wxArrayString tmpItem;
		//tmpItem.Add(it.first);
		//tmpItem.Add(Resource::getInstance()->abbreviationToLanguage(tmplgsrc));
		//tmpItem.Add(Resource::getInstance()->abbreviationToLanguage(tmplgto));
		
		////Ajout de l'item dans la liste.
		//addItem(tmpItem, false);
	//}
}

bool PanelListLists::OnDeleteItem(wxString const& item)
{
	//auto shortcuts = EditActionManager::getInstance()->getShortcutUsedList(item);
	
	////Des action utilise cette liste ?
	//if(shortcuts.size() != 0)
	//{
		////Si il y a des action qui utilise cette liste,
		////On demande confirmation de pour supprimer aussi les action utiliser cette liste.
		//wxMessageDialog dlg(this, _("Of actions use this list. Are you sure of want delete the actions and a list?"), _("Delete actions and list"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
		//if(dlg.ShowModal() == wxID_NO)
			//return false;
	//}
	
	////Suppression des actions.
	//for(auto it: shortcuts)
		//EditActionManager::getInstance()->remove(it);
	
	////Suppression de la liste.
	//EditListManager::getInstance()->getValue(item)->removeFile();
	//EditListManager::getInstance()->remove(item);
	
	return true;
}

//! \todo A implémenter.
wxArrayString PanelListLists::OnPreferencesItem(wxString const& item)
{
	wxMessageDialog dlg(this, _("Sorry, No implemented!"), _("No implemented"), wxOK|wxICON_INFORMATION|wxCENTRE);
	dlg.ShowModal();
	return wxArrayString();
}

wxArrayString PanelListLists::OnAddItem()
{	
	//wxArrayString de retours.
	wxArrayString newItem;
	
	//DialogListAdd dlg(this);
	//while(1)
	//{
		////Montre le dialogue
		//if(dlg.ShowModal() == wxID_OK)
		//{
			////Récupère la nouvelle liste.
			//wxString newList = dlg.getNamelist();
			
			////newList est vide ?
			//if(newList.IsEmpty())
				//break;
			
			////vérifie si la liste n'est pas déjà existent.
			//if(EditListManager::getInstance()->exist(newList))
			//{
				//wxMessageDialog dlg(this, _("The list already exist!"), _("List exist"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
				//dlg.ShowModal();
				
				//continue;
			//}
			
			////Récupération des langue.
			//wxString lgsrc;
			//wxString lgto;
			//dlg.getlanguages(&lgsrc, &lgto);
			
			////On crée une nouvelle liste.
			//if(!EditListManager::getInstance()->createAndAddList(newList, lgsrc, lgto))
			//{
				//wxMessageDialog dlg(this, _("A problem is occured, the list can't add!"), _("List corrupt"), wxOK|wxICON_INFORMATION|wxCENTRE);
				//dlg.ShowModal();
				
				//continue;
			//}
			
			////Un nouveau item
			//newItem.Add(newList);
			//newItem.Add(Resource::getInstance()->abbreviationToLanguage(lgsrc));
			//newItem.Add(Resource::getInstance()->abbreviationToLanguage(lgto));
		
			////Une liste à ajouter;
			//_newLists.Add(newList);
		//}
		//break;
	//}
	
	return newItem;
}

// *********************************************************************
// Class ListManagerBase
// *********************************************************************

ListManagerBase::ListManagerBase()
{
}

ListManagerBase::~ListManagerBase()
{
}

bool ListManagerBase::createAndAddList(	wxString const &listName,
										wxString const &lgsrc,
										wxString const &lgto)
{
	//Création et initialisation d'une nouvelle liste.
	List* tmpList = new List();
	if(tmpList->init(getPath()+'/'+listName, lgsrc, lgto))
	{
		//Si l'init est ok, on l'ajout.
		if(add(listName, tmpList))
			return true;
	}

	delete tmpList;
	return false;
}

wxArrayString ListManagerBase::getNameLists()const
{
	wxArrayString tmpArrayString;
	
	//Parcoure des lites.
	for(auto it: _data)
	{
		//Ajout de la liste au wxArrayString.
		tmpArrayString.Add(it.first);
	}
	
	return tmpArrayString;
}

wxArrayString ListManagerBase::getNameListsByLanguages(	wxString const& lgsrc,
														wxString const& lgto)const
{
	wxArrayString tmpArrayString;
	wxString tmplgsrc;
	wxString tmplgto;
	
	//Parcoure des lites.
	for(auto it: _data)
	{
		//Récupère les langages de la liste.
		it.second->getlanguages(&tmplgsrc, &tmplgto);
		
		//Si les lange son équivalente.
		if(tmplgsrc == lgsrc && tmplgto == lgto)
		{
			//Ajout le nom de la liste au wxArrayString.
			tmpArrayString.Add(it.first);
		}
	}
	
	return tmpArrayString;
}

// *********************************************************************
// Class ListManager
// *********************************************************************

ListManager::ListManager() :
EditableByPanel(_("Lits"))
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
	{
		//On positionne le path a la racine.
		fileConfig.SetPath("/");
		return;
	}
		
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
		createAndAddList(tmpNameList, tmplgsrc, tmplgto);
		
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

List* ListManager::getListCheckDialog(	wxString const& listName,
										wxString const& actionName)
{
	//On vérifie la validités de la liste (Liste existante ou pas).
	List* tmpList = getValue(listName);
	if(tmpList == nullptr)
	{
		wxMessageBox(wxString::Format(_("Sorry, the list '%s' is nonexistent.\nPlease correct this problem in delete this action (%s)."), listName, actionName), _("List invalid."), wxOK|wxICON_EXCLAMATION|wxCENTRE);
	}
	
	return tmpList;
}

wxString ListManager::getPath()
{
	return wxStandardPaths::Get().GetUserDataDir()+"/lists";
}

wxPanel* ListManager::newEditPanel(wxWindow *parent)
{
	return new PanelListLists(parent);
}

bool ListManager::check()const
{
	return true;
}

bool ListManager::apply()
{
	return true;
}

// *********************************************************************
// Class EditListManager
// *********************************************************************

EditListManager::EditListManager()
{
}

EditListManager::~EditListManager()
{
	//Destruction du dossier temporaire.
	wxDir::Remove(EditListManager::getPath(), wxPATH_RMDIR_RECURSIVE);
}

void EditListManager::init()
{	
	//Récupération de ListManager.
	ListManager* listManager = ListManager::getInstance();
	
	//Création du répertoire temporaire.
	wxDir::Make(getPath(),  wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
		
	//Récupération des listes.
	auto lists = listManager->getData();
	
	wxString tmplgsrc;
	wxString tmplgto;
		
	//Copie de tout les listes.
	for(auto it : lists)
	{
		//Si le fichier de la liste existe.
		if(wxFileExists(listManager->getPath()+'/'+it.first))
		{
			//Copie la liste dans le dossier temporaire.
			wxCopyFile(	listManager->getPath()+'/'+it.first,
						getPath()+'/'+it.first);
		}
			
		//Récupération des langues
		it.second->getlanguages(&tmplgsrc, &tmplgto);
		
		//Création et initialisation d'une nouvelle liste.
		createAndAddList(it.first, tmplgsrc, tmplgto);
	}
}

void EditListManager::apply()
{	
	//Récupération de ListManager.
	ListManager* listManager = ListManager::getInstance();
	
	//Destruction du dossier des liste utilisateur.
	wxDir::Remove(listManager->getPath(), wxPATH_RMDIR_RECURSIVE);
	
	//Création du dossier des liste utilisateur.
	wxDir::Make(listManager->getPath(),  wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	
	//On supprime tout
	listManager->removeAll();
		
	//Copie de tout les listes.
	wxString tmplgsrc;
	wxString tmplgto;
	for(auto it : _data)
	{
		//Si le fichier de la liste existe.
		if(wxFileExists(getPath()+'/'+it.first))
		{
			//Copie la liste dans le dossier temporaire.
			wxCopyFile(	getPath()+'/'+it.first,
						listManager->getPath()+'/'+it.first);
		}
							
		//Récupération des langues
		it.second->getlanguages(&tmplgsrc, &tmplgto);
		
		//Création et initialisation d'une nouvelle liste.
		listManager->createAndAddList(it.first, tmplgsrc, tmplgto);
	}
}

wxString EditListManager::getPath()
{
	return wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME;
}
