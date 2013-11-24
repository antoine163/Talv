//! \file **************************************************************
//! \brief Source Cache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 16.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "cache.hpp"

//TEST
#include <iostream>

// *********************************************************************
// Class Cache
// *********************************************************************

Cache::Cache()
{
}

Cache::~Cache()
{
}

bool Cache::isEmptyFile()const
{
}

bool Cache::isEmptyMemory()const
{
}

void Cache::clearFile()
{
}

void Cache::clearMemory()
{
}

bool Cache::removeTextFile(wxString const& text)
{
}

bool Cache::removeTextMemory(wxString const& text)
{
}

bool Cache::existTextFile(wxString const& text)const
{
}

bool Cache::existTextMemory(wxString const& text)const
{
}

bool Cache::loadFile(wxFileName const& fileName)
{
}

bool Cache::loadMemory(wxFileName const& fileName)
{
}

bool saveFile(wxFileName const& fileName)const
{
}

bool saveMemory(wxFileName const& fileName)const
{
}
