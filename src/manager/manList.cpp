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
#include "manager/manAction.hpp"
#include "manager/manCache.hpp"
#include "dialog/dlgNewList.hpp"
#include "dialog/dlgFind.hpp"
#include "shortcut.hpp"
#include "defs.hpp"

//Stl
#include <vector>

//WxWidgets
#include <wx/sizer.h>
#include <wx/dir.h>
#include <wx/filefn.h> 
#include <wx/stdpaths.h>
#include <wx/arrstr.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>

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

bool ManList::remove(wxString const& name)
{
	List list = getList(name);
	
	if(list.isOk() != STATUS_OK)
		return false;
		
	if(list.clear() == STATUS_SUCCESS)
		return true;
		
	return false;
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
	_ctrlDataList->addMenuItemSeparator();
	_ctrlDataList->addMenuItem(wxID_PREVIEW, 	wxEmptyString, ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addMenuItem(wxID_PRINT, 		wxEmptyString, ENABLE_SELECTING_ITEMS);
	
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
	sizeButtons->Add(buttonImport, 		0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	sizeButtons->Add(buttonEdit, 		0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	sizeButtons->Add(buttonNew, 		0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_ctrlDataList, 	1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	sizerMain->Add(sizeButtons,		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(sizerMain);
	
	//Bind
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onNew, 	this, wxID_NEW);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onEdit,	this, wxID_EDIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onFind, 	this, wxID_FIND);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onDelete, 	this, wxID_DELETE);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onLearn, 	this, ID_LEARN);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onExport, 	this, ID_EXPORT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onImport, 	this, ID_IMPORT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onPreview, this, wxID_PREVIEW);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onPrint, 	this, wxID_PRINT);
	
	Bind(wxEVT_BUTTON, 					&WinManList::onDelete, 	this, wxID_DELETE);
	Bind(wxEVT_BUTTON, 					&WinManList::onImport,	this, ID_IMPORT);
	Bind(wxEVT_BUTTON, 					&WinManList::onEdit,	this, wxID_EDIT);
	Bind(wxEVT_BUTTON, 					&WinManList::onNew, 	this, wxID_NEW);
	
	//Accélérateurs
	wxAcceleratorEntry entries[4];
    entries[0].Set(wxACCEL_CTRL, 	(int) 'F', 		wxID_FIND);
    entries[1].Set(wxACCEL_CTRL, 	(int) 'N', 		wxID_NEW);
    entries[2].Set(wxACCEL_CTRL, 	(int) 'P', 		wxID_PRINT);
    entries[3].Set(wxACCEL_NORMAL,	 WXK_DELETE, 	wxID_DELETE);
    wxAcceleratorTable accel(4, entries);
    SetAcceleratorTable(accel);
}

WinManList::~WinManList()
{
	//On travaille dans le dossier utilisateur.
	ManList::get().workToTmp(false);
	ManCache::get().workToTmp(false);
	
	//Unbind
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onNew, 	this, wxID_NEW);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onEdit,	this, wxID_EDIT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onFind, 	this, wxID_FIND);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onDelete, 	this, wxID_DELETE);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onLearn, 	this, ID_LEARN);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onExport, 	this, ID_EXPORT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onImport, 	this, ID_IMPORT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onPreview, this, wxID_PREVIEW);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManList::onPrint, 	this, wxID_PRINT);
	
	Unbind(wxEVT_BUTTON, 					&WinManList::onDelete, 	this, wxID_DELETE);
	Unbind(wxEVT_BUTTON, 					&WinManList::onImport,	this, ID_IMPORT);
	Unbind(wxEVT_BUTTON, 					&WinManList::onEdit,	this, wxID_EDIT);
	Unbind(wxEVT_BUTTON, 					&WinManList::onNew, 	this, wxID_NEW);
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
}

