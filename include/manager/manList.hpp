//! \file **********************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ****************************************************************************

#ifndef MAN_LIST_H
#define MAN_LIST_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup managers
//! \brief ManList
class ManList : public Manager
{
	DECLARE_MANAGER(ManList);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_LIST_H
