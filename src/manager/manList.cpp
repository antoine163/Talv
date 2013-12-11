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
#include "defs.hpp"

//WxWidgets
#include <wx/sizer.h>

// *****************************************************************************
// Class ManList
// *****************************************************************************

ManList::ManList()
{
}

ManList::~ManList()
{
}

IMPLEMENT_MANAGER(ManList);

WinManager* ManList::newEditWindow(wxWindow* parent)
{
	return new WinManList(parent);
}

void ManList::manLoad(wxFileConfig&)
{
}

void ManList::manSave(wxFileConfig&)const
{
}

// *****************************************************************************
// Class WinManList
// *****************************************************************************

WinManList::WinManList(wxWindow* parent)
: WinManager(parent, _("Lists"))
{
	//Creation de la liste.
	_ctrlDataList = new CtrlDataList(this);
	
	//Ajout des colonnes.
	_ctrlDataList->AppendTextColumn(_("List name"), 			wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);	
	_ctrlDataList->AppendTextColumn(_("Source language"), 		wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_ctrlDataList->AppendTextColumn(_("Translation language"), 	wxDATAVIEW_CELL_INERT, -1, 	wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
							
	//Remplissage de la liste.(TMP)
	wxVector<wxVariant> data;
	data.push_back( wxVariant("List1") );
	data.push_back( wxVariant("en") );
	data.push_back( wxVariant("fr") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("List2") );
	data.push_back( wxVariant("fr") );
	data.push_back( wxVariant("en") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("Cache") );
	data.push_back( wxVariant("en") );
	data.push_back( wxVariant("fr") );
	_ctrlDataList->AppendItem( data );
							
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
	wxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(buttonDelete,	 	0, wxEXPAND);
	buttonsSizer->AddStretchSpacer(1);
	buttonsSizer->Add(buttonImport, 	0, wxEXPAND|wxRIGHT, SIZE_BORDER);//ajouter bordure
	buttonsSizer->Add(buttonEdit, 		0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	buttonsSizer->Add(buttonNew, 		0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(_ctrlDataList, 	1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	mainSizer->Add(buttonsSizer,	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(mainSizer);
}

WinManList::~WinManList()
{
}

void WinManList::refreshGuiFromManager()
{
}

void WinManList::refreshManagerFromGui()const
{
}
