//! \file **************************************************************
//! \brief Source editableByPanel.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
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
	ManagerEditableByPanel::getInstance()->add(this);
}

EditableByPanel::~EditableByPanel()
{	
	ManagerEditableByPanel::getInstance()->remove(this);
}

const wxString& EditableByPanel::getName()const
{
	return _name;
}

// *********************************************************************
// Class ManagerEditableByPanel
// *********************************************************************

ManagerEditableByPanel::ManagerEditableByPanel()
{
}
	
ManagerEditableByPanel::~ManagerEditableByPanel()
{
}

std::vector<EditableByPanel*> const& ManagerEditableByPanel::getEditableByPanel()
{
	return _iAll;
}

void ManagerEditableByPanel::add(EditableByPanel* val)
{
	_iAll.push_back(val);
}

void ManagerEditableByPanel::remove(EditableByPanel* val)
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
