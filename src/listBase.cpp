//! \file **************************************************************
//! \brief Source ListBase
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 17.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "listBase.hpp"

// *********************************************************************
// Class ListBase
// *********************************************************************

ListBase::ListBase()
{
}

ListBase::~ListBase()
{
}

void ListBase::getLanguages(wxString* lgsrc, wxString* lgto)const
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

bool ListBase::setLanguages(wxString const& lgsrc, wxString const& lgto)
{
	if(!isEmpty())
		return false;
		
	_lgsrc = lgsrc;
	_lgto = lgto;
	
	return true;
}

bool ListBase::isEmpty()const
{
	if(_fileName.HasName())
		return isEmptyFile();
	else
		return isEmptyMemory();
	
	return false;
}

void ListBase::clear()
{
	_fileName.Clear();
	_lgsrc.Clear();
	_lgto.Clear();
	
	if(_fileName.HasName())
		clearFile();
	else
		clearMemory();
}

bool ListBase::removeText(wxString const& text)
{
	if(_fileName.HasName())
		return removeTextFile(text);
	else
		return removeTextMemory(text);
	
	return false;
}

bool ListBase::existText(wxString const& text)const
{
	if(_fileName.HasName())
		return existTextFile(text);
	else
		return existTextMemory(text);
	
	return false;
}

bool ListBase::load(wxFileName const& fileName)
{		
	if(_fileName.HasName())
	{
		if(fileName == _fileName)
			return true;
			
		return loadFile(fileName);
	}
	else
		return loadMemory(fileName);
	
	return false;
}

bool ListBase::save(wxFileName const& fileName)const
{		
	if(_fileName.HasName())
	{
		if(fileName == _fileName)
			return true;
			
		return saveFile(fileName);
	}
	else
		return saveMemory(fileName);
	
	return false;
}

wxFileName ListBase::getFileName()const
{
	return _fileName;
}

void ListBase::setFileName(wxFileName const& fileName)
{
	_lgsrc.Clear();
	_lgto.Clear();
	_fileName = fileName;
}
