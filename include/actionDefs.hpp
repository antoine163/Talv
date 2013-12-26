//! \file **********************************************************************
//! \brief Header incluent tout les actions 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 01.12.2013
//!
//! ****************************************************************************


#ifndef ACTION_DEF_H
#define ACTION_DEF_H

#include "action/actTranslationToNotification.hpp"
#include "action/actTranslationToList.hpp"

#define MAKE_CREATE_ACTION()	CREATE_ACTION(ActTranslationToNotification)	\
								CREATE_ACTION(ActTranslationToList)


#endif //ACTION_DEF_H
