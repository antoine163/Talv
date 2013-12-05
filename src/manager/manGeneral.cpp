//! \file **********************************************************************
//! \brief Source ManGeneral
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

//App
#include "manager/manGeneral.hpp"


// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

ManGeneral::ManGeneral()
{
}

ManGeneral::~ManGeneral()
{
}

IMPLEMENT_MANAGER(ManGeneral);

void ManGeneral::manLoad(wxFileConfig&)
{
}

void ManGeneral::manSave(wxFileConfig&)const
{
}
		