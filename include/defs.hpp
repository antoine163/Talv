//! \file **********************************************************************
//! \brief Header def
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 26.11.2013
//!
//! ****************************************************************************

#ifndef DEF_H
#define DEF_H

//WxWidgets
#include <wx/defs.h>

//! \brief Taille des bordures
#define SIZE_BORDER 4

// *****************************************************************************
// Enum Status_e
// *****************************************************************************
enum Status_e
{
	STATUS_OK,					//!< Ok.
	STATUS_SUCCESS,				//!< Aucune erreur est survenue.

	STATUS_FILE_NO_NAME,		//!< Vous n'avais pas spécifier de non de fichier.
	STATUS_FILE_NO_REMOVE,		//!< Le fichier n'a pas pu être supprimer. Peut être qu'il existe pas.
	STATUS_FILE_OPEN_FAILED, 	//!< Le fichier n'a pas pu être ouvert. Peut être qu'il existe pas.
	STATUS_FILE_CREATE_FAILED,	//!< Le fichier n'a pas pu être créé.
	STATUS_FILE_READ_ERROR,		//!< Erreur l'or d'une lecture dans le fichier.
	STATUS_FILE_WRITE_ERROR,	//!< Erreur l'or d'une écriture dans le fichier.


	STATUS_EMPTY,				//!< Le conteneur est vide.
	STATUS_NO_EMPTY,			//!< Le conteneur n'est pas vide.

	STATUS_TEXT_EXIST,			//!< Le texte existe.
	STATUS_TEXT_NO_EXIST		//!< Le texte n'existe pas.
};

// *****************************************************************************
// Enum id_e
// *****************************************************************************
enum id_e
{
	ID_PREFERENCES = 		wxID_PREFERENCES,
	ID_ENABLE_SHORTKUT = 	1,
	ID_ABOUT = 				wxID_ABOUT,
	ID_QUIT = 				2,
	ID_LEARN,
	ID_EXPORT,
	ID_IMPORT,
	ID_TO_PDF,
	ID_CHANGE_SHORTCUT,
	
	ID_DIALOG_PREFERENCES
};

#endif //DEF_H
