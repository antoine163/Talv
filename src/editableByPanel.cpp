//! \file **************************************************************
//! \brief Source editableByPanel.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 25.09.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "editableByPanel.hpp"

// *********************************************************************
// Class EditableByPanel
// *********************************************************************

//! \todo faire un truc pour s'abonnées au préférence
//! et qui n'y a pas besoin de faire autre chose pour voir le panel
//! dans les préférence...
EditableByPanel::EditableByPanel(wxString const& name)
: _name(name)
{
	EditableByPanelManager::getInstance()->add(this);
}

EditableByPanel::~EditableByPanel()
{	
	EditableByPanelManager::getInstance()->remove(this);
}

const wxString& EditableByPanel::getName()const
{
	return _name;
}

// *********************************************************************
// Class EditableByPanelManager
// *********************************************************************

EditableByPanelManager::EditableByPanelManager()
{
}
	
EditableByPanelManager::~EditableByPanelManager()
{
}

std::vector<EditableByPanel*> const& EditableByPanelManager::getEditableByPanel()
{
	return _iAll;
}

void EditableByPanelManager::add(EditableByPanel* val)
{
	_iAll.push_back(val);
}

void EditableByPanelManager::remove(EditableByPanel* val)
{
	for(size_t i = 0; i < _iAll.size(); i++)
	{
		if(_iAll[i] == val)
		{
			_iAll.erase(_iAll.begin()+i);
			break;
		}
	}
}
