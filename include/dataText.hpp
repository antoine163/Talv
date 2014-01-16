//! \file **********************************************************************
//! \brief Header DataText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 19.11.2013
//!
//! ****************************************************************************

#ifndef DATA_TEXT_H
#define DATA_TEXT_H

//Stl
#include <map>

//WxWidgets
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/file.h>

// *****************************************************************************
// Enum Knowledge_e
// *****************************************************************************
//! \brief Les différentes connaissances.
enum Knowledge_e
{
	KNOWLEDGE_ALL			= 0x0f,
	KNOWLEDGE_UNKNOWN		= 0x01,
	KNOWLEDGE_LITTLE_KNOWN	= 0x02,
	KNOWLEDGE_KNOWN			= 0x04,
	KNOWLEDGE_VERY_KNOWN	= 0x08
};

inline Knowledge_e operator|(Knowledge_e val1, Knowledge_e val2)
{
	unsigned int val = (unsigned int)val1|(unsigned int)val2;
	return static_cast<Knowledge_e>(val);
}

// *****************************************************************************
// Class DataText
// *****************************************************************************

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
		
		//! \brief Pour récupérer touts les traductions.
		//! \return le wxString correspond aux natures et le wxArrayString
		//! aux traductions.
		std::map<wxString, wxArrayString> const& getTranslations()const;
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
