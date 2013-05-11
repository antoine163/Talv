//! \file **************************************************************
//! \brief Header List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
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

//! \brief Pour manipuler une liste avec sont fichier associer.
//!
//! Seul ListManager peut crée et supprimer des instances de la class \ref List.
class List
{
	public:		
		//! \brief Constructeur.
		List();
				
		//! \brief destructeur.
		virtual ~List();
		
		//! \brief Constructeur.
		bool init(	wxFileName const& fileName,
					wxString const& lgsrc,
					wxString const& lgto);
		
		//! \brief Récupérée les deux langues de la liste.
		void getlanguages(wxString* lgsrc, wxString* lgto);
		
		//! \brief Pour sauvegarder un texte et ça traduction dans la liste.
		//! \param text le texte à sauvegarder.
		//! \param mainTranslate la traduction à sauvegarder.
		//! \return -1 le texte na pas put être sauvegarder(Erreur au niveau du fichier).
		//!			0 le texte est déjà existent.
		//!			1 le texte à bien été sauvegarder.
		int save(	wxString const& text,
					wxString const& mainTranslate);
					
		//! \brief Pour sauvegarder un texte et ces traductions dans la liste.
		//! \param text le texte à sauvegarder.
		//! \param mainTranslate la traduction principale à sauvegarder.
		//! \param translations les traductions à sauvegarder.
		//! \return -1 le texte na pas put être sauvegarder (Erreur au niveau du fichier).
		//!			0 le texte est déjà existent.
		//!			1 le texte à bien été sauvegarder.
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
		
		//! \brief Supprimer le fichier du système.
		void removeFile();
		
	private:
		//! \brief Ouverture le fichier.
		//!
		//! Ouvre le fichier, vérifie la validité des langues et met à jours Knowledge au besoin.
		bool openFile();
		
		//! \brief Fermeture du fichier.
		//!
		//! Mai aussi a jour \ref _lastModificationFile.
		void closeFile();
	
		//! \brief Analyse la première ligne du fichier.
		//! 
		//! Cette méthode remplie l'attribut \ref _firstLine.
		//! \note Le fichier à besoin d'être ouvert au préalable.
		//! \note Le fichier doit être au moins constituer de la première ligne.
		void parseFirstLine();
	
		//! \brief Analyse du fichier pour remplier les connaissance.
		//!
		//! Cette méthode remplie l'attribut \ref _knowledges.
		//! \note Le fichier à besoin d'être ouvert au préalable.
		//! \note Le fichier doit être au moins constituer de la première ligne.
		//! \see Knowledge_e
		void parseKnowledge();
		
		//! \brief Pour connaître le numéro de ligne (dans le fichier) ou se troue un texte.
		//! \note Le fichier à besoin d'être ouvert au préalable.
		//! \param texte à chercher.
		//! \return le numéro de ligne dans le fichier. Si 0, le texte n'a pas été trouver.
		size_t getTextLine(wxString text);
		
		//! \brief Représente la première ligne du fichier sous la forme d'un wxArrayString.
		wxArrayString _firstLine;
		
		//! \brief Représente le nombre de texte trier par connaissance.
		std::map<Knowledge_e, unsigned int> _knowledges;
		
		//! \brief Le non du fichier de la liste.
		wxFileName _fileName;
		
		//! \brief Pour connaître la dernière fois que l'on a accéder au fichier.
		wxDateTime _lastModificationFile;
		
		//! \brief C'est le fichier de la liste.
		wxTextFile _file;
		
		//! \brief Lange source de liste.
		wxString _lgsrc;
		//! \brief Lange de traduction de liste.
		wxString _lgto;
};

#endif //LIST_H
