//! \file **********************************************************************
//! \brief Source ManCache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 19.11.2013
//!
//! ****************************************************************************

//App
#include "manager/manCache.hpp"


// *****************************************************************************
// Class ManCache
// *****************************************************************************

ManCache::ManCache()
: _workInTmp(false)
{
}

ManCache::~ManCache()
{
}

IMPLEMENT_MANAGER(ManCache);

WinManager* ManCache::newEditWindow(wxWindow* parent)
{
	return nullptr;
}

Cache ManCache::getCache(wxLanguage const& lgsrc, wxLanguage const& lgto)
{
}

Cache ManCache::getCache(wxString const& name)
{
}

wxArrayString ManCache::getNameCaches()const
{
}

void ManCache::workToTmp(bool toTmp, bool apply)
{
}

void ManCache::manLoad(wxFileConfig&)
{
}

void ManCache::manSave(wxFileConfig&)const
{
}