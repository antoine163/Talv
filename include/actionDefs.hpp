//! \file **************************************************************
//! \brief Header incluent tout les actions 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.12.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/


#ifndef ACTION_DEF_H
#define ACTION_DEF_H

#include "action/actTranslation.hpp"
#include "action/actTranslationToList.hpp"
#include "action/actLearn.hpp"
#include "action/actSay.hpp"


#ifdef SHOW_ACTION
#define MAKE_SHOW_ACTION()\ 
		SHOW_ACTION(ActTranslation)\
		SHOW_ACTION(ActTranslationToList)\
		SHOW_ACTION(ActSay)\
		SHOW_ACTION(ActLearn)
#endif

#ifdef NEW_ACTION
#define MAKE_NEW_ACTION()\ 
		NEW_ACTION(ActTranslation)\
		NEW_ACTION(ActTranslationToList)\
		NEW_ACTION(ActSay)\
		NEW_ACTION(ActLearn)
#endif


#endif //ACTION_DEF_H
