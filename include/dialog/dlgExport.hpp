//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

#ifndef DLG_EXPORT_H
#define DLG_EXPORT_H

//App
#include "dialogInlay.hpp"

//WxWidgets

// *****************************************************************************
// Class DlgExport
// *****************************************************************************

class DlgExport : public DialogInlay 
{
	public:
		//! \brief Constructeur.
		DlgExport(wxWindow* parent, std::vector<List> const& lists);
		//! \brief Destructeur.
		~DlgExport();
		
	private:
};

#endif //DLG_EXPORT_H
