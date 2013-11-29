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
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
	
	Status_e valReturn = SUCCESS;
	
	//Lecture du langage source.
	valReturn = readStringInFile(file, lgsrc);
	
	//Si ok. Lecture de l'autre langage.
	if(valReturn == SUCCESS)
		valReturn = readStringInFile(file, lgto);
		
	file.Close();
	return valReturn;
}

Status_e ListBase::setLanguages(wxString const& lgsrc, wxString const& lgto)
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	Status_e valReturn = SUCCESS;
	
	//On vérifie si la liste est vide
	valReturn = isEmpty();
	if(valReturn != EMPTY)
		return valReturn;
		
	
	wxFile file;
	//On crées un nouveau fichier, en écrasant
	//au préalable l'ancien.
	if(!file.Create(_fileName.GetFullPath(), true))
		valReturn = FILE_CREATE_FAILED;
	else
	{
		//Écriture du langage source.
		valReturn = writeStringInFile(file, lgsrc);
		//Si ok. Écriture de l'autre langage.
		if(valReturn == SUCCESS)
			valReturn = writeStringInFile(file, lgto);
	}
		
	file.Close();
	return valReturn;
}

Status_e ListBase::isEmpty()const
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	if(!_fileName.FileExists())
		return EMPTY;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
		
	//Positionne le curseur Après les langages.
	Status_e valReturn = filePointerAfterHeader(file);
	if(valReturn == SUCCESS)
	{
		if(file.Eof())
			valReturn = EMPTY;
		else
			valReturn = NO_EMPTY;
	}
		
	file.Close();
	return valReturn;
}

Status_e ListBase::clear()
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	if(!wxRemoveFile(_fileName.GetFullPath()))
		return FILE_NO_REMOVE;
		
	_fileName.Clear();
		
	return SUCCESS;
}

wxFileName ListBase::getFileName()const
{
	return _fileName;
}

void ListBase::setFileName(wxFileName const& fileName)
{
	_fileName = fileName;
}

Status_e ListBase::filePointerAfterHeader(wxFile& file)const
{
	uint8_t sizelg;
	
	//Lecture de la taille du premier langage.
	if(file.Read(&sizelg, sizeof sizelg) != sizeof sizelg)
		return FILE_READ_ERROR;
		
	//Pointer sur la taille du deuxième langage.
	if(file.Seek(sizelg, wxFromCurrent) ==  wxInvalidOffset)
		return FILE_READ_ERROR;
	
	//Lecture de la taille du deuxième langage.
	if(file.Read(&sizelg, sizeof sizelg) != sizeof sizelg)
		return FILE_READ_ERROR;
		
	//Pointer sur la taille du premier texte ou la fin du fichier
	file.Seek(sizelg, wxFromCurrent);
	
	return SUCCESS;
}

Status_e ListBase::readStringInFile(wxFile& file, wxString* str)const
{
	uint8_t sizeStr;
	
	//Lecture de la taille du texte.
	if(file.Read(&sizeStr, sizeof sizeStr) != sizeof sizeStr)
		return FILE_READ_ERROR;
	
	//Lecture du texte.
	wxMemoryBuffer buffer;
	if(file.Read(buffer.GetWriteBuf(sizeStr), sizeStr) != sizeStr)
		return FILE_READ_ERROR;
	buffer.UngetWriteBuf(sizeStr);
		
	str->Clear();
	str->Append(wxString::FromUTF8Unchecked((const char *)buffer.GetData(), buffer.GetDataLen()));
	
	return SUCCESS;
}

Status_e ListBase::writeStringInFile(wxFile& file, wxString const& str)
{
	uint8_t sizeStr = strlen(str.fn_str());
	
	//Écriture de la taille du texte.
	if(file.Write(&sizeStr, sizeof sizeStr) != sizeof sizeStr)
		return FILE_WRITE_ERROR;
	
	//Écriture du texte.
	if(!file.Write(str))
		return FILE_WRITE_ERROR;
	
	return SUCCESS;
}
