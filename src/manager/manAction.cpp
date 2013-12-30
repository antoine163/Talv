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
#include "dialog/dlgPickShortcutKey.hpp"
#include "defs.hpp"

//Stl
#include <array>

//WxWidgets
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/msgdlg.h>

// *****************************************************************************
// Class ManAction
// *****************************************************************************

ManAction::ManAction()
: _shortcut(this)
{
	Bind(EVT_SHORTCUT, &ManAction::onShortcut, this);
	
	add(ShortcutKey::stringToShortcutKey("shift+a"), Action::createAction("ActTranslationToNotification"));
	add(ShortcutKey::stringToShortcutKey("shift+b"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+c"), Action::createAction("ActTranslationToNotification"));
	add(ShortcutKey::stringToShortcutKey("shift+d"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+e"), Action::createAction("ActTranslationToNotification"));
	add(ShortcutKey::stringToShortcutKey("shift+f"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+g"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+h"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+i"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+j"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+k"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+l"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+m"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+n"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+o"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+p"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+q"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+r"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+s"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+t"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+u"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+v"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+w"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+x"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+y"), Action::createAction("ActTranslationToList"));
	add(ShortcutKey::stringToShortcutKey("shift+z"), Action::createAction("ActTranslationToList"));
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
		
	_shortcutKeysActions[shortcut] = act;
	_shortcut.creat(shortcut);
	
	return true;
}

Action const* ManAction::getAction(ShortcutKey const &shortcut)const
{
	for(auto it: _shortcutKeysActions)
	{
		if(it.first == shortcut)
			return it.second;
	}
	
	return nullptr;
}

bool ManAction::exist(ShortcutKey const& shortcut)
{
	for(auto it: _shortcutKeysActions)
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
		
	delete _shortcutKeysActions[shortcut];
	_shortcutKeysActions.erase(shortcut);
	
	_shortcut.remove(shortcut);
	
	return true;
}

void ManAction::removeAll()
{
	for(auto it: _shortcutKeysActions)
		delete it.second;
		
	_shortcutKeysActions.clear();
	_shortcut.removeAll();
}

void ManAction::shortcutsEnable(bool val)
{
	_shortcut.enable(val);
}

bool ManAction::shortcutsIsEnable()
{
	return _shortcut.isEnable();
}

std::map<ShortcutKey, Action*>const& ManAction::getShortcutKeysActions()const
{
	return _shortcutKeysActions;
}

void ManAction::manLoad(wxFileConfig&)
{
}

void ManAction::manSave(wxFileConfig&)const
{
}	

void ManAction::onShortcut(ShortcutEvent& event)
{
	_shortcutKeysActions.at(event.getShortcutKey())->execute();
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
	
	//Bind
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onAdd, 				this, wxID_ADD);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onPreferences, 		this, wxID_PREFERENCES);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onFind, 				this, wxID_FIND);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onDelete, 			this, wxID_DELETE);
	Bind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onChangeShortcut, 	this, ID_CHANGE_SHORTCUT);
	
	Bind(wxEVT_BUTTON, 					&WinManAction::onDelete, 			this, wxID_DELETE);
	Bind(wxEVT_BUTTON, 					&WinManAction::onPreferences, 		this, wxID_PREFERENCES);
	Bind(wxEVT_BUTTON, 					&WinManAction::onAdd, 				this, wxID_ADD);
	
	
	Bind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED,	&WinManAction::onItemEditingStarted, 	this);
	Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE,		&WinManAction::onItemEditingDone, 		this);
	
	//Accélérateurs
	wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL, 	(int) 'F', 		wxID_FIND);
    entries[1].Set(wxACCEL_NORMAL,	 WXK_DELETE, 	wxID_DELETE);
    wxAcceleratorTable accel(2, entries);
    SetAcceleratorTable(accel);
}

WinManAction::~WinManAction()
{
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onAdd, 				this, wxID_ADD);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onPreferences, 		this, wxID_PREFERENCES);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onFind, 				this, wxID_FIND);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onDelete, 			this, wxID_DELETE);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, 	&WinManAction::onChangeShortcut, 	this, ID_CHANGE_SHORTCUT);

	Unbind(wxEVT_BUTTON, 					&WinManAction::onDelete, 			this, wxID_DELETE);
	Unbind(wxEVT_BUTTON, 					&WinManAction::onPreferences, 		this, wxID_PREFERENCES);
	Unbind(wxEVT_BUTTON, 					&WinManAction::onAdd, 				this, wxID_ADD);
	
	Unbind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED,	&WinManAction::onItemEditingStarted, 	this);
	Unbind(wxEVT_DATAVIEW_ITEM_EDITING_DONE,	&WinManAction::onItemEditingDone, 		this);
}

