//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "list.hpp"
#include <wx/filefn.h> 

// *********************************************************************
// Class List
// *********************************************************************

List::List(	wxFileName const& fileName,
			wxString const& lgsrc,
			wxString const& lgto)
: _fileName(fileName), _lgsrc(lgsrc), _lgto(lgto)
{
	//Le fichier existe ?
	if(wxFileExists(_fileName.GetFullPath()))
	{
		//On ouvre le fichier
		_file.Open(_fileName.GetFullPath());

		//On analyse la première ligne
		wxString firstLine = _file.GetFirstLine();
		wxString beforeComma;
		for(size_t i = 0; i<firstLine.Length(); i++)
		{
			if(firstLine[i] == ',')
			{
				_FirstLine.Add(beforeComma);
				beforeComma.Clear();
			}
			else
			{
				beforeComma << firstLine[i];
			}
		}
		//On enregistre aussi le dernier texte trouver si il n'est pas vide
		if(!beforeComma.IsEmpty())
		{
			_FirstLine.Add(beforeComma);
		}
		
		//On vérifie les langages.
		wxASSERT(_FirstLine[1]==_lgsrc);
		wxASSERT(_FirstLine[2]==_lgto);
	}
}

List::~List()
{
	_file.Close();
}

wxString List::getName()const
{
	return _fileName.GetName();
}

bool List::exist(wxString const& text)
{
	if(getTextLine(text) != 0)
		return true;
		
	return false;
}

int List::save(	wxString const& text,
				wxString const& mainTranslate)
{	
	std::map<wxString, wxArrayString> empty;
	return save(text, mainTranslate, empty);
}
			
int List::save(	wxString text,
				wxString mainTranslate,
				std::map<wxString, wxArrayString> const& translations)
{
	//On vérifie si le texte est existent.
	if(exist(text))
		return 0;
	
	//Caractère en minuscule.
	text.MakeLower();
	mainTranslate.MakeLower();

	//Si le fichier n'est pas déjà existent
	if(!wxFileExists(_fileName.GetFullPath()))
	{
		//On le crée
		if(!_file.Create(_fileName.GetFullPath()))
			return -1;
		//On ajout la première ligne.
		_file.AddLine("knowledge,"+_lgsrc+','+_lgto);

		_FirstLine.Add("knowledge");
		_FirstLine.Add(_lgsrc);
		_FirstLine.Add(_lgto);
	}

	//Parcoure autant de ligne qu'il y en a dans "translations".
	bool loop = true;
	for(size_t iline = 0;;iline++)
	{
		std::map<int, wxString> strline;
		int nbColumn = 0;

		//Parcoure tout les colonnes du fichier
		for(auto it : translations)
		{
			//On vérifie si le type du mot et connue dans la première ligne.
			int column = _FirstLine.Index(it.first, false);
			if(column == wxNOT_FOUND)
			{
				//Si il n'existe pas on l'ajoute.
				column = _FirstLine.Add(it.first);
			}

			//Le nombre de colonne et égale à l'index de la colonne la plus élever.
			if(nbColumn < column)
				nbColumn = column;

			//Si il n'y a plus de texte à cette colonne et à cette ligne
			if(iline >= it.second.GetCount())
			{
				//On a plus besoin de boucler pour cette ligne.
				loop = false;
			}
			else
			{
				//On a besoin de boucler pour cette ligne.
				loop = true;
				//On ajoute le texte dans la bonne colonne et la bonne ligne
				strline[column] = it.second[iline];
			}
		}

		//Si on ne doit plus boucler.
		if(!loop)
			break;

		//La ligne à ajouter
		wxString addLine;

		//Première ligne (à sauvegarder) ?
		if(iline == 0)
			addLine << KNOWLEDGE_UNKNOWN << ',' << text << ',' << mainTranslate;
		else
			addLine << ",,";

		//On parcoure tout les colonne (soft les deux première).
		for(int iColumn = 2; iColumn <= nbColumn; iColumn++)
		{
			addLine << ',';
			if(strline.count(iColumn) > 0)
			{
				addLine << strline[iColumn];
			}
		}
		//Écriture des données dans le fichier.
		_file.AddLine(addLine);
	}

	//Réécriture de la première ligne du fichier.
	wxString addFirstLine;
	for(auto it : _FirstLine)
	{
		addFirstLine << it << ',';
	}
	_file.RemoveLine(0);
	_file.InsertLine(addFirstLine, 0);

	//Écriture des données dans le fichier.
	if(!_file.Write())
		return -1;
	
	return 1;
}

void List::removeFile()
{
	//Récupération du non du fichier
	wxString fileName = _fileName.GetFullPath();
	
	//Si le fichier est existent, on le supprime.
	if(wxFileExists(fileName))
		wxRemoveFile(fileName);
}

size_t List::getTextLine(wxString text)
{
	//Fichier ouvert ?
	if(_file.IsOpened())
	{
		//Caractère en minuscule.
		text.MakeLower();

		//On recherche si le texte existe (avent le deuxième ',' de tout les lignes)
		for(wxString line = _file.GetFirstLine(); !_file.Eof(); line = _file.GetNextLine())
		{
			//Texte trouver ?
			if(line.BeforeFirst(',').BeforeFirst(',') == text)
			{
				return _file.GetCurrentLine();
			}
		}
	}

	return 0;
}
