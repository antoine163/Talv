//! \file **************************************************************
//! \brief Source Dialogue générale des préférences.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.12
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dialogPreferences.hpp"
#include "editableByPanel.hpp"

#include <wx/stdpaths.h>

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
	//On ouvre le fichier de config.
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
	fileConfig.DeleteAll();
	
	for(auto it : EditableByPanelManager::getInstance()->getEditableByPanel())
	{		
		it->panelApply();
		it->panelSave(fileConfig);
	}
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
		
