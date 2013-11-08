//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.11
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogPreferences.hpp"
#include "editableByPanel.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class DialogPreferences
// *********************************************************************

DialogPreferences::DialogPreferences()
: GuiDialogPreferences(nullptr)
{	
	for(auto it : EditableByPanelManager::getInstance()->getEditableByPanel())
	{		
		//Ajout des panels
		wxPanel* panel = it->newEditPanel(_notebook);
		if(panel)
			_notebook->AddPage(panel, it->getName());
	}
}

DialogPreferences::~DialogPreferences()
{
}
 
void DialogPreferences::applyAndSave()
{
	////On ouvre le fichier de config.
	//wxFileConfig fileConfig(	PROJECT_NAME,
								//wxEmptyString,
								//wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
	//fileConfig.DeleteAll();
	
	////Affectation des valeurs dans les ressources.
	//Resource::getInstance()->setShowMenu(_checkBoxShowMenu->GetValue());
	//Resource::getInstance()->setPowerOn(_checkBoxPowerOn->GetValue());
	
	////On sauvegarde les ressources.
	//Resource::getInstance()->save(fileConfig);
	
	////Affectation des paramètres des notifications.
	////! \todo provisoire
	//#ifdef USE_EMULATE_NOTIFICATION	
	//int n = _choiceNotification->GetSelection();
	//wxString nString = _choiceNotification->GetString(n);
	
	//if(nString == _("Top left"))
	//{
		//Notification::getInstance()->setPositionNotification(POSITION_SCREEN_TOP_LEFT);
	//}
	//else if(nString == _("Top right"))
	//{
		//Notification::getInstance()->setPositionNotification(POSITION_SCREEN_TOP_RIGHT);
	//}
	//else if(nString == _("Bottom left"))
	//{
		//Notification::getInstance()->setPositionNotification(POSITION_SCREEN_BOTTOM_LEFT);
	//}
	//else if(nString == _("Bottom right"))
	//{
		//Notification::getInstance()->setPositionNotification(POSITION_SCREEN_BOTTOM_RIGHT);
	//}
	//#endif
	
	////On sauvegarde les paramètres des notifications.
	//Notification::getInstance()->save(fileConfig);
	
	////On sauvegarde EN PREMIER les listes
	//EditListManager::getInstance()->apply();
	//ListManager::getInstance()->save(fileConfig);
	
	////On sauvegarde EN DEUXIÈME les actions
	//EditActionManager::getInstance()->apply();
	//ActionManager::getInstance()->save(fileConfig);
}

void DialogPreferences::OnNotebookPageChanged(wxNotebookEvent& event)
{
	//Mise a jour de la page sélectionner
	_notebook->GetCurrentPage()->Update();
	event.Skip();
}

void DialogPreferences::OnButtonClickOK(wxCommandEvent& event)
{	
	applyAndSave();
	event.Skip();
}

void DialogPreferences::OnButtonClickApply(wxCommandEvent& event)
{
	applyAndSave();
	event.Skip();
}
		
