//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

//App

//WxWidgets

// *****************************************************************************
// Class DlgExport
// *****************************************************************************

DlgExport::DlgExport(wxWindow* parent, std::vector<List> const& lists)
: DialogInlay(parent, _("Export lists"))
{	
}

DlgExport::~DlgExport()
{	
}
