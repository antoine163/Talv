//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
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

wxString List::getLanguage()const
{
	return _lg;
}

bool List::setLanguage(wxString const& lg)
{
	if(!isEmpty())
		return false;
		
	//Il y a un nom de fichier.
	if(_fileName.HasName())	
	{
		wxFile file(_fileName.GetFullPath(), wxFile::write);
	
		//Écriture de la lange.
		file.Write(lg);
			
		file.Close();
	}
		
	_lg = lg;
	
	return true;
}

bool List::isEmpty()
{
	//Il y a un nom de fichier.
	if(_fileName.HasName())	
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
	}
	else
		return _texts.IsEmpty();
	
	return true;
}

void List::clear()
{
	//Il y a un nom de fichier.
	if(_fileName.HasName())
		wxRemoveFile(_fileName.GetFullPath());

	_lg.Clear();
	_texts.Clear();
}

bool List::addText(wxString const& text)
{
	//Le texte existe déjà ?
	if(exist(text))
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

bool List::removeText(wxString const& text)
{
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		wxArrayString tmpTexts;
		wxString tmpLg;
		
		//Chargement des textes dans tmpTexts.
		if(!load(_fileName, &tmpTexts, &tmpLg))
			return false;
		
		//Suppression du texte si il existe.
		if(!remove(tmpTexts, text))
			return false;
		
		//Sauvegarde des textes dans le fichier.
		if(!save(_fileName, tmpTexts, tmpLg))
			return false;
	}
	else
	{
		//Suppression du texte si il existe.
		if(!remove(_texts, text))
			return false;
	}
	
	return true;
}

bool List::exist(wxString const& text)
{
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		wxArrayString tmpTexts;
		
		//Chargement des textes dans tmpTexts.
		load(_fileName, &tmpTexts);
		
		//le texte existe ?
		if(exist(tmpTexts, text))
			return true;
	}
	else
	{
		if(exist(_texts, text))
			return true;
	}
	
	return false;
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

bool List::load(wxFileName const& fileName)
{
	if(fileName == _fileName)
		return true;
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{	
		//Chargement de la lange.
		if(!load(fileName, nullptr, &_lg))
			return false;
		
		//Copie de fichier
		if(!wxCopyFile(fileName.GetFullPath(), _fileName.GetFullPath(), false))
			return false;
	}
	else
	{
		//Chargement des textes.
		if(!load(fileName, &_texts, &_lg))
			return false;
	}
	
	return true;
}

bool List::sove(wxFileName const& fileName)
{
	if(_fileName == fileName)
		return true;
		
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		//Copie de fichier
		if(!wxCopyFile(_fileName.GetFullPath(), fileName.GetFullPath()))
			return false;
	}
	else
	{
		//Chargement des textes.
		if(!save(fileName, _texts, _lg))
			return false;
	}
	
	return true;
}

wxFileName List::getFileName()const
{
	return _fileName;
}

void List::setFileName(wxFileName const& fileName)
{
	_texts.Clear();	
	_fileName = fileName;
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		//Chargement de la lange
		load(_fileName, nullptr, &_lg);
	}
}

bool List::load(	wxFileName const& fileName,
					wxArrayString* texts,
					wxString* language)const
{
	wxString tmpText;
	
	wxTextFile file;
	if(!file.Open(fileName.GetFullPath()))
		return false;
	
	//Premier ligne c'est la lange de la liste
	tmpText = file.GetFirstLine();
	if(language != nullptr)
		*language = tmpText;
	
	//Les autres lignes c'est la liste ...
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
					wxString const& language)const
{
	wxFile file;
	if(!file.Open(fileName.GetFullPath(), wxFile::write))
		return false;
	
	//Écriture de la lange.
	file.Write(language);
	
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

