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
#include <wx/intl.h>

// *****************************************************************************
// Class ManAction
// *****************************************************************************

ManAction::ManAction()
: _shortcut(this)
{
	Bind(EVT_SHORTCUT, &ManAction::onShortcut, this);
	
	add(ShortcutKey::stringToShortcutKey("shift+super+a"), Action::createAction("ActTranslationToNotification"));
	add(ShortcutKey::stringToShortcutKey("shift+super+b"), Action::createAction("ActTranslationToList"));
}

ManAction::~ManAction()
{
	Unbind(EVT_SHORTCUT, &ManAction::onShortcut, this);
	
	removeAll();
}

IMPLEMENT_MANAGER(ManAction);

WinManager* ManAction::newEditWindow(wxWindow* parent)
{
	return new WinManAction(parent);
}

bool ManAction::add(ShortcutKey const &shortcut, Action* act)
{
	if(exist(shortcut))
		return false;
		
	_shortcutKeyAction[shortcut] = act;
	_shortcut.creat(shortcut);
	
	return true;
}

bool ManAction::exist(ShortcutKey const& shortcut)
{
	for(auto it: _shortcutKeyAction)
	{
		if(it.first == shortcut)
			return true;
	}
	
	return false;
}

bool ManAction::remove(ShortcutKey const& shortcut)
{
	if(!exist(shortcut))
		return false;
		
	delete _shortcutKeyAction[shortcut];
	_shortcutKeyAction.erase(shortcut);
	
	_shortcut.remove(shortcut);
	
	return true;
}

void ManAction::removeAll()
{
	for(auto it: _shortcutKeyAction)
		delete it.second;
		
	_shortcutKeyAction.clear();
	_shortcut.removeAll();
}

void ManAction::enableShortcuts(bool val)
{
	_shortcut.enable(val);
}

void ManAction::manLoad(wxFileConfig&)
{
}

void ManAction::manSave(wxFileConfig&)const
{
}	

void ManAction::onShortcut(ShortcutEvent& event)
{
	_shortcutKeyAction.at(event.getShortcutKey())->execute();
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

void WinManAction::onPreferences(wxCommandEvent&)
{	
}
