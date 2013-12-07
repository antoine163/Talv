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
#include "manager/manAction.hpp"	
#include "manager/manList.hpp"	
#include "manager/manNotification.hpp"	
#include "manager/manTts.hpp"
#include "manager/manNetwork.hpp"	
		
		
#define MAKE_CREATE_MANAGERS()	CREATE_MANAGER(ManGeneral)		\
								CREATE_MANAGER(ManAction)		\
								CREATE_MANAGER(ManList)			\
								CREATE_MANAGER(ManNotification)	\
								CREATE_MANAGER(ManTts)			\
								CREATE_MANAGER(ManNetwork)
								

#define MAKE_KILL_MANAGERS()	KILL_MANAGER(ManGeneral)		\
								KILL_MANAGER(ManAction)			\
								KILL_MANAGER(ManList)			\
								KILL_MANAGER(ManNotification)	\
								KILL_MANAGER(ManTts)			\
								KILL_MANAGER(ManNetwork)

#endif //MANAGER_DEF_H
