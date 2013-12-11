//! \file **********************************************************************
//! \brief Header Gestion de tts (text to speech)
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.12.2013
//!
//! ****************************************************************************

//App
#include "manager/manTts.hpp"

// *****************************************************************************
// Class ManTts
// *****************************************************************************

ManTts::ManTts()
{
}

ManTts::~ManTts()
{
}

IMPLEMENT_MANAGER(ManTts);

WinManager* ManTts::newEditWindow(wxWindow* parent)
{
	//wxWindow* tmp = new wxWindow(parent, _("Text to speech"));
	//return tmp;
	
	return nullptr;
}

void ManTts::manLoad(wxFileConfig&)
{
}

void ManTts::manSave(wxFileConfig&)const
{
}
