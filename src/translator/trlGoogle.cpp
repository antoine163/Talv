//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 12.01.2014
//!
//! ***************************************************************************

//App
#include "translator/trlGoogle.hpp"

//WxWidgets
#include <wx/intl.h> 

// *****************************************************************************
// Class TrlGoogle
// *****************************************************************************

TrlGoogle::TrlGoogle()
{
}

TrlGoogle::~TrlGoogle()
{
}

IMPLEMENT_TRANSLATOR(TrlGoogle, _("Google"), _("Translation a text from \"Google Translate.\""), "http://translate.google.com/");

wxString TrlGoogle::getTranslations(std::map<wxString, wxArrayString>* translations,
									wxString const& text,
									wxLanguage lgsrc,
									wxLanguage lgto)
{
	return wxEmptyString;
}

