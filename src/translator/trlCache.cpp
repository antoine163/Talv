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
#include "translator/trlCache.hpp"

//WxWidgets
#include <wx/intl.h> 

// *****************************************************************************
// Class TrlCache
// *****************************************************************************

TrlCache::TrlCache()
{
}

TrlCache::~TrlCache()
{
}

IMPLEMENT_TRANSLATOR(TrlCache, _("Cache"), _("Translation a text from the caches files. (work without network).\nThis is a particular translator. because the words you did never translated with auther translator don"), wxEmptyString);

wxString TrlCache::getTranslations(	std::map<wxString, wxArrayString>* translations,
									wxString const& text,
									wxLanguage lgsrc,
									wxLanguage lgto)
{
	return wxEmptyString;
}

