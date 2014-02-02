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
#include "manager/manCache.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/dir.h>
#include <wx/filefn.h> 
#include <wx/stdpaths.h>
#include <wx/arrstr.h>
#include <wx/filename.h>

// *****************************************************************************
// Class ManList
// *****************************************************************************

ManList::ManList()
: _workInTmp(false)
{
	_directoryUser = wxStandardPaths::Get().GetUserDataDir()+"/lists";
	_directoryTmp = wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME+"/lists";
	
	_workDirectory = _directoryUser;
	if(!wxDir::Exists(_workDirectory))
		wxDir::Make(_workDirectory);
}

ManList::~ManList()
{
}

IMPLEMENT_MANAGER(ManList);

WinManager* ManList::newEditWindow(wxWindow* parent)
{
	return new WinManList(parent);
}

bool ManList::existList(wxString const& name)const
{
	wxString fileName = name+".lis";
	return wxFileExists(_workDirectory+"/"+fileName);
}

bool ManList::createList(wxString const& name, wxLanguage lgsrc, wxLanguage lgto)
{
	if(existList(name))
		return false;
		
	wxString fileName = name+".lis";
	List newList;
	newList.setFileName(_workDirectory+"/"+fileName);
	newList.setLanguages(lgsrc, lgto);
	
	return true;
}

wxArrayString ManList::getNamesLists()const
{
	wxArrayString files;
	wxArrayString nameFiles;
	wxDir::GetAllFiles(_workDirectory, &files);
	
	wxFileName file;
	for(auto it: files)
	{
		file.Assign(it);
		nameFiles.Add(file.GetName());
	}
	
	return nameFiles;
}

wxArrayString ManList::getNamesLists(wxLanguage lgsrc, wxLanguage lgto)const
{
	wxArrayString lists = getNamesLists();
	wxArrayString tmpLists;
	wxLanguage tmpLgsrc;
	wxLanguage tmpLgto;
	for(auto it: lists)
	{
		getList(it).getLanguages(&tmpLgsrc, &tmpLgto);
		if(lgsrc == tmpLgsrc && lgto == tmpLgto)
			tmpLists.Add(it);
	}
	
	return tmpLists;
}

List ManList::getList(wxString const& name)const
{
	List rList;
	wxString fileName = name+".lis";
	rList.setFileName(_workDirectory+"/"+fileName);
	return rList;
}

void ManList::workToTmp(bool toTmp)
{
	//To Tmp
	if(!_workInTmp && toTmp)
	{
		wxDir::Make(_directoryTmp, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);

		wxArrayString files = getNamesLists();
		for(auto it: files)
			wxCopyFile(_directoryUser+"/"+it+".lis", _directoryTmp+"/"+it+".lis");
		
		_workDirectory = _directoryTmp;
	}
	//From Tmp
	else if(_workInTmp && !toTmp)
	{
		wxDir::Remove(_directoryTmp, wxPATH_RMDIR_FULL|wxPATH_RMDIR_RECURSIVE);
		_workDirectory = _directoryUser;
	}
	else
		return;
	
	_workInTmp = toTmp;
}

void ManList::applyTmp()const
{
	if(_workInTmp)
	{
		wxDir::Remove(_directoryUser, wxPATH_RMDIR_FULL|wxPATH_RMDIR_RECURSIVE);
		wxDir::Make(_directoryUser);
		
		wxArrayString files = getNamesLists();
		for(auto it: files)
			wxCopyFile(_directoryTmp+"/"+it+".lis", _directoryUser+"/"+it+".lis");
	}
}

void ManList::manLoad(wxFileConfig&)
{
}

void ManList::manSave(wxFileConfig&)const
{
	applyTmp();
}

// *****************************************************************************
// Class WinManList
// *****************************************************************************

