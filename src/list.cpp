//! \file **************************************************************
//! \brief Source List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.6
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "list.hpp"
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

bool List::init(	wxFileName const& fileName,
					wxString const& lgsrc,
					wxString const& lgto)
{
	_fileName = fileName;
	_lgsrc = lgsrc;
	_lgto = lgto;
	
	//Le fichier existe ?
	if(wxFileExists(_fileName.GetFullPath()))
	{
		//On récupère la date de la dernière modification du fichier.
		_lastModificationFile = _fileName.GetModificationTime();
		
		//On ouvre le fichier. Se qui aura pour effet d'analyser
		//le fichier et de vérifier sa validités.
		if(!openFile())
			return false;
		//Fermeture du fichier
		closeFile();
	}
	
	return true;
}

void List::getlanguages(wxString* lgsrc, wxString* lgto)
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

int List::exist(wxString text)
{
	//Caractère en minuscule.
	text.MakeLower();
	
	//Ouverture du fichier.
	if(!openFile())
		return -1;
			
	//Le texte est existent ?
	if(getTextLine(text) != 0)
	{
		//Fermeture du fichier
		closeFile();
		
		return 1;
	}
	
	//Fermeture du fichier
	closeFile();
		
	return 0;
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
	if(!openFile())
		return -1;
			
	//Le texte est existent ?
	if(getTextLine(text) != 0)
	{
		//Fermeture du fichier
		closeFile();
		
		return 0;
	}
	
	//Caractère en minuscule.
	text.MakeLower();
	mainTranslate.MakeLower();

	//Parcoure autant de ligne qu'il y en à dans "translations".
	bool loop = true;
	for(size_t iline = 0;;iline++)
	{
		std::map<int, wxString> strline;
		int nbColumn = 0;

		//Parcoure tout les colonnes du fichier
		for(auto it : translations)
		{
			//On vérifie si le type du mot et connue dans la première ligne.
			int column = _firstLine.Index(it.first, false);
			if(column == wxNOT_FOUND)
			{
				//Si il n'existe pas on l'ajoute.
				column = _firstLine.Add(it.first);
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
	for(auto it : _firstLine)
	{
		addFirstLine << it << ',';
	}
	_file.RemoveLine(0);
	_file.InsertLine(addFirstLine, 0);

	//Écriture des données dans le fichier.
	if(!_file.Write())
	{
		//Fermeture du fichier
		closeFile();
		
		return -1;
	}
	
	//Fermeture du fichier
	closeFile();
		
	return 1;
}

void List::removeFile()
{
	//Récupération du non du fichier.
	wxString fileName = _fileName.GetFullPath();
	
	//Si le fichier est existent, on le supprime.
	if(wxFileExists(fileName))
		wxRemoveFile(fileName);
}

//! \bug n'analyse pas le fichier à l'init.
bool List::openFile()
{
	//le non de fichier est valide ?
	if(!_fileName.IsOk())
		return false;

	//Si le fichier n'est pas déjà existent.
	if(!wxFileExists(_fileName.GetFullPath()))
	{
		//On le crée.
		if(!_file.Create(_fileName.GetFullPath()))
			return -1;
		//On ajout la première ligne.
		_file.AddLine("knowledge,"+_lgsrc+','+_lgto);

		_firstLine.Add("knowledge");
		_firstLine.Add(_lgsrc);
		_firstLine.Add(_lgto);
		
		if(!_file.Write())
		{
			//Fermeture du fichier
			closeFile();
			return false;
		}
		
		//On récupère la date du fichier.
		_lastModificationFile = _fileName.GetModificationTime();
	}
	else
	{		
		//On ouvre le fichier.
		if(!_file.Open(_fileName.GetFullPath()))
			return false;
		
		//Le fichier à t'il été accéder (par une autre instance de la liste ou par un autre programme) depuis le dernier accès ?
		if(_lastModificationFile < _fileName.GetModificationTime())
		{
			//Dans se cas on analyse la première ligne.
			parseFirstLine();
			
			//Vérifie la validité des langues.
			if((_lgsrc != _firstLine[1]) || (_lgto != _firstLine[2]))
			{
				//Fermeture du fichier.
				closeFile();
				
				return false;
			}
			
			//Et on analyse les connaissance.
			parseKnowledge();
		}
	}
	
	return true;
}

void List::closeFile()
{
	_file.Close();
	
	//Mise a jour de la date de modification.
	if(_fileName.IsOk())
		_lastModificationFile = _fileName.GetModificationTime();
}

void List::parseFirstLine()
{
	//On supprime l'analyse précédant.
	_firstLine.Clear();
	
	//On analyse la première ligne
	wxString firstLine = _file.GetFirstLine();
	wxString beforeComma;
	for(size_t i = 0; i<firstLine.Length(); i++)
	{
		if(firstLine[i] == ',')
		{
			_firstLine.Add(beforeComma);
			beforeComma.Clear();
		}
		else
			beforeComma << firstLine[i];
	}
	if(!beforeComma.IsEmpty())
		_firstLine.Add(beforeComma);
}

void List::parseKnowledge()
{
	//On supprime l'analyse précédant.
	_knowledges.clear();
	
	//Lire tout le fichier ligne par ligne.
	_file.GetFirstLine();
	long nb;
	for(wxString line = _file.GetNextLine(); !_file.Eof(); line = _file.GetNextLine())
	{
		//Extraction de la connaissance.
		line.BeforeFirst(',').ToLong(&nb);
		_knowledges[(Knowledge_e)nb]++;
	}
}

size_t List::getTextLine(wxString text)
{
	//Caractère en minuscule.
	text.MakeLower();

	//On recherche si le texte existe (avent la deuxième ',').
	wxString line = _file.GetFirstLine();
	for(line = _file.GetNextLine(); !_file.Eof(); line = _file.GetNextLine())
	{		
		//Texte trouver ?
		if(line.AfterFirst(',').BeforeFirst(',') == text)
		{
			return _file.GetCurrentLine();
		}
	}

	return 0;
}
