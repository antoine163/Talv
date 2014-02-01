//! \file **********************************************************************
//! \brief Header List
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ****************************************************************************

#ifndef LIST_H
#define LIST_H

//App
#include "fileText.hpp"

//WxWidgets
#include <wx/filename.h>
#include <wx/file.h>

// *****************************************************************************
// Class List
// *****************************************************************************
//! \brief Manipulation de liste de texte.
//!
//! Cette classe permet de manipuler un fichier contenant une liste de textes.
//!
//! Pour crée une liste vous devais commencer par renseigner le non du fichier
//! avec \ref setFileName(). Ensuit vous dévirez appeler \ref setLanguages() dans 
//! quele cas le fichier ne sera pas crée sur le disque.
class List : public FileText
{
	public:		
		//! \brief Constructeur par défaut.
		List();
				
		//! \brief Destructeur.
		virtual ~List();
		
		//! \brief Ajout un texte à la liste si il n'est pas déjà existent.
		//! \param text le texte à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_TEXT_EXIST, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e addText(wxString const& text);
		
		//! \brief Remplace touts les textes pas de nouveaux.
		//! \param texts les textes à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e replaceTexts(wxArrayString const& texts);
		
		//! \brief Obtenir tout les textes contenue dans le fichier.
		//! \param texts là où seront stoker les texte.
		//! Ce paramètre ne doit pas être nullptr.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED, 
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e getTexts(wxArrayString* texts)const;
		
		//! \brief Savoir si un texte est déjà existent dans le fichier.
		//! \param text Le texte rechercher.
		//! \return \ref STATUS_TEXT_EXIST, \ref STATUS_TEXT_NO_EXIST, 
		//! \ref STATUS_FILE_OPEN_FAILED, \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e existText(wxString const& text)const;
		
		//! \brief Supprime un texte de la liste.
		//! Suprime le premier texte trouver.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_TEXT_NO_EXIST, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_CREATE_FAILED, \ref STATUS_FILE_READ_ERROR, 
		//! \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e removeText(wxString const& text);
		
	protected:
		//! \brief Ajoute des textes à la liste. Ne vérifie pas si 
		//! les textes son déjà existent.
		//! \param texts les text à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		virtual Status_e addTexts(wxArrayString const& texts);
};

#endif //LIST_H
