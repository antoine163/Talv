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

#ifndef TRANSLATOR_GOOGLE_H
#define TRANSLATOR_GOOGLE_H

//App
#include "translator.hpp"

// *****************************************************************************
// Class TrlGoogle
// *****************************************************************************

//! \brief Traducteur prenant les google traduction comme base de données.
class TrlGoogle : public Translator
{	
	DECLARE_TRANSLATOR();
	
	public:
		//! \brief Constructeur par défaut.
		TrlGoogle();
						
		//! \brief Destructeur.
		~TrlGoogle();
		
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

#endif //TRANSLATOR_GOOGLE_H
