//! \file **************************************************************
//! \brief Header List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_H
#define LIST_H

#include <wx/filename.h>
#include <wx/file.h>

// *********************************************************************
// Enum Status_e
// *********************************************************************
enum Status_e
{
	SUCCESS,			//!< Aucune erreur est survenue.

	FILE_NO_NAME,		//!< Vous n'avais pas spécifier de non de fichier.
	FILE_NO_REMOVE,		//!< Le fichier n'a pas pu être supprimer. Peut être qu'il existe pas.
	FILE_OPEN_FAILED, 	//!< Le fichier n'a pas pu être ouvert. Peut être qu'il existe pas.
	FILE_CREATE_FAILED,	//!< Le fichier n'a pas pu être créé.
	FILE_READ_ERROR,	//!< Erreur l'or d'une écriture dans le fichier.
	FILE_WRITE_ERROR,	//!< Erreur l'or d'une lecture dans le fichier.
	
	
	LIST_EMPTY,			//!< La liste ne contient aucun textes.
	LIST_NO_EMPTY,		//!< La liste contient des textes.
	
	TEXT_EXIST,			//!< Le texte existe.
	TEXT_NO_EXIST		//!< Le texte n'existe pas.
};

// *********************************************************************
// Class List
// *********************************************************************
//! \brief Manipulation de liste de textes.
//!
//! Cette classe permet de manipuler un fichier contenant une liste de textes.
//!
//! Pour crée une liste vous devais commencer par renseigner le non du fichier
//! avec \ref setFileName(). Ensuit vous dévirez appeler \ref setLanguages() dans 
//! quele cas le fichier ne sera pas crée sur le disque.
class List
{
	public:		
		//! \brief Constructeur par défaut.
		List();
				
		//! \brief Destructeur.
		virtual ~List();
		
		//! \brief Obtenir les langages de la liste.
		//! \param lgsrc là où sera stoker le langage source.
		//! Ce paramètre ne doit pas être nullptr.
		//! \param lgto là où sera stoker le langage de traduction.
		//! Ce paramètre ne doit pas être nullptr.
		//! \return \ref SUCCESS, \ref FILE_OPEN_FAILED,
		//! \ref FILE_READ_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		//! - Si \ref FILE_OPEN_FAILED est retourner il est probablement
		//! que vous avez besoin d'appeler \ref setLanguages().
		Status_e getLanguages(wxString* lgsrc, wxString* lgto)const;
		
		//! \brief Modifier les langages de la liste.
		//!
		//! Vous pouvez faire ceci seulement si la liste est vide.
		//! Le fichier sera créé si il n'existe pas.
		//!
		//! \return \ref SUCCESS, \ref LIST_NO_EMPTY, \ref FILE_OPEN_FAILED,
		//! \ref FILE_CREATE_FAILED, \ref FILE_READ_ERROR,
		//! \ref FILE_WRITE_ERROR, \ref FILE_NO_NAME,
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		//! \see isEmpty()
		Status_e setLanguages(wxString const& lgsrc, wxString const& lgto);
		
		//! \brief Pour savoir si la liste est vide ou pas.
		//! \return \ref LIST_EMPTY, \ref LIST_NO_EMPTY, 
		//! \ref FILE_OPEN_FAILED, \ref FILE_READ_ERROR, 
		//! \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e isEmpty()const;
		
		//! \brief Supprimer le fichier et supprime le non de fichier
		//! \return \ref SUCCESS, \ref FILE_NO_REMOVE, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e clear();
		
		//! \brief Ajout un textes à la liste si il n'est pas déjà existent.
		//! \param text le texte à ajouter.
		//! \return \ref SUCCESS, \ref TEXT_EXIST, \ref FILE_OPEN_FAILED,
		//! \ref FILE_READ_ERROR, \ref FILE_WRITE_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e addText(wxString const& text);
		
		//! \brief Remplace touts les textes pas de nouveaux.
		//! \param texts les textes à ajouter.
		//! \return \ref SUCCESS, \ref FILE_OPEN_FAILED,
		//! \ref FILE_WRITE_ERROR, \ref FILE_READ_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e replaceTexts(wxArrayString const& texts);
		
		//! \brief Obtenir tout les textes contenue dans le fichier.
		//! \param texts là où seront stoker les texte.
		//! Ce paramètre ne doit pas être nullptr.
		//! \return \ref SUCCESS, \ref FILE_OPEN_FAILED, 
		//! \ref FILE_READ_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e getTexts(wxArrayString* texts)const;
		
		//! \brief Savoir si un texte est déjà existent dans le fichier.
		//! \param text Le texte rechercher.
		//! \return \ref TEXT_EXIST, \ref TEXT_NO_EXIST, 
		//! \ref FILE_OPEN_FAILED, \ref FILE_READ_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e existText(wxString const& text)const;
		
		//! \brief Supprime un texte de la liste.
		//! Suprime le premier texte trouver.
		//! \return \ref SUCCESS, \ref TEXT_NO_EXIST, \ref FILE_OPEN_FAILED,
		//! \ref FILE_CREATE_FAILED, \ref FILE_READ_ERROR, 
		//! \ref FILE_WRITE_ERROR, \ref FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e removeText(wxString const& text);
		
		//! \brief Obtenir le non du fichier
		wxFileName getFileName()const;
		
		//! \brief Modifier le non du fichier.
		//!
		//! Cette méthode de ne copie les données du fichier actuelle
		//! ver le nouveau.
		void setFileName(wxFileName const& fileName);
		
	protected:
		//! \brief Ajoute des textes à la liste. Ne vérifie pas si 
		//! les textes son déjà existent.
		//! \param texts les text à ajouter.
		//! \return \ref SUCCESS, \ref FILE_OPEN_FAILED,
		//! \ref FILE_WRITE_ERROR, \ref FILE_NO_NAME
		Status_e addTexts(wxArrayString const& texts);
		
	private:
		Status_e readInFile(wxFile& file, wxString* str)const;
		Status_e writeInFile(wxFile& file, wxString const& str);
		Status_e filePointerAfterHeader(wxFile& file)const;
	
		//! \brief Fichier de la liste.
		wxFileName _fileName;
};

#endif //LIST_H
