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
#include "defs.hpp"

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

WinManager* ManAction::newEditWindow(wxWindow* parent)
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
: WinManager(parent, _("Actions"))
{
	//Creation de la liste.
	_ctrlDataList = new CtrlDataList(this);
	
	//Ajout des colonnes.
	_ctrlDataList->AppendTextColumn(_("Shortcut"), 			wxDATAVIEW_CELL_EDITABLE, 	100, 	wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_ctrlDataList->AppendTextColumn(_("Action name"), 		wxDATAVIEW_CELL_INERT, 		120, 	wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE);
	_ctrlDataList->AppendTextColumn(_("Short description"), wxDATAVIEW_CELL_INERT, 		-1, 	wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
							
	//Remplissage de la liste.(TMP)
	wxVector<wxVariant> data;
	data.push_back( wxVariant("ctrl+c") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+v") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+m") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	data.clear();
	data.push_back( wxVariant("ctrl+p") );
	data.push_back( wxVariant("Translate") );
	data.push_back( wxVariant("Translate a text") );
	_ctrlDataList->AppendItem( data );
	
	//Créations du menu.
	_ctrlDataList->addMenuItem(wxID_ADD, 			wxEmptyString, 				ENABLE_ANYTIME);
	_ctrlDataList->addMenuItem(wxID_PREFERENCES, 	wxEmptyString, 				ENABLE_SELECTING_ONE_ITEM);
	_ctrlDataList->addMenuItem(wxID_FIND, 			wxEmptyString, 				ENABLE_ANYTIME);
	_ctrlDataList->addMenuItem(wxID_DELETE, 		wxEmptyString, 				ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addMenuItemSeparator();
	_ctrlDataList->addMenuItem(ID_CHANGE_SHORTCUT, _("Change the shortcut"), 	ENABLE_SELECTING_ONE_ITEM);
	
	//Créations des boutons.
	wxButton* buttonDelete = 		new wxButton(this, wxID_DELETE);
	wxButton* buttonPreferences = 	new wxButton(this, wxID_PREFERENCES);
	wxButton* buttonAdd = 			new wxButton(this, wxID_ADD);
	
	//Ajout des bouton au ControlDataList pour qu'il s'occupe d'activer ou pas
	//les boutons en fonction de la sélection.
	_ctrlDataList->addWindowEnable(		buttonDelete, 		ENABLE_SELECTING_ITEMS);
	_ctrlDataList->addWindowEnable(		buttonPreferences, 	ENABLE_SELECTING_ONE_ITEM);
	_ctrlDataList->addWindowEnable(		buttonAdd, 			ENABLE_ANYTIME);

	//Mise en forme des boutons avec un sizer.
	wxSizer* sizerButtons = new wxBoxSizer(wxHORIZONTAL);
	sizerButtons->Add(buttonDelete,	 		0, wxEXPAND);
	sizerButtons->AddStretchSpacer(1);
	sizerButtons->Add(buttonPreferences, 	0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	sizerButtons->Add(buttonAdd, 			0, wxEXPAND);
	
	//Mise en forme du GUI avec des sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(_ctrlDataList, 	1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	sizerMain->Add(sizerButtons, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(sizerMain);
	
	
	//bind
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onPreferences, this, wxID_PREFERENCES);
	Bind(wxEVT_BUTTON, 					&WinManAction::onPreferences, this, wxID_PREFERENCES);
}

WinManAction::~WinManAction()
{
}

void WinManAction::refreshGuiFromManager()
{
}

void WinManAction::refreshManagerFromGui()const
{
}
#include "manager/manNotification.hpp"
void WinManAction::onPreferences(wxCommandEvent&)
{	
	ManNotification::get().notify("test", "Le message");
	ManNotification::get().notify("test", "Le message", wxICON_ERROR);
	ManNotification::get().notify("test", "Le message", wxICON_INFORMATION);
	ManNotification::get().notify("test", "Le message", wxICON_WARNING);
	std::cout << "WinManAction::onPreferences" << std::endl;
}
