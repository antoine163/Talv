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
		wxFile file(_fileName.GetFullPath(), wxFile::write_append)
		file.Write("\n"text);
		file.Close();
	}
	else	
		_texts->Add(text);
	
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
		load(_fileName, &tmpTexts)
		
		//le texte existe ?
		if(exist(tmpTexts, text))
			return true;
	}
	else
	{
		if(exist(_texts, text))
			return true;
	}
	
	return false
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

bool List::load(wxFileName const& file)
{
	if(file == _fileName)
		return true;
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{	
		//Chargement de la lange.
		if(!load(file, nullptr, &_lg))
			return false;
		
		//Copie de fichier
		if(!wxCopyFile(file.GetFullPath(), _fileName.GetFullPath(), false))
			return false;
	}
	else
	{
		//Chargement des textes.
		if(!load(file, &_texts, &_lg))
			return false;
	}
	
	return true;
}

bool List::sove(wxFileName const& file)
{
	if(_fileName == file)
		return true;
		
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		//Copie de fichier
		if(!wxCopyFile(_fileName.GetFullPath(), file.GetFullPath()))
			return false;
	}
	else
	{
		//Chargement des textes.
		if(!save(file, &_texts, &_lg))
			return false;
	}
	
	return true;
}

wxFileName List::getFileName()const
{
	return _fileName;
}

void List::setFileName(wxFileName const& file)
{
	_texts.Clear();	
	_fileName = file;
	
	//Il y a un nom de fichier.
	if(_fileName.HasName())
	{
		//Chargement de la lange
		load(_fileName, nullptr, &_lg);
	}
}

bool List::load(	wxFileName const& file,
					wxArrayString* texts,
					wxString* language)
{
	wxString tmpText;
	
	wxTextFile file(file.GetFullPath())
	
	//Premier ligne c'est la lange de la liste
	tmpText = file.GetFirstLine();
	if(language != nullptr)
		language = tmpText;
	
	//Les autres lignes c'est la liste ...
	if(texts != nullptr)
	{
		for(tmpText = file.GetNextLine(); !file.Eof(); str = file.GetNextLine())
			texts->Add(tmpText);
	}
	file.Close();
}

bool List::save(	wxFileName const& file,
					wxArrayString const& texts,
					wxString const& language)
{
	wxFile file(_fileName.GetFullPath(), wxFile::write_append)
	
	//Écriture de la lange.
	file.Write(language);
	
	//Écriture des textes.
	for(auto it: texts)
		file.Write("\n"+it);
		
	file.Close();
}

bool List::exist(wxArrayString const& texts, wxString const& text)
{
	int index = texts.Index(text, false);
	if(index == wxNOT_FOUND)
		return false;
		
	return true;
}

bool List::remove(wxArrayString& texts, wxString const& text)
{
	int index = texts.Index(text, false);
	if(index == wxNOT_FOUND)
		return false;
		
	texts.RemoveAt(index);
	
	return true;
}

