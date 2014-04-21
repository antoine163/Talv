//! \file **********************************************************************
//! \brief Header incluent tout les actions 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.12.2013
//!
//! ****************************************************************************


#ifndef ACTION_DEF_H
#define ACTION_DEF_H

#include "action/actTranslationToNotification.hpp"
#include "action/actTranslationToClipboard.hpp"
#include "action/actTranslationToList.hpp"
#include "action/actTextToSpeech.hpp"
#include "action/actLauncher.hpp"

#define MAKE_CREATE_ACTION()	CREATE_ACTION(ActTranslationToNotification)	\
								CREATE_ACTION(ActTranslationToClipboard)	\
								CREATE_ACTION(ActTranslationToList)			\
								CREATE_ACTION(ActTextToSpeech)				\
								CREATE_ACTION(ActLauncher)


#endif //ACTION_DEF_H
