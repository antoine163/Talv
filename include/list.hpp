//! \file **************************************************************
//! \brief Header List
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

#ifndef LIST_H
#define LIST_H

#include "listBase.hpp"

#include <wx/string.h>
#include <wx/filename.h>

// *********************************************************************
// Class List
// *********************************************************************

//! \brief Manipulation de liste contenant de simple textes.
//! \see ListBase
class List : public ListBase
{
	public:		
		//! \brief Constructeur par défaut.
		List();
				
		//! \brief destructeur.
		virtual ~List();
		
		//! \brief Ajout d'un nouveau texte.
		//! \param text texte à ajouter.
		//! \return true si le texte a put être ajouter.
		//! false si le texte existe déjà ou problème sur le fichier.
		bool addText(wxString const& text);
		
		//! \brief Pour obtenir tout les textes de la lite.
		wxArrayString getTexts()const;
		
		//! \brief Réimplantation à partir de \ref ListBase
		//! \see ListBase
		virtual void setFileName(wxFileName const& fileName);
		
	private:
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool isEmptyFile()const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool isEmptyMemory()const;
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual void clearFile();
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual void clearMemory();
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool removeTextFile(wxString const& text);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool removeTextMemory(wxString const& text);
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool existTextFile(wxString const& text)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool existTextMemory(wxString const& text)const;
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool loadFile(wxFileName const& fileName);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool loadMemory(wxFileName const& fileName);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		
		virtual bool saveFile(wxFileName const& fileName)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool saveMemory(wxFileName const& fileName)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		
		//! \brief Charge les textes d'un fichier dans la mémoire.
		//! \param fileName c'est le fichier.
		//! \param texts Les textes trouver dans le fichier serons stoker ici.
		//! Si vous ne voulez pas de cette informations vous pouvez
		//! passer nullptr.
		//! \param lgsrc Le langage source trouver dans le fichier sera
		//! stoker ici. Si vous ne voulez pas de cette informations
		//! vous pouvez passer nullptr.
		//! \param lgto Le langage de destination trouver dans le fichier sera
		//! stoker ici. Si vous ne voulez pas de cette informations
		//! vous pouvez passer nullptr.
		//!
		//! \note Par exemple si vous passer nullptr a \p lgsrc
		//! et que vous donné un pointeur valide a \p lgto
		//! la valeur de se pointeur ne sera pas modifier. Et vis versa.
		//! \return true si tout c'est bien passer.
		bool load(	wxFileName const& fileName,
					wxArrayString* texts,
					wxString* lgsrc = nullptr,
					wxString* lgto = nullptr)const;
					
		//! \brief Sauvegarde les textes contenue dans la mémoire dans
		//! un fichier.
		//! \param fileName c'est le fichier.
		//! \param texts Les textes a écrire dans le fichier.
		//! \param lgsrc Le langage source a écrie dans le fichier.
		//! \param lgto Le langage de destination a écrie dans le fichier.
		//! \return true si tout c'est bien passer.
		bool save(	wxFileName const& fileName,
					wxArrayString const& texts,
					wxString const& lgsrc,
					wxString const& lgto)const;
			
		//! \brief Pour savoir si un texte existe dans un wxArrayString.
		//! \param texts les textes où chercher.
		//! \param text le texte a chercher.
		//! \return true si tout c'est bien passer.
		bool exist(wxArrayString const& texts, wxString const& text)const;
		//! \brief Pour supprimer un texte dans un wxArrayString.
		//! \param texts les textes où supprimer le texte.
		//! \param text le texte a supprimer.
		//! \return true si tout c'est bien passer.
		bool remove(wxArrayString& texts, wxString const& text)const;
		
		
		//! \brief Les textes de la listes (si pas de non de fichier spécifier).
		wxArrayString _texts;
};

#endif //LIST_H