void WinManAction::refreshGuiFromManager()
{
	//On commence par tout effacer.
	_ctrlDataList->DeleteAllItems();
	
	//Récupération des raccourcis et actions.
	std::map<ShortcutKey, Action*>const& shortcutKeysActions = ManAction::get().getShortcutKeysActions();
	
	wxVector<wxVariant> data;
	for(auto it: shortcutKeysActions)
	{
		data.clear();
		data.push_back(wxVariant(ShortcutKey::shortcutKeyToString(it.first)));
		data.push_back(wxVariant(it.second->getName()));
		data.push_back(wxVariant(it.second->getStringPreferences()));
		_ctrlDataList->AppendItem(data);
	}
}

void WinManAction::refreshManagerFromGui()const
{
	//Pas utile ici puis que le manager et mise a jour en même temps que le gui.
}
#include <iostream>
void WinManAction::onAdd(wxCommandEvent&)
{
	std::cout << "WinManAction::onAdd" << std::endl;
}

void WinManAction::onPreferences(wxCommandEvent&)
{
	std::cout << "WinManAction::onPreferences" << std::endl;
}

void WinManAction::onFind(wxCommandEvent&)
{	
	DlgPickShortcutKey dlg(this, _("Find a shortcut"));
	
	if(dlg.ShowModal() == wxID_OK)
	{
		//On récupère le raccourcie.
		ShortcutKey shortcut = dlg.getShortcutKey();
		
		//Le raccourci n'est pas valide.
		if(!shortcut.isOk())
		{
			wxMessageDialog dlg(this,
				_("You didn't pick a shortcut."),
				_("Shortcut no valid"),
				wxOK|wxICON_INFORMATION|wxCENTRE);
			dlg.ShowModal();
			
			return;
		}
		
		//On cherche le raccourcie
		for(int i = 0; i<_ctrlDataList->GetItemCount(); i++)
		{
			//Si on n'a trouver, on le ren visible.
			if(ShortcutKey::stringToShortcutKey(_ctrlDataList->GetTextValue(i, 0)) == shortcut)		
			{			
				_ctrlDataList->EnsureVisible(_ctrlDataList->RowToItem(i));
				_ctrlDataList->UnselectAll();
				_ctrlDataList->SelectRow(i);
				_ctrlDataList->updateEnableElements();
				return ;
			}	
		}
		
		//On n'a pas trouver le raccourcis.
		wxMessageDialog dlg(this, _("The shortcut didn't find."), _("Shortcut no valid"), wxOK|wxICON_INFORMATION|wxCENTRE);
		dlg.ShowModal();
	}
}

void WinManAction::onDelete(wxCommandEvent&)
{
	wxMessageDialog dlg(this, _("Is you sure to want delete the actions selected?"), _("Delete actions"), wxYES_NO|wxICON_QUESTION|wxCENTRE);
			
	//On doit supprimer Les actions?
	if(dlg.ShowModal() == wxID_YES)//Oui
	{	
		wxDataViewItemArray itemsSelected;
		_ctrlDataList->GetSelections(itemsSelected);
		
		for(auto it: itemsSelected)
		{
			int row = _ctrlDataList->ItemToRow(it);
			ManAction::get().remove(ShortcutKey::stringToShortcutKey(_ctrlDataList->GetTextValue(row, 0)));
			_ctrlDataList->DeleteItem(row);
		}
	}
}

