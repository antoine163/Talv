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
#include "manager/manCache.hpp"
#include "cache.hpp"

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

IMPLEMENT_TRANSLATOR(TrlCache,
					_("Cache"),
					_("Translation a text from the caches files. (work without network).\n"
					"This is a particular translator.\n"
					"Because the words you did never translated with a author translator,\n"
					"can't will be translate by this translator."), wxEmptyString);

void TrlCache::getTranslations(	DataText* translations,
								wxString const& text,
								wxLanguage lgsrc,
								wxLanguage lgto)
{
	//Si le cache n'existe on fait rien.
	if(!ManCache::get().existCache(lgsrc, lgto))
		return;
					
	Cache cache = ManCache::get().getCache(lgsrc, lgto);
	cache.getData(text, translations);
}
