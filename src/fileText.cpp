//! \file **********************************************************************
//! \brief Source FileTextFileText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 17.11.2013
//!
//! ****************************************************************************

//App
#include "fileText.hpp"

// *****************************************************************************
// Class FileText
// *****************************************************************************

FileText::FileText()
{
}

FileText::~FileText()
{
}

Status_e FileText::getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
	
	Status_e valReturn = STATUS_SUCCESS;
	
	wxString lg;
	valReturn = readStringInFile(file, &lg);
	if(valReturn == STATUS_SUCCESS)
	{
		*lgsrc = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
		
		valReturn = readStringInFile(file, &lg);
		if(valReturn == STATUS_SUCCESS)
			*lgto = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
	}
		
	file.Close();
	return valReturn;
}

Status_e FileText::setLanguages(wxLanguage lgsrc, wxLanguage lgto)
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	Status_e valReturn = STATUS_SUCCESS;
	
	//On vérifie si la liste est vide
	valReturn = isEmpty();
	if(valReturn != STATUS_EMPTY)
		return valReturn;
		
	
	wxFile file;
	//On crées un nouveau fichier, en écrasant
	//au préalable l'ancien.
	if(!file.Create(_fileName.GetFullPath(), true))
		valReturn = STATUS_FILE_CREATE_FAILED;
	else
	{
		//Écriture du langage source.
		valReturn = writeStringInFile(file, wxLocale::GetLanguageName(lgsrc));
		//Si ok. Écriture de l'autre langage.
		if(valReturn == STATUS_SUCCESS)
			valReturn = writeStringInFile(file, wxLocale::GetLanguageName(lgto));
	}
		
	file.Close();
	return valReturn;
}

Status_e FileText::isOk()const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
		
	file.Close();
	
	return STATUS_OK;
}

Status_e FileText::isEmpty()const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	if(!_fileName.FileExists())
		return STATUS_EMPTY;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
		
	//Positionne le curseur Après les langages.
	Status_e valReturn = filePointerAfterHeader(file);
	if(valReturn == STATUS_SUCCESS)
	{
		if(file.Eof())
			valReturn = STATUS_EMPTY;
		else
			valReturn = STATUS_NO_EMPTY;
	}
		
	file.Close();
	return valReturn;
}

Status_e FileText::clear()
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	if(!wxRemoveFile(_fileName.GetFullPath()))
		return STATUS_FILE_NO_REMOVE;
		
	_fileName.Clear();
		
	return STATUS_SUCCESS;
}

wxFileName FileText::getFileName()const
{
	return _fileName;
}

void FileText::setFileName(wxFileName const& fileName)
{
	_fileName = fileName;
}

Status_e FileText::filePointerAfterHeader(wxFile& file)const
{
	uint8_t sizelg;
	
	//Lecture de la taille du premier langage.
	if(file.Read(&sizelg, sizeof sizelg) != sizeof sizelg)
		return STATUS_FILE_READ_ERROR;
		
	//Pointer sur la taille du deuxième langage.
	if(file.Seek(sizelg, wxFromCurrent) ==  wxInvalidOffset)
		return STATUS_FILE_READ_ERROR;
	
	//Lecture de la taille du deuxième langage.
	if(file.Read(&sizelg, sizeof sizelg) != sizeof sizelg)
		return STATUS_FILE_READ_ERROR;
		
	//Pointer sur la taille du premier texte ou la fin du fichier
	file.Seek(sizelg, wxFromCurrent);
	
	return STATUS_SUCCESS;
}

Status_e FileText::readStringInFile(wxFile& file, wxString* str)const
{
	uint8_t sizeStr;
	
	//Lecture de la taille du texte.
	if(file.Read(&sizeStr, sizeof sizeStr) != sizeof sizeStr)
		return STATUS_FILE_READ_ERROR;
	
	//Lecture du texte.
	wxMemoryBuffer buffer;
	if(file.Read(buffer.GetWriteBuf(sizeStr), sizeStr) != sizeStr)
		return STATUS_FILE_READ_ERROR;
	buffer.UngetWriteBuf(sizeStr);
		
	str->Clear();
	str->Append(wxString::FromUTF8Unchecked((const char *)buffer.GetData(), buffer.GetDataLen()));
	
	return STATUS_SUCCESS;
}

Status_e FileText::writeStringInFile(wxFile& file, wxString const& str)
{
	uint8_t sizeStr = strlen(str.fn_str());
	
	//Écriture de la taille du texte.
	if(file.Write(&sizeStr, sizeof sizeStr) != sizeof sizeStr)
		return STATUS_FILE_WRITE_ERROR;
	
	//Écriture du texte.
	if(!file.Write(str))
		return STATUS_FILE_WRITE_ERROR;
	
	return STATUS_SUCCESS;
}