WinManList::WinManList(wxWindow* parent)
: WinManager(parent, _("Lists"))
{
	//On travaille dans le dossier temporaire.
	ManList::get().workToTmp();
	ManCache::get().workToTmp();
	
	//Creation de la liste.
	_ctrlDataList = new CtrlDataList(this);
	
	//Ajout des colonnes.
	_ctrlDataList->AppendTextColumn(_("List name"), 			wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);	
	_ctrlDataList->AppendTextColumn(_("Source language"), 		wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_ctrlDataList->AppendTextColumn(_("Translation language"), 	wxDATAVIEW_CELL_INERT, -1, 	wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
							
	//Créations du menu.
	_ctrlDataList->addMenuItem(wxID_NEW, 	wxEmptyString, ENABLE_ANYTIME);
	_ctrlDataList->addMenuItem(wxID_EDIT, 	wxEmptyString, ENABLE_SELECTING_ONE_ITEM);
	_ctrlDataList->addMenuItem(wxID_FIND, 	wxEmptyString, ENABLE_ANYTIME);
	_ctrlDataList->addMenuItem(wxID_DELETE, wxEmptyString, ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addMenuItemSeparator();
	_ctrlDataList->addMenuItem(ID_LEARN, 	_("Learn"), ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addMenuItemSeparator();
	_ctrlDataList->addMenuItem(ID_EXPORT, 	_("Export"), ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addMenuItem(ID_IMPORT, 	_("Import"));
	
	//Créations des boutons.
	wxButton* buttonDelete =	new wxButton(this, wxID_DELETE);
	wxButton* buttonImport = 	new wxButton(this, ID_IMPORT, _("Import"));
	wxButton* buttonEdit = 		new wxButton(this, wxID_EDIT);
	wxButton* buttonNew = 		new wxButton(this, wxID_NEW);
	
	//Ajout des bouton au ControlDataList pour qu'il s'occupe d'activer ou pas
	//les boutons en fonction de la sélection.
	_ctrlDataList->addWindowEnable(	buttonDelete, 	ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addWindowEnable(	buttonEdit, 	ENABLE_SELECTING_ONE_ITEM);
	_ctrlDataList->addWindowEnable(buttonImport, 	ENABLE_ANYTIME);
	_ctrlDataList->addWindowEnable(buttonNew, 		ENABLE_ANYTIME);

	//Mise en forme des boutons avec un sizer.
	wxSizer* sizeButtons = new wxBoxSizer(wxHORIZONTAL);
	sizeButtons->Add(buttonDelete,	 	0, wxEXPAND);
	sizeButtons->AddStretchSpacer(1);
	sizeButtons->Add(buttonImport, 		0, wxEXPAND|wxRIGHT, SIZE_BORDER);//ajouter bordure
	sizeButtons->Add(buttonEdit, 		0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	sizeButtons->Add(buttonNew, 		0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_ctrlDataList, 	1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	sizerMain->Add(sizeButtons,		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(sizerMain);
}

WinManList::~WinManList()
{
	//On travaille dans le dossier utilisateur.
	ManList::get().workToTmp(false);
	ManCache::get().workToTmp(false);
}

void WinManList::refreshGuiFromManager()
{
	//On commence par tout effacer.
	_ctrlDataList->DeleteAllItems();
	
	//Récupération des Lists.
	wxArrayString lists = ManList::get().getNamesLists();
	//Récupération des Caches.
	wxArrayString caches = ManCache::get().getNamesCaches();
	
	wxVector<wxVariant> data;
	wxLanguage lgsrc;
	wxLanguage lgto;
	for(auto it: lists)
	{
		ManList::get().getList(it).getLanguages(&lgsrc, &lgto);
		
		data.clear();
		data.push_back(wxVariant(it));
		data.push_back(wxVariant(wxLocale::GetLanguageName(lgsrc)));
		data.push_back(wxVariant(wxLocale::GetLanguageName(lgto)));
		_ctrlDataList->AppendItem(data);
	}
	for(auto it: caches)
	{
		ManList::get().getList(it).getLanguages(&lgsrc, &lgto);
		
		data.clear();
		data.push_back(wxVariant(it));
		data.push_back(wxVariant(wxLocale::GetLanguageName(lgsrc)));
		data.push_back(wxVariant(wxLocale::GetLanguageName(lgto)));
		_ctrlDataList->AppendItem(data);
	}
}

void WinManList::refreshManagerFromGui()const
{
}
