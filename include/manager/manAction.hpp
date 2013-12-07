//! \file **********************************************************************
//! \brief Header Gestion des actions/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.0
//! \date 20.03.2013
//!
//! ****************************************************************************

#ifndef MAN_ACTION_H
#define MAN_ACTION_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManAction
// *****************************************************************************

//! \ingroup managers
//! \brief ManAction
class ManAction : public Manager
{
	DECLARE_MANAGER(ManAction);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_ACTION_H
