//! \file **********************************************************************
//! \brief Header définition et configuration des managers.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.12.2013
//!
//! ****************************************************************************

#ifndef MANAGER_DEF_H
#define MANAGER_DEF_H

//Header de tous les manager utiliser dans l'application.
#include "manager/manGeneral.hpp"	
		
		
#define MAKE_CREATE_MANAGERS()	CREATE_MANAGER(ManGeneral)

#define MAKE_KILL_MANAGERS()	KILL_MANAGER(ManGeneral)

#endif //MANAGER_DEF_H
