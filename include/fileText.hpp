//! \file **************************************************************
//! \brief Header FileText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 17.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_BASE_H
#define LIST_BASE_H

#include "def.hpp"

#include <wx/string.h>
#include <wx/filename.h>

// *********************************************************************
// Class FileText
// *********************************************************************

//! \brief Classe de base pour manipuler des textes dans un fichier.
class FileText
{
	public:		
		//! \brief Constructeur par défaut.
		FileText();
				
		//! \brief Destructeur.
		virtual ~FileText();
		
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
		//! \return \ref SUCCESS, \ref NO_EMPTY, \ref FILE_OPEN_FAILED,
		//! \ref FILE_CREATE_FAILED, \ref FILE_READ_ERROR,
		//! \ref FILE_WRITE_ERROR, \ref FILE_NO_NAME,
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		//! \see isEmpty()
		Status_e setLanguages(wxString const& lgsrc, wxString const& lgto);
		
		//! \brief Pour savoir si la liste est vide ou pas.
		//! \return \ref EMPTY, \ref NO_EMPTY, 
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
		
		
		//! \brief Obtenir le non du fichier.
		wxFileName getFileName()const;
		
		//! \brief Modifier le non du fichier.
		//!
		//! Cette méthode ne copie les données du fichier actuelle
		//! ver le nouveau.
		void setFileName(wxFileName const& fileName);
		
	protected:
		//! \brief Positionne le curseur après l'entête.
		//!
		//! Le fichier devra déjà être ouvert en lecture. 
		//! \param file Le fichier où positionner le curseur.
		//! \return \ref SUCCESS, \ref FILE_READ_ERROR
		virtual Status_e filePointerAfterHeader(wxFile& file)const;
		
		//! \brief Lis une chaîne de caractère a partir du curseur
		//! actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en lecture. 
		//! \param file Le fichier où lire le texte.
		//! \param str là ou sera stoker le résulta de la lecture.
		//! Doit être un pointeur valide.
		//! \return \ref SUCCESS, \ref FILE_READ_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après le texte (l'octet
		//! juste après le texte sa peut être aussi la fin du fichier).
		virtual Status_e readStringInFile(wxFile& file, wxString* str)const;
		
		//! \brief Écrire une chaîne de caractère a partir du curseur
		//! actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en écriture. 
		//! \param file Le fichier où écrire le texte.
		//! \param str le texte à écrire.
		//! \return \ref SUCCESS, \ref FILE_WRITE_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après le texte (l'octet
		//! juste après le texte sa peut être aussi la fin du fichier).
		virtual Status_e writeStringInFile(wxFile& file, wxString const& str);
	
		//! \brief Fichier de la liste.
		wxFileName _fileName;
};

#endif //LIST_BASE_H
