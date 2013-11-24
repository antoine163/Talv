//! \file **************************************************************
//! \brief Source ListBase
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
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

Status_e ListBase::getLanguages(wxString* lgsrc, wxString* lgto)const
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

Status_e ListBase::setLanguages(wxString const& lgsrc, wxString const& lgto)
{
	if(!isEmpty())
		return false;
		
	_lgsrc = lgsrc;
	_lgto = lgto;
	
	return true;
}

Status_e ListBase::isEmpty()const
{
	if(_fileName.HasName())
		return isEmptyFile();
	else
		return isEmptyMemory();
	
	return false;
}

Status_e ListBase::clear()
{
	_fileName.Clear();
	_lgsrc.Clear();
	_lgto.Clear();
	
	if(_fileName.HasName())
		clearFile();
	else
		clearMemory();
}

Status_e ListBase::removeText(wxString const& text)
{
	if(_fileName.HasName())
		return removeTextFile(text);
	else
		return removeTextMemory(text);
	
	return false;
}

Status_e ListBase::existText(wxString const& text)const
{
	if(_fileName.HasName())
		return existTextFile(text);
	else
		return existTextMemory(text);
	
	return false;
}

Status_e ListBase::load(wxFileName const& fileName)
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

Status_e ListBase::save(wxFileName const& fileName)const
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

Status_e ListBase::setFileName(wxFileName const& fileName)
{
	_lgsrc.Clear();
	_lgto.Clear();
	_fileName = fileName;
	
	if(_fileName.HasName())
	{
		wxFile file;
		
		//Le fichier existe déjà ?
		if(_fileName.FileExists())
		{
			//On charge les langes.
			if(!file.Open(fileName.GetFullPath(), wxFile::write))
			return false;
		
			//Écriture des langes.
			file.Write(lgsrc+' '+lgto);
			
			//Écriture des textes.
			for(auto it: texts)
				file.Write("\n"+it);
				
			file.Close();
		}
		else
		{
		}
	}
}
