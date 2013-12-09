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

wxWindow* ManList::newEditWindow(wxWindow* parent)
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
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Lists"))
{
	//Creation de la liste.
	_controlDataList = new ControlDataList(this);
	
	//Ajout des colonnes.
	_controlDataList->AppendTextColumn(
							_("List name"),
							wxDATAVIEW_CELL_INERT,
							150,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
										
	_controlDataList->AppendTextColumn(
							_("Source language"),
							wxDATAVIEW_CELL_INERT,
							150,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
							
	_controlDataList->AppendTextColumn(
							_("Translation language"),
							wxDATAVIEW_CELL_INERT,
							-1,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
							
	//Remplissage de la liste.(TMP)
	wxVector<wxVariant> data;
	data.push_back( wxVariant("List1") );
	data.push_back( wxVariant("en") );
	data.push_back( wxVariant("fr") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("List2") );
	data.push_back( wxVariant("fr") );
	data.push_back( wxVariant("en") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("Cache") );
	data.push_back( wxVariant("en") );
	data.push_back( wxVariant("fr") );
	_controlDataList->AppendItem( data );
							
	//Créations du menu.
	_controlDataList->addMenuItem(	wxID_NEW);
	_controlDataList->addMenuItem(	wxID_EDIT,	
									wxEmptyString,
									ENABLE_SELECTING_ONE_ITEM);
	_controlDataList->addMenuItem(	wxID_FIND);
	_controlDataList->addMenuItem(	wxID_DELETE,
									wxEmptyString,
									ENABLE_SELECTING_ITEMS);
	_controlDataList->addMenuItemSeparator();
	_controlDataList->addMenuItem(	wxID_ANY,
									_("Export"),
									ENABLE_SELECTING_ITEMS);
	_controlDataList->addMenuItem(	wxID_ANY,
									_("Import"));
	
	//Créations des boutons.
	wxButton* buttonDelete =	new wxButton(this, wxID_DELETE);
	wxButton* buttonImport = 	new wxButton(this, wxID_ANY, _("Import"));
	wxButton* buttonEdit = 		new wxButton(this, wxID_EDIT);
	wxButton* buttonNew = 		new wxButton(this, wxID_NEW);
	
	//Ajout des bouton au ControlDataList pour qu'il s'occupe d'activer ou pas
	//les boutons en fonction de la sélection.
	_controlDataList->addWindowEnable(	buttonDelete,
										ENABLE_SELECTING_ITEMS);
	_controlDataList->addWindowEnable(	buttonEdit,
										ENABLE_SELECTING_ONE_ITEM);
	//_controlDataList->addWindowEnable(	buttonImport,
	//										ENABLE_ANYTIME);
	//_controlDataList->addWindowEnable(	buttonNew,
	//										ENABLE_ANYTIME);

	//Mise en forme des boutons avec un sizer.
	wxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(buttonDelete,	 	0, wxEXPAND);
	buttonsSizer->AddStretchSpacer(1);
	buttonsSizer->Add(buttonImport, 	0, wxEXPAND);
	buttonsSizer->Add(buttonEdit, 		0, wxEXPAND);
	buttonsSizer->Add(buttonNew, 		0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(_controlDataList, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);
	mainSizer->Add(buttonsSizer, 	 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);	
	SetSizer(mainSizer);
}

WinManList::~WinManList()
{
}
