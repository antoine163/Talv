//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "list.hpp"
#include <wx/buffer.h>

// *********************************************************************
// Class List
// *********************************************************************

List::List()
{
}

List::~List()
{
}

Status_e List::getLanguages(wxString* lgsrc, wxString* lgto)const
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
	
	Status_e valReturn = SUCCESS;
	
	//Lecture du langage source.
	valReturn = readInFile(file, lgsrc);
	
	//Si ok. Lecture de l'autre langage.
	if(valReturn == SUCCESS)
		valReturn = readInFile(file, lgto);
		
	file.Close();
	return valReturn;
}

Status_e List::setLanguages(wxString const& lgsrc, wxString const& lgto)
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	Status_e valReturn = SUCCESS;
	
	//On vérifie si la liste est vide
	valReturn = isEmpty();
	if(valReturn != LIST_EMPTY)
		return valReturn;
		
	
	wxFile file;
	//On crées un nouveau fichier avec les l'engages, en écrasant
	//au préalable l'ancien.
	if(!file.Create(_fileName.GetFullPath(), true))
		valReturn = FILE_CREATE_FAILED;
	else
	{
		//Écriture du langage source.
		valReturn = writeInFile(file, lgsrc);
		//Si ok. Écriture de l'autre langage.
		if(valReturn == SUCCESS)
			valReturn = writeInFile(file, lgto);
	}
		
	file.Close();
	return valReturn;
}

Status_e List::isEmpty()const
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	if(!_fileName.FileExists())
		return LIST_EMPTY;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
		
	//Positionne le curseur Après les langages.
	Status_e valReturn = filePointerAfterHeader(file);
	if(valReturn == SUCCESS)
	{
		if(file.Eof())
			valReturn = LIST_EMPTY;
		else
			valReturn = LIST_NO_EMPTY;
	}
		
	file.Close();
	return valReturn;
}

Status_e List::clear()
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	if(!wxRemoveFile(_fileName.GetFullPath()))
		return FILE_NO_REMOVE;
		
	_fileName.Clear();
		
	return SUCCESS;
}

Status_e List::addText(wxString const& text)
{
	Status_e valReturn = existText(text);
	
	if(valReturn == TEXT_EXIST)
		return valReturn;
	
	wxArrayString texts;
	texts.Add(text);
	return addTexts(texts);
}

Status_e List::replaceTexts(wxArrayString const& texts)
{
	wxString lgsrc;
	wxString lgto;
	Status_e valReturn = getLanguages(&lgsrc, &lgto);
	if(valReturn != SUCCESS)
		return valReturn;
		
	wxFileName tmpFileName = _fileName;
	
	valReturn = clear();
	if(valReturn != SUCCESS)
		return valReturn;
	
	_fileName = tmpFileName;
	
	valReturn = setLanguages(lgsrc, lgto);
	if(valReturn != SUCCESS)
		return valReturn;
	
	return addTexts(texts);
}

Status_e List::getTexts(wxArrayString* texts)const
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
		
	Status_e valReturn = filePointerAfterHeader(file);
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier.
	wxString tmpStr;
	while(valReturn == SUCCESS && !file.Eof())
	{
		valReturn = readInFile(file, &tmpStr);
		texts->Add(tmpStr);
	}
		
	file.Close();
	return valReturn;
}

Status_e List::existText(wxString const& text)const
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return FILE_OPEN_FAILED;
		
	Status_e valReturn = filePointerAfterHeader(file);
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier ou que l'on a pas trouver
	//le texte rechercher.
	wxString tmpStr;
	while(valReturn == SUCCESS && !file.Eof())
	{
		valReturn = readInFile(file, &tmpStr);
		
		if(valReturn == SUCCESS && tmpStr == text)
			valReturn = TEXT_EXIST;
	}
	
	//Si valReturn == SUCCESS le texte n'a pas été trouver.
	if(valReturn == SUCCESS)
		valReturn = TEXT_NO_EXIST;
		
	file.Close();
	return valReturn;
}

