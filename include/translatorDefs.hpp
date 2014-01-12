//! \file **********************************************************************
//! \brief Header définition et configuration des traducteurs.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.01.2014
//!
//! ****************************************************************************

#ifndef TRANSLATOR_DEF_H
#define TRANSLATOR_DEF_H

//Header de tous les traducteurs utiliser dans l'application.
#include "translator/trlCache.hpp"	
#include "translator/trlGoogle.hpp"	
		
		
#define MAKE_CREATE_TRANSLATOR()	CREATE_TRANSLATOR(TrlCache)		\
									CREATE_TRANSLATOR(TrlGoogle)

#endif //TRANSLATOR_DEF_H
