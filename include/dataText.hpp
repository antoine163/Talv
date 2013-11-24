//! \file **************************************************************
//! \brief Header DataText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 19.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DATA_TEXT_H
#define DATA_TEXT_H

#include <map>
#include <wx/string.h>
#include <wx/arrstr.h>

// *********************************************************************
// Enum Knowledge_e
// *********************************************************************
//! \brief Les différentes connaissances.
enum Knowledge_e
{
	KNOWLEDGE_ALL			= 0x0f,
	KNOWLEDGE_UNKNOWN		= 0x01,
	KNOWLEDGE_LITTLE_KNOWN	= 0x02,
	KNOWLEDGE_KNOWN			= 0x04,
	KNOWLEDGE_VERY_KNOWN	= 0x08
};

// *********************************************************************
// Class DataText
// *********************************************************************

//! \brief classe représentent les données d'un texte traduit.
class DataText
{
	public:		
		//! \brief Constructeur.
		DataText();
		
		//! \brief Constructeur.
		DataText(wxString const& translation);
				
		//! \brief Destructeur.
		virtual ~DataText();
		
		//! \brief Pour récupérer la traduction principale.
		wxString getMainTranslation()const;
		//! \brief Pour modifier la traduction principale.
		void setMainTranslation(wxString const& translation);
		
		//! \brief Pour récupérer les traductions en fonction de la nature
		//! traduction.
		wxArrayString getTranslations(wxString const& nature)const;
		//! \brief Pour récupérer tout les natures des traduction
		//! existante pour ce texte.
		wxArrayString getNatures()const;
		//! \brief Ajouter une traduction au texte.
		void addTranslation(wxString const& nature, wxString const& translation);
		
		//! \brief Pour récupérer le niveau de connaissance.
		Knowledge_e getKnowledge()const;
		//! \brief Pour modifier le niveau de connaissance.
		void setKnowledge(Knowledge_e knowledge);
		
		//! \brief Pour récupérer la nombre traduction.
		unsigned int getNbTranslation()const;
		//! \brief Pour modifier le nombre traduction.
		void setNbTranslation(unsigned int nbTranslation);
		//! \brief Pour incrementer le nombre de traduction.
		void incrementNbTranslation();
		
		//! \brief Remise à zéro de tous les paramètres.
		void clear();
		
	private:	
		wxString _mainTranslation;
		std::map<wxString, wxArrayString> _translations;
		
		Knowledge_e _knowledge;
		unsigned int _nbTranslation;
};

#endif //DATA_TEXT_H