Status_e List::removeText(wxString const& text)
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read_write))
		return FILE_OPEN_FAILED;
		
	Status_e valReturn = filePointerAfterHeader(file);
	wxString tmpStr;
	wxFileOffset fileOffsetLastText = wxInvalidOffset;
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier ou que l'on a pas trouver
	//le texte rechercher.
	while(valReturn == SUCCESS && !file.Eof())
	{
		fileOffsetLastText = file.Tell();
		valReturn = readInFile(file, &tmpStr);
		
		if(valReturn == SUCCESS && tmpStr == text)
			valReturn = TEXT_EXIST;
	}
	
	//Si valReturn == SUCCESS le texte n'a pas été trouver car le curseur
	//est a la fin du fichier.
	if(valReturn == SUCCESS)
		valReturn = TEXT_NO_EXIST;
	else
	{
		wxMemoryBuffer topFile;
		wxMemoryBuffer bottomFile;
		size_t sizeRead;
		
		//Mis en buffer du bas du fichier
		sizeRead = file.Length() - file.Tell();
		if((size_t)file.Read(bottomFile.GetWriteBuf(sizeRead), sizeRead) != sizeRead)
		{
			file.Close();
			return FILE_READ_ERROR;
		}
		bottomFile.UngetWriteBuf(sizeRead);
		
		//Mis en buffer du haut du fichier
		sizeRead = fileOffsetLastText;
		file.Seek(0);
		if((size_t)file.Read(topFile.GetWriteBuf(sizeRead), sizeRead) != sizeRead)
		{
			file.Close();
			return FILE_READ_ERROR;
		}
		topFile.UngetWriteBuf(sizeRead);

		//On ferme le fichier et on en crée un nouveau.
		file.Close();
		if(!file.Create(_fileName.GetFullPath(), true))
			valReturn = FILE_CREATE_FAILED;
		else
		{
			//On écris les données précédemment lu (mais bien sur sen le
			//texte que le doit supprimer)
			
			size_t sizeWrite = topFile.GetDataLen();
			if(file.Write(topFile.GetData(), sizeWrite) != sizeWrite)
			{
				file.Close();
				return FILE_WRITE_ERROR;
			}
			
			sizeWrite = bottomFile.GetDataLen();
			if(file.Write(bottomFile.GetData(), sizeWrite) != sizeWrite)
			{
				file.Close();
				return FILE_WRITE_ERROR;
			}
			valReturn = SUCCESS;
		}
	}
		
	file.Close();
	return valReturn;
}

wxFileName List::getFileName()const
{
	return _fileName;
}

void List::setFileName(wxFileName const& fileName)
{
	_fileName = fileName;
}

Status_e List::readInFile(wxFile& file, wxString* str)const
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
	str->Append(wxString::FromUTF8((const char *)buffer.GetData(), buffer.GetDataLen()));
	
	return SUCCESS;
}

Status_e List::writeInFile(wxFile& file, wxString const& str)
{
	uint8_t sizeStr = str.Length();
	
	//Écriture de la taille du texte.
	if(file.Write(&sizeStr, sizeof sizeStr) != sizeof sizeStr)
		return FILE_WRITE_ERROR;
	
	//Écriture du texte.
	if(!file.Write(str))
		return FILE_WRITE_ERROR;
	
	return SUCCESS;
}

Status_e List::filePointerAfterHeader(wxFile& file)const
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

Status_e List::addTexts(wxArrayString const& texts)
{
	if(!_fileName.HasName())
		return FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::write_append))
		return FILE_OPEN_FAILED;
		
	Status_e valReturn = SUCCESS;
	for(auto& it: texts)
	{
		valReturn = writeInFile(file, it);
		if(valReturn != SUCCESS)
			break;
	}
		
	file.Close();
	return valReturn;
}
