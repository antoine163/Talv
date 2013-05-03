//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "list.hpp"

// *********************************************************************
// Class List
// *********************************************************************

List::List(wxString const& name)
{
}

List::~List()
{
}

wxString const& List::getName()const
{
	return "test";
}

int List::save(	wxString text,
				wxString mainTranslate)
{
	return -1;
}
			
int List::save(	wxString text,
				wxString mainTranslate,
				std::map<wxString, wxArrayString> const& translations)
{
	return -1;
}

bool List::exist(wxString text)
{
	return true;
}

bool List::existInFileSystem(wxString const& name)
{
	return false;
}
