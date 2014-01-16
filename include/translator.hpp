//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.01.2014
//!
//! ****************************************************************************

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

//App
#include "translator.hpp"
#include "dataText.hpp"

//Std
#include <map>
#include <vector>

//WxWidgets
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/language.h>


#define DECLARE_TRANSLATOR()					\
		public:									\
		virtual wxString getName()const;		\
		virtual wxString getDescription()const;	\
		virtual wxString getURL()const
	
#define IMPLEMENT_TRANSLATOR(translator, name, description, url)		\
		wxString translator::getName()const{return name;}				\
		wxString translator::getDescription()const{return description;}	\
		wxString translator::getURL()const{return url;}
	
//! \defgroup translator Translators
//! \brief Liste des traducteurs
//!
//! Les classes dans cette section sont des traducteurs.
//! Les classes préfixer par \b Trl sont touts basée sur la classe \ref Translator.


// *****************************************************************************
// Class Translator
// *****************************************************************************

//! \brief Class de base pour les traducteur.
//! \see \ref pageCreateTranslator

class Translator
{
	public:
		//! \brief Constructeur.
		Translator();
		
		//! \brief Destructeur.
		virtual ~Translator();
		
		//! \brief Obtenir la traduction d'un texte.
		//! \param translations variable de retour contenant la traduction du texte.
		//! \param text est le textes à traduire.
		//! \param lgsrc Langue du texte.
		//! \param lgto Langue de traduction.
		virtual void getTranslations(	DataText* translations,
										wxString const& text,
										wxLanguage lgsrc,
										wxLanguage lgto)=0;
	
		//! @name Auto implémenter
		//!
		//! Dans les casses filles c'est méthode son auto implémenter
		//! par l'appelle des macros \ref DECLARE_TRANSLATOR et \ref IMPLEMENT_TRANSLATOR
		//! @{

		//! \brief Obtenir le non du traducteur.
		//! \return Le non de l'action.
		virtual wxString getName()const=0;
		
		//! \brief Obtenir la description du traducteur.
		//! \return La description.
		virtual wxString getDescription()const=0;
		
		//! \brief Obtenir le lien ver le site web du traducteur.
		//! \return Le lien.
		virtual wxString getURL()const=0;
		
		//! @} //Auto implémenter
		
		//! \brief Créées tout les type de traducteur connue.
		//!
		//! Penser a libérer la mémoire.
		static std::vector<Translator*> createAllTranslators();
	private:
};

#endif //TRANSLATOR_H
