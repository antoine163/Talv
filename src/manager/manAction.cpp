//! \file **********************************************************************
//! \brief Source Gestion des action/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.0
//! \date 20.03.2013
//!
//! ****************************************************************************

//App
#include "manager/manAction.hpp"

//WxWidgets
#include <wx/sizer.h>
#include <wx/button.h>

// *****************************************************************************
// Class ManAction
// *****************************************************************************

ManAction::ManAction()
{
}

ManAction::~ManAction()
{
}

IMPLEMENT_MANAGER(ManAction);

wxWindow* ManAction::newEditWindow(wxWindow* parent)
{
	return new WinManAction(parent);
}

void ManAction::manLoad(wxFileConfig&)
{
}

void ManAction::manSave(wxFileConfig&)const
{
}									
									
// *****************************************************************************
// Class WinManAction
// *****************************************************************************

WinManAction::WinManAction(wxWindow* parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _("Actions"))
{
	//Creation de la liste.
	_controlDataList = new ControlDataList(this);
	
	//Ajout des colonnes.
	_controlDataList->AppendTextColumn(
							_("Shortcut"),
							wxDATAVIEW_CELL_EDITABLE,
							100,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
										
	_controlDataList->AppendTextColumn(
							_("Action name"),
							wxDATAVIEW_CELL_INERT,
							120,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
							
	_controlDataList->AppendTextColumn(
							_("Short description"),
							wxDATAVIEW_CELL_INERT,
							-1,
							wxALIGN_LEFT,
							wxDATAVIEW_COL_RESIZABLE);
							
	//Remplissage de la liste.(TMP)
	wxVector<wxVariant> data;
	data.push_back( wxVariant("ctrl+c") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_controlDataList->AppendItem( data );
	
	//Créations du menu.
	_controlDataList->addMenuItem(	wxID_ADD);
	_controlDataList->addMenuItem(	wxID_PREFERENCES,	
									wxEmptyString,
									ENABLE_SELECTING_ONE_ITEM);
	_controlDataList->addMenuItem(	wxID_FIND);
	_controlDataList->addMenuItem(	wxID_DELETE,
									wxEmptyString,
									ENABLE_SELECTING_ITEMS);
	_controlDataList->addMenuItemSeparator();
	_controlDataList->addMenuItem(	wxID_ANY,
									_("Change the shortcut"),
									ENABLE_SELECTING_ONE_ITEM);
	
	//Créations des boutons.
	wxButton* buttonDelete = 		new wxButton(this, wxID_DELETE);
	wxButton* buttonPreferences = 	new wxButton(this, wxID_PREFERENCES);
	wxButton* buttonAdd = 			new wxButton(this, wxID_ADD);
	
	//Ajout des bouton au ControlDataList pour qu'il s'occupe d'activer ou pas
	//les boutons en fonction de la sélection.
	_controlDataList->addWindowEnable(	buttonDelete,
										ENABLE_SELECTING_ITEMS);
	_controlDataList->addWindowEnable(	buttonPreferences,
										ENABLE_SELECTING_ONE_ITEM);
	//_controlDataList->addWindowEnable(	buttonAdd,
	//										ENABLE_ANYTIME);

	//Mise en forme des boutons avec un sizer.
	wxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(buttonDelete,	 		0, wxEXPAND);
	buttonsSizer->AddStretchSpacer(1);
	buttonsSizer->Add(buttonPreferences, 	0, wxEXPAND);
	buttonsSizer->Add(buttonAdd, 			0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(_controlDataList, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);
	mainSizer->Add(buttonsSizer, 	 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 4);	
	SetSizer(mainSizer);
}

WinManAction::~WinManAction()
{
}