void WinManList::refreshManagerFromGui()const
{
}
#include <iostream>
void WinManList::onNew(wxCommandEvent&)
{
	DlgNewList dlg(DialogInlay::findParent());
	while(dlg.showModal() == wxID_OK)
	{
		//On vérifie si la liste n'est pas existante.
		if(dlg.getNameList().IsEmpty())
		{
			wxMessageDialog dlgm(this,
					_("You didn't chose a new list name!"),
					_("List no name"),
					wxOK|wxICON_INFORMATION|wxCENTRE);
			dlgm.ShowModal();
		}
		else if(ManList::get().existList(dlg.getNameList()))
		{
			wxMessageDialog dlgm(this,
					_("The list is already existing!"),
					_("List existing"),
					wxOK|wxICON_INFORMATION|wxCENTRE);
			dlgm.ShowModal();
		}
		else
		{
			//Creation et ajoute de la list. 
			wxLanguage lgsrc;
			wxLanguage lgto;
			dlg.getLanguages(&lgsrc, &lgto);
			ManList::get().createList(dlg.getNameList(), lgsrc, lgto);
			
			wxVector<wxVariant> data;
			data.clear();
			data.push_back(wxVariant(dlg.getNameList()));
			data.push_back(wxVariant(wxLocale::GetLanguageName(lgsrc)));
			data.push_back(wxVariant(wxLocale::GetLanguageName(lgto)));
			_ctrlDataList->AppendItem(data);
			
			ensureVisible(dlg.getNameList());
			break;
		}
	}
}

void WinManList::onEdit(wxCommandEvent&)
{
	std::cout << "WinManList::onEdit" << std::endl;
}

void WinManList::onFind(wxCommandEvent&)
{
	DlgFind dlg(this, _("Find a list"), ManList::get().getNamesLists());
	if(dlg.ShowModal() == wxID_OK)
		ensureVisible(dlg.getValue());
}

void WinManList::onDelete(wxCommandEvent&)
{
	wxMessageDialog dlg(this, _("Is you sure to want delete the lists selected?"), _("Delete lists"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
			
	//On doit supprimer les listes?
	if(dlg.ShowModal() == wxID_YES)//Oui
	{	
		wxDataViewItemArray itemsSelected;
		_ctrlDataList->GetSelections(itemsSelected);
		
		for(auto it: itemsSelected)
		{
			int row = _ctrlDataList->ItemToRow(it);
			wxString tmpList = _ctrlDataList->GetTextValue(row, 0);
			
			std::vector<ShortcutKey> tmpShortcut;
			
			//Récupéret les actions qui sont utilise par la liste.
			for(auto ita: ManAction::get().getShortcutKeysActions())
			{
				if(ita.second->listIsUsed(tmpList))
					tmpShortcut.push_back(ita.first);
			}
			
			//Des action utilise cette liste ?
			if(tmpShortcut.size() > 0)
			{
				wxMessageDialog dlg(this,
									wxString::Format(_("There are actions used this list \"%s\".\nDo you want delete the list and the actions?"), tmpList),
									_("Delete action"),
									wxYES_NO|wxICON_QUESTION|wxCENTRE);
									
				if(dlg.ShowModal() == wxID_NO)
					continue;
			}
			
			//On supprime les actions
			for(auto its: tmpShortcut)
				ManAction::get().remove(its);
			
			//On supprime la liste
			ManList::get().remove(tmpList);
			_ctrlDataList->DeleteItem(row);
		}
	}
}

void WinManList::onLearn(wxCommandEvent&)
{
	std::cout << "WinManList::onLearn" << std::endl;
}

void WinManList::onExport(wxCommandEvent&)
{
	std::cout << "WinManList::onExport" << std::endl;
}

void WinManList::onImport(wxCommandEvent&)
{
	std::cout << "WinManList::onImport" << std::endl;
}

void WinManList::onPreview(wxCommandEvent&)
{
	std::cout << "WinManList::onPreview" << std::endl;
}

void WinManList::onPrint(wxCommandEvent&)
{
	std::cout << "WinManList::onPrint" << std::endl;
}

bool WinManList::ensureVisible(wxString nameList)
{
	_ctrlDataList->UnselectAll();
	
	//On cherche le raccourcie dans le _ctrlDataList
	for(int i = 0; i<_ctrlDataList->GetItemCount(); i++)
	{
		//Si on a trouver, on le rend visible.
		if(_ctrlDataList->GetTextValue(i, 0) == nameList)		
		{			
			_ctrlDataList->EnsureVisible(_ctrlDataList->RowToItem(i));
			_ctrlDataList->SelectRow(i);
			_ctrlDataList->updateEnableElements();
			return true;
		}	
	}
	
	return false;
}
