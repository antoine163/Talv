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

Status_e List::addText(wxString const& text)
{
	Status_e valReturn = existText(text);
	
	if(valReturn != TEXT_NO_EXIST)
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
		valReturn = readStringInFile(file, &tmpStr);
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
		valReturn = readStringInFile(file, &tmpStr);
		
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
		valReturn = readStringInFile(file, &tmpStr);
		
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
		valReturn = writeStringInFile(file, it);
		if(valReturn != SUCCESS)
			break;
	}
		
	file.Close();
	return valReturn;
}