void WinManAction::onChangeShortcut(wxCommandEvent&)
{
	//On récupère le raccourcis sélectionner.
	wxString shortcut = _ctrlDataList->GetTextValue(_ctrlDataList->GetSelectedRow(), 0);
	ShortcutKey oldShortcut = ShortcutKey::stringToShortcutKey(shortcut);
	
	DlgPickShortcutKey dlg(this, _("Pick a new shortcut"), oldShortcut);
	
	if(dlg.ShowModal() == wxID_OK)
	{
		//On récupère le nouveau raccourcie.
		ShortcutKey newShortcut = dlg.getShortcutKey();
		
		//Vérifie si le raccourci est le même que l'ancien, dans se cas on ne fais rien.
		if(newShortcut == oldShortcut)
			return;
		
		//Le raccourci n'est pas valide.
		if(!newShortcut.isOk())
		{
			wxMessageDialog dlg(this,
				_("You didn't pick a shortcut."),
				_("Shortcut no valid"),
				wxOK|wxICON_INFORMATION|wxCENTRE);
			dlg.ShowModal();
			
			return;
		}
		
		changeSelectedShortcut(newShortcut);
	}
}

void WinManAction::onItemEditingStarted(wxDataViewEvent&)
{
	_itemOldShortcut = _ctrlDataList->GetTextValue(_ctrlDataList->GetSelectedRow(), 0);
}

void WinManAction::onItemEditingDone(wxDataViewEvent&)
{
	//On récupère le nouveau raccourcie.
	ShortcutKey newShortcut = ShortcutKey::stringToShortcutKey(_ctrlDataList->GetTextValue(_ctrlDataList->GetSelectedRow(), 0));
	
	//L'ancien raccourcie.
	ShortcutKey oldShortcut = ShortcutKey::stringToShortcutKey(_itemOldShortcut);
	
	//Vérifie si le raccourci est le même que l'ancien, dans se cas on ne fais rien.
	if(newShortcut == oldShortcut)
	{
		_ctrlDataList->SetTextValue(_itemOldShortcut, _ctrlDataList->GetSelectedRow(), 0);
		return;
	}
	
	//Le raccourci n'est pas valide.
	if(!newShortcut.isOk())
	{
		wxMessageDialog dlg(this,
			_("Your shortcut is not valide.\n The shortcut must is a forme: \"mod+key\".\n'mod' can tack the follow value:\n\t\"ctrl\"\n\t\"alt\"\n\t\"shift\"\n\t\"super\"\n\t\"altgr\" (only on unix).\n eg: \"shift+super+f\""),
			_("Shortcut no valid"),
			wxOK|wxICON_INFORMATION|wxCENTRE);
		dlg.ShowModal();
		
		//On remet l'ancien raccourcie.
		_ctrlDataList->SetTextValue(_itemOldShortcut, _ctrlDataList->GetSelectedRow(), 0);
		
		return;
	}
	
	//On change le raccourcie.
	_ctrlDataList->SetTextValue(_itemOldShortcut, _ctrlDataList->GetSelectedRow(), 0);
	changeSelectedShortcut(newShortcut);
}

void WinManAction::changeSelectedShortcut(ShortcutKey newShortcut)
{
	//L'ancien raccourcie.
	ShortcutKey oldShortcut = ShortcutKey::stringToShortcutKey(_ctrlDataList->GetTextValue(_ctrlDataList->GetSelectedRow(), 0));
	
	//Le raccourci est déjà existante ?
	if(ManAction::get().exist(newShortcut))
	{
		wxMessageDialog dlg(this,
			_("Your shortcut is already used.\nYou want delete the other shortcut and the associate actions ?"),
			_("Shortcut already used"),
			wxYES_NO|wxICON_QUESTION|wxCENTRE);
			
		//On doit supprimer l'autre raccourcie ?
		if(dlg.ShowModal() == wxID_YES)//Oui
		{
			ManAction::get().remove(newShortcut);
			
			//On cherche la ligne a supprimer.
			for(int i = 0; i<_ctrlDataList->GetItemCount(); i++)
			{
				//Si on n'a trouver on la supprime.
				if(ShortcutKey::stringToShortcutKey(_ctrlDataList->GetTextValue(i, 0)) == newShortcut && i != _ctrlDataList->GetSelectedRow())		
				{			
					_ctrlDataList->DeleteItem(i);
					break;
				}	
			}
		}
		else //non
			return;
	}
	
	//Enfin on modifie le raccourcie.
	Action* tmpAct = ManAction::get().getAction(oldShortcut)->newClone();
	ManAction::get().remove(oldShortcut);
	ManAction::get().add(newShortcut, tmpAct);
	_ctrlDataList->SetTextValue(ShortcutKey::shortcutKeyToString(newShortcut), _ctrlDataList->GetSelectedRow(), 0);
}

