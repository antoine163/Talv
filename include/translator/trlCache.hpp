//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 12.01.2014
//!
//! ****************************************************************************

#ifndef TRANSLATOR_CACHE_H
#define TRANSLATOR_CACHE_H

//App
#include "translator.hpp"

// *****************************************************************************
// Class TrlCache
// *****************************************************************************

//! \brief Traducteur prenant les caches comme base de données.
class TrlCache : public Translator
{	
	DECLARE_TRANSLATOR();
	
	public:
		//! \brief Constructeur par défaut.
		TrlCache();
						
		//! \brief Destructeur.
		~TrlCache();
		
		//! \brief Obtenir la traduction d'un texte a partir des cache.
		//! \param translations variable de retour contenant la traduction du texte.
		//! \param text est le textes à traduire.
		//! \param lgsrc Langue du texte.
		//! \param lgto Langue de traduction.
		//! \return La traduction principale. (elle et aussi présente dans \p translations)
		virtual wxString getTranslations( 	std::map<wxString, wxArrayString>* translations,
											wxString const& text,
											wxLanguage lgsrc,
											wxLanguage lgto);
};

#endif //TRANSLATOR_CACHE_H
