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

#ifndef DLG_IMPORT_H
#define DLG_IMPORT_H

//App
#include "dialogInlay.hpp"

//WxWidgets

// *****************************************************************************
// Class DlgImport
// *****************************************************************************

class DlgImport : public DialogInlay 
{
	public:
		//! \brief Constructeur.
		DlgImport(wxWindow* parent);
		//! \brief Destructeur.
		~DlgImport();
		
	private:
};

#endif //DLG_IMPORT_H
