//! \file **************************************************************
//! \brief Header List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.14
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
//! \brief Les différentes connaissances.
enum Knowledge_e
{
	KNOWLEDGE_ALL			= 0,
	KNOWLEDGE_UNKNOWN		= 1,
	KNOWLEDGE_LITTLE_KNOWN	= 2,
	KNOWLEDGE_KNOWN			= 3,
	KNOWLEDGE_VERY_KNOWN	= 4
};

//! \brief Nombre de connaissance différente.
#define KNOWLEDGE_NB 4

// *********************************************************************
// Class List
// *********************************************************************

//! \brief Pour manipuler une liste avec sont fichier associer.
class List
{
	public:		
		//! \brief Constructeur.
		List();
				
		//! \brief destructeur.
		virtual ~List();
		
		//! \brief Initialise la liste.
		//!
		//! Cette méthode vas initialiser cette classe.
		//! Si le fichier \p fileName n'est pas existent alors
		//! le fichier sera crée et les langages utiliser dans cette liste sera
		//! écrit dans le fichier.  Autrement si le fichier \p fileName
		//! est déjà existent, les langages de la liste seront comparé. Ainsi
		//! si les langage ne sont pas identique cette méthode retournera \b false
		//! et la classe ne sera pas initialiser.
		//!
		//! Dans le cas ou le fichier est déjà existant il est possible
		//! de renseigner \p wxEmptyString pour les langages. Si toutefois le fichier n'excite
		//! pas \b false sera retourner et la classe ne sera pas initialiser.
		//!
		//! \param fileName le fichier de la liste.
		//! \param lgsrc le langage source de la liste.
		//! \param lgto le langage de traduction de la liste.
		//! \return true si la liste à put être initialiser.
		bool init(	wxFileName const& fileName,
					wxString const& lgsrc,
					wxString const& lgto);
			
		//! \brief Nettoyage de la class (désinit).
		//!		
		//! \note le fichier associer n'est pas supprimer.
		bool clear();
		
		//! \brief Récupérée les deux langues de la liste.
		//!
		//! Si les valeur renvoyer son vide il est probable que la classe
		//! est besoin d'être initialiser.
		void getlanguages(wxString* lgsrc, wxString* lgto);
		
		//! \brief Pour savoirs si un texte existe dans la liste.
		//! \return -1 problème au niveau du fichier.
		//!			0 le texte n'a pas été trouver.
		//!			1 le texte est existent dans la liste.
		int exist(wxString text);
		
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
		
		//! \brief Supprime un texte de la liste.
		//! \param text le texte a supprimer.
		//! \return true si le texte a pu être supprimer.
		bool removeText(wxString const& text);
							
		//! \brief Obtenir le texte et tout ces informations associer.
		//! \param index ces l'index du texte. Le premier index est 1.
		//! \param knowledge recherche de l'index parmi le niveau de connaissance.
		//! Passée \b nullptr ou un pointeur ayant comme valeur \ref KNOWLEDGE_ALL,
		//! à le même comportement au niveau de la recherche de l'index.
		//! Si un pointeur ayant comme valeur \ref KNOWLEDGE_ALL est passée
		//! comme paramètre alors la valeur du pointeur sera remplacer par le
		//! niveau de connaissance du texte recherchée.
		//! \param text le texte trouvé.
		//! \param mainTranslate la traduction principale du texte trouvé.
		//! \param translations les traduction du texte trouvé.
		//! \return true si l'index a été trouver, sinon false.
		//!
		//! Pour les paramètres demandant un pointeur, il est possible de
		//! passer \b nullptre si l'information ne vous intéresse pas.
		bool getText(	size_t index,
						Knowledge_e* knowledge,
						wxString* text,
						wxString* mainTranslate,
						std::map<wxString, wxArrayString>* translations);
						
		//! \brief Modifie la connaissance d'un texte.
		//! \param text à modifier.
		//! \param knowledge la nouvelle connaissance a appliquer au texte.
		//! \return true si la connaissance a pu être modifier.
		bool setKnowledge(wxString const& text, Knowledge_e knowledge);
		
		//! \brief Pour connaître le nombre de texte par connaissance.
		size_t getNumberTextByKnowledge(Knowledge_e level);
		
		//! \brief Obtenir le nombre de texte.
		size_t getNumberText();
		
		//! \brief Pour connaître le nombre de connaissance se trouvent dans la liste.
		size_t getNumberKnowledge();
		
		//! \brief Supprimer le fichier du système.
		void removeFile();
		
		//! \brief Obtenir le \ref Knowledge_e en fonction de sa version string.
		//! \return \ref KNOWLEDGE_ALL si la conversion na pas pu se faire.
		static Knowledge_e stringToKnowledge(wxString const& knowledge);
		
		//! \brief Obtenir la version string d'un \ref Knowledge_e.
		//! \return wxEmptyString si la conversion na pas pu se faire.
		static wxString knowledgeToString(Knowledge_e knowledge);
		
	private:
		//! \brief Ouverture le fichier.
		//!
		//! Parse de nouveau le fichier si il y a besoin.
		//!\return false si il y un problème.
		bool openFile();
		
		//! \brief Fermeture du fichier.
		//!
		//! \note Met aussi à jour \ref _lastModificationFile.
		void closeFile();
		
		//! \brief Analyse la première ligne du fichier.
		//! 
		//! Cette méthode remplie l'attribut \ref _firstLine. Et vérifie
		//! la cohérence des langages. 
		//! \note Le fichier à besoin d'être ouvert au préalable.
		//! \return face si problème.
		bool parseFirstLine();
	
		//! \brief Analyse du fichier pour remplier les connaissance.
		//!
		//! Cette méthode remplie l'attribut \ref _knowledges.
		//! \note Le fichier à besoin d'être ouvert au préalable.
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
		
		//! \brief pour savoirs si la classe List est initialiser.
		bool _init;
};

#endif //LIST_H
