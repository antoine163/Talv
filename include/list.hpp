//! \file **************************************************************
//! \brief Header List
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

#ifndef LIST_H
#define LIST_H

#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/string.h>
#include <map>

// *********************************************************************
// Lnum ListKnowledge_e
// *********************************************************************
enum Knowledge_e
{
	KNOWLEDGE_UNKNOWN		= 1,
	KNOWLEDGE_LITTLE_KNOWN	= 2,
	KNOWLEDGE_KNOWN			= 3,
	KNOWLEDGE_VERY_KNOWN	= 4
};

// *********************************************************************
// Class List
// *********************************************************************

class ListManager;

//! \brief Pour manipuler une liste avec sont fichier associer.
//!
//! Seul ListManager peut crée et supprimer des instances de la class \ref List.
class List
{
	friend class ListManager;
	
	public:		
		//! \brief Pour connaître le non de la liste.
		//! \return le non de la liste.
		wxString getName()const;
		
		//! \brief Pour connaître l'existence d'un texte dans la liste.
		//! \param texte à vérifier.
		//! \return true si le texte existe sinon flase.
		bool exist(wxString const& text);
		
		//! \brief Pour sauvegarder un texte et ça traduction dans la liste.
		//! \param text le texte à sauvegarder.
		//! \param mainTranslate la traduction à sauvegarder.
		//! \return -1 le texte na pas put être sauvegarder(Erreur au niveau du fichier).
		//!			0 le texte est déjà existent.
		//!			1 le texte a bien été sauvegarder.
		int save(	wxString const& text,
					wxString const& mainTranslate);
					
		//! \brief Pour sauvegarder un texte et ces traductions dans la liste.
		//! \param text le texte à sauvegarder.
		//! \param mainTranslate la traduction principale à sauvegarder.
		//! \param translations les traductions à sauvegarder.
		//! \return -1 le texte na pas put être sauvegarder (Erreur au niveau du fichier).
		//!			0 le texte est déjà existent.
		//!			1 le texte a bien été sauvegarder.
		int save(	wxString text,
					wxString mainTranslate,
					std::map<wxString, wxArrayString> const& translations);
					
		//bool getTranslates(	wxString const& text,
							//wxString* mainTranslate);
					
		//bool getTranslates(	wxString const& text,
							//wxString* mainTranslate,
							//std::map<wxString, wxArrayString>* translations);
					
		//bool getTranslates(	int index,
							//wxString* mainTranslate);
					
		//bool getTranslates(	int index,
							//wxString* mainTranslate,
							//std::map<wxString, wxArrayString>* translations);
							
		//Knowledge_e getKnowledge(wxString const& text);
		//bool setKnowledge(wxString const& text, Knowledge_e knowledge);
		
		//int getNumberTextByKnowledge(Knowledge_e level);
		
		//! \brief Supprimer le fichier de la liste.
		void removeFile();
		
	private:
		//! \brief Pour connaître le numéro de ligne (dans le fichier) ou se troue un texte.
		//! \param texte a chercher.
		//! \return le nu numéro de ligne dans le fichier. Si 0, le texte n'a pas été trouver.
		size_t getTextLine(wxString text);
		
		//! \brief Constructeur.
		List(	wxFileName const& fileName,
				wxString const& lgsrc,
				wxString const& lgto);
				
		//! \brief destructeur.
		virtual ~List();
		
		//! \brief Le non nu fichier de la liste.
		wxFileName _fileName;
		
		//! \brief Représente la première ligne du fichier sous la forme d'un wxArrayString.
		wxArrayString _FirstLine;
		
		//! \brief C'est le fichier de la liste.
		wxTextFile _file;
		
		//! \brief Lange source de liste.
		wxString _lgsrc;
		
		//! \brief Lange de traduction de liste.
		wxString _lgto;
};

#endif //LIST_H
