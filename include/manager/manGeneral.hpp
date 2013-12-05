//! \file **********************************************************************
//! \brief Header ManGeneral
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

#ifndef MAN_GENERAL_H
#define MAN_GENERAL_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

//! \ingroup managers
//! \brief ManGeneral
class ManGeneral : public Manager
{
	DECLARE_MANAGER(ManGeneral);
	
	public:	
		//virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_GENERAL_H
