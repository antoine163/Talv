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
#include <wx/string.h>
#include <map>

// *********************************************************************
// Lnum ListKnowledge_e
// *********************************************************************
enum Knowledge_e
{
	VAL1,
	VAL2
};

// *********************************************************************
// Class List
// *********************************************************************

class ListManager;

//! \brief Pour manipuler une liste son fichier associer.
//!
//! Seul ListManager peut crée et supprimer des instance de la class \ref List.
class List
{
	friend class ListManager;
	
	public:		
		wxString const& getName()const;
		
		//! \brief Pour sauvegarder un texte et ça traduction dans la liste.
		//! \param text le texte a sauvegarder.
		//! \param mainTranslate la traduction a sauvegarder.
		//! \return 
		int save(	wxString text,
					wxString mainTranslate);
					
		//! \brief Pour sauvegarder un texte et c'est traductions dans la liste.
		//! \param text le texte a sauvegarder.
		//! \param mainTranslate la traduction principale a sauvegarder.
		//! \param translations les traductions a sauvegarder.
		//! \return 
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
	
		//! \brief Pour connaître l'existence d'un texte dans la liste.
		//! \param text a vérifier.
		//! \return true si le texte existe sinon flase.
		bool exist(wxString text);
		
		
		void removeFile();
		
	private:
		//! \brief Constructeur.
		List(	wxString const& name,
				wxString const& lgsrc,
				wxString const& lgto);
		//! \brief destructeur.
		virtual ~List();
		
		
		wxFileName _name;
		
		wxString _lgsrc;
		wxString _lgto;
};

#endif //LIST_H
