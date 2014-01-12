//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.01.2014
//!
//! ****************************************************************************

//App
#include "translator.hpp"

//WxWidgets
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/sizer.h>

#define CREATE_TRANSLATOR(translator)				\
			ptrTranslators.push_back(new translator());
#include "translatorDefs.hpp"

// *****************************************************************************
// Class Translator
// *****************************************************************************

Translator::Translator()
{
}

Translator::~Translator()
{
}

std::vector<Translator*> Translator::createAllTranslators()
{
	std::vector<Translator*> ptrTranslators;
	MAKE_CREATE_TRANSLATOR();
	return ptrTranslators;
}
