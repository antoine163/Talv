//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.1
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "list.hpp"
#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/filefn.h> 

//TEST
#include <iostream>

// *********************************************************************
// Class List
// *********************************************************************

List::List()
{
}

List::~List()
{
}

bool List::addText(wxString const& text)
{
	//Le texte existe déjà ?
	if(existText(text))
		return false;
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		wxFile file;
		if(!file.Open(_fileName.GetFullPath(), wxFile::write_append))
			return false;
			
		file.Write("\n"+text);
		file.Close();
	}
	else
		_texts.Add(text);
	
	return true;
}

wxArrayString List::getTexts()const
{
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		wxArrayString tmpTexts;
		
		//Chargement des textes dans tmpTexts.
		load(_fileName, &tmpTexts);
		
		return tmpTexts;
	}
	else
		return _texts;
	
	return wxArrayString();
}

void List::setFileName(wxFileName const& fileName)
{
	ListBase::setFileName(fileName);
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		//Si le fichier existe on charge les langes.
		if(_fileName.FileExists())
			load(_fileName, nullptr, &_lgsrc, &_lgto);
		//sinon on crée le fichier.
		else
			save(_fileName, wxArrayString(), _lgsrc, _lgto);
	}
	
}

bool List::isEmptyFile()const
{
	wxFile file(_fileName.GetFullPath());
	
	//Si il y a un '\n' cela veux dire que la liste n'est pas vide.
	char tmpc;
	ssize_t n;
	do
	{
		n = file.Read(&tmpc, 1);
		
		if(tmpc == '\n')
			return false;
		
	}while(n != wxInvalidOffset);
		
	file.Close();
	
	return true;
}

bool List::isEmptyMemory()const
{
	return _texts.IsEmpty();
}

void List::clearFile()
{
	wxRemoveFile(_fileName.GetFullPath());
}

void List::clearMemory()
{
	_texts.Clear();
}

bool List::removeTextFile(wxString const& text)
{
	wxArrayString tmpTexts;
	
	//Chargement des textes dans tmpTexts.
	if(!load(_fileName, &tmpTexts))
		return false;
	
	//Suppression du texte si il existe.
	if(!remove(tmpTexts, text))
		return false;
	
	//Sauvegarde des textes dans le fichier.
	if(!save(_fileName, tmpTexts, _lgsrc, _lgto))
		return false;
		
	return true;
}

bool List::removeTextMemory(wxString const& text)
{
	return remove(_texts, text);
}

bool List::existTextFile(wxString const& text)const
{
	wxArrayString tmpTexts;
		
	//Chargement des textes dans tmpTexts.
	load(_fileName, &tmpTexts);
	
	//le texte existe ?
	return exist(tmpTexts, text);
}

bool List::existTextMemory(wxString const& text)const
{
	return exist(_texts, text);
}

bool List::loadFile(wxFileName const& fileName)
{
	//Chargement des langes.
	if(!load(fileName, nullptr, &_lgsrc, &_lgto))
		return false;
	
	//Copie de fichier
	if(!wxCopyFile(fileName.GetFullPath(), _fileName.GetFullPath(), false))
		return false;
		
	return true;
}

bool List::loadMemory(wxFileName const& fileName)
{
	return load(fileName, &_texts, &_lgsrc, &_lgto);
}

bool List::saveFile(wxFileName const& fileName)const
{
	return wxCopyFile(_fileName.GetFullPath(), fileName.GetFullPath());
}

bool List::saveMemory(wxFileName const& fileName)const
{
	return save(fileName, _texts, _lgsrc, _lgto);
}

bool List::load(	wxFileName const& fileName,
					wxArrayString* texts,
					wxString* lgsrc,
					wxString* lgto)const
{
	wxString tmpText;
	
	wxTextFile file;
	if(!file.Open(fileName.GetFullPath()))
		return false;
	
	//Premier ligne c'est la lange de la liste
	tmpText = file.GetFirstLine();
	if(lgsrc != nullptr && lgto != nullptr)
	{
		*lgsrc = tmpText.BeforeFirst(' ');
		*lgto = tmpText.AfterLast(' ');
	}
	
	//Les autres lignes c'est les textes ...
	if(texts != nullptr)
	{
		for(tmpText = file.GetNextLine(); !file.Eof(); tmpText = file.GetNextLine())
			texts->Add(tmpText);
	}
	file.Close();
	
	return true;
}

bool List::save(	wxFileName const& fileName,
					wxArrayString const& texts,
					wxString const& lgsrc,
					wxString const& lgto)const
{
	wxFile file;
	if(!file.Open(fileName.GetFullPath(), wxFile::write))
		return false;
	
	//Écriture des langes.
	file.Write(lgsrc+' '+lgto);
	
	//Écriture des textes.
	for(auto it: texts)
		file.Write("\n"+it);
		
	file.Close();
	
	return true;
}

bool List::exist(wxArrayString const& texts, wxString const& text)const
{
	int index = texts.Index(text, false);
	if(index == wxNOT_FOUND)
		return false;
		
	return true;
}

bool List::remove(wxArrayString& texts, wxString const& text)const
{
	int index = texts.Index(text, false);
	if(index == wxNOT_FOUND)
		return false;
		
	texts.RemoveAt(index);
	
	return true;
}
