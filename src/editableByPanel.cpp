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
	_panel = nullptr;
}

EditableByPanel::~EditableByPanel()
{
	if(_panel)
		delete _panel;
}

void EditableByPanel::closeEditPanel()
{
	if(_panel)
		delete _panel;
		
	_panel = nullptr;
}

const wxString& EditableByPanel::getName()const
{
	return _name;
}
