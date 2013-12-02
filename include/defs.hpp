//! \file **************************************************************
//! \brief Header def
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 26.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DEF_H
#define DEF_H

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
	
	
	EMPTY,				//!< Le conteneur est vide.
	NO_EMPTY,			//!< Le conteneur n'est pas vide.
	
	TEXT_EXIST,			//!< Le texte existe.
	TEXT_NO_EXIST		//!< Le texte n'existe pas.
};

// *********************************************************************
// Enum id_e
// *********************************************************************
enum id_e
{
	ID_PREFERENCES = wxID_PREFERENCES,
	ID_ENABLE_SHORTKUT,
	ID_ABOUT = wxID_ABOUT,
	ID_QUIT
};

#endif //DEF_H
