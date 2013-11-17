//! \file **************************************************************
//! \brief Header List
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

#ifndef LIST_H
#define LIST_H

#include <wx/string.h>
#include <wx/filename.h>

// *********************************************************************
// Class List
// *********************************************************************

//! \brief Manipulation de textes dans une liste.
//!
//! Temps que vous ne spécifier pas de fichier ( avec \ref setFileName() )
//! tout les textes sont stoker dans la mémoire ram. Au contraire, si 
//! vous spécifier un n'on de fichier avec \ref setFileName(), dans ce
//! cas tout les textes sont stoker dans le fichier spécifier. \n
//! Vous pouvez appeler la méthode \ref setFileName() avec comme argument
//! wxEmptyString qui aura pour effet de passer au mode sans fichier.
//! \todo setlangage()
class List
{
	public:		
		//! \brief Constructeur par défaut.
		List();
				
		//! \brief destructeur.
		virtual ~List();
					
		//! \brief Obtenir le langage de la liste.
		wxString getLanguage()const;
		//! \brief Modifier langage de la liste.
		//! \attention Cette méthode et utilisable seulement si la liste
		//! est vide (\ref isEmpty()), a la création ou Après un
		//! \ref clean() par exemple. Vous pouvez vérifier en appellent
		//! \ref getLanguage().
		//! \return true si la lange à pu être changer.
		bool setLanguage(wxString const& lg);
		
		//! \brief Pour savoir si la liste est vide ou pas.
		bool isEmpty();
		
		//! \brief Suppression de tous les textes.
		//! 
		//! Si un non de fichier à été spécifier avec \ref setFileName() ,
		//! alors se fichier sera aussi supprimer du disque dur.
		void clear();
		
		//! \brief Ajout d'un nouveau texte.
		//! \param text texte à ajouter.
		//! \return true si le texte a put être ajouter.
		//! false si le texte existe déjà ou problème sur le fichier.
		bool addText(wxString const& text);
		//! \brief Suppression d'un texte.
		//! \param text texte à supprimer.
		//! \return true si le texte a put être supprimer.
		//! false si le texte n'existe pas ou problème sur le fichier.
		bool removeText(wxString const& text);
		
		//! \brief Pour savoir si un texte existe.
		//! \param text texte à chercher.
		//! \return true si le texte existe.
		bool exist(wxString const& text);
		
		//! \brief Pour obtenir tout les textes de la lite.
		wxArrayString getTexts()const;
		
		//! \brief Charger la lite de textes à partir d'un fichier.
		//!
		//! Si vous avez au préalable spécifier un fichier avec
		//! \ref setFileName() , alors le contenue du fichier spécifier
		//! sera remplacer par le contenue du fichier passer en
		//! paramètre à cette méthode ( \p file).
		//! \param file fichier à partir du quelle les données seront charger.
		//! \return false si problème avec le fichier.
		bool load(wxFileName const& fileName);
		//! \brief Sauvegarder la lite de textes dans un fichier.
		//! \param file fichier où serons stoker les données.
		//! \return false si problème avec le fichier.
		bool sove(wxFileName const& fileName);
		
		//! \brief Obtenir le non de fichier.
		wxFileName getFileName()const;
		//! \brief Attribuer un fichier à la liste.
		//!
		//! Après cette appelle de méthode, toutes les opérations se
		//! ferons dans le fichier et non pas dans la mémoire.
		//! Si il y a, au préalable des données dans la liste, elle serons
		//! perdue. De nouvelle données serons charger à partir 
		//! du fichier.
		//!
		//! Dans le cas inverse, si vous passez \b wxFileName()
		//! (mode sans fichier) toutes les opération se ferons dans la ram.
		//! Si il y a, au préalable des données dans la liste, elle serons
		//! aussi perdue (elle resterons écrite dans le fichier).
		//! \return dans le cas ou 
		void setFileName(wxFileName const& fileName);
		
	private:
		bool load(	wxFileName const& fileName,
					wxArrayString* texts,
					wxString* language = nullptr)const;
		bool save(	wxFileName const& fileName,
					wxArrayString const& texts,
					wxString const& language)const;
		bool exist(wxArrayString const& texts, wxString const& text)const;
		bool remove(wxArrayString& texts, wxString const& text)const;
		
		
		//! \brief Les textes de la listes (si pas de non de fichier spécifier).
		wxArrayString _texts;
		//! \brief Fichier de la liste.
		wxFileName _fileName;
		//! \brief Langage de la liste.
		wxString _lg;
};

#endif //LIST_H
