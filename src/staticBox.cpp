//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.01.2014
//!
//! ****************************************************************************

//App
#include "staticBox.hpp"

// *****************************************************************************
// Class StaticBox
// *****************************************************************************

StaticBox::StaticBox(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxControl(parent, id, pos, size, style, name) 
{
	SetLabelMarkup("<b>"+label+"</b>");
}

StaticBox::~StaticBox()
{
}

