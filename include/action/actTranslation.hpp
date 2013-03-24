//17.03.2013
//v 0.3

#ifndef ACTION_TRANSLATION_H
#define ACTION_TRANSLATION_H

#include "action.hpp"

//! \brief Action de traduction.
class ActTranslation : public Action
{
	public:
		//! \brief Constructeur.
		//! Les deux paramètres doive être écrit en abrégé.
		//! ex: pour le français "fr"
		//! ex: pour l'anglais "en"
		//!
		//! \param lgsrc lange source.
		//! \param lgto lange de traduction.
		ActTranslation(wxString const& lgsrc, wxString const& lgto);
						
		//! \brief Obtenir le non de l'action.
		~ActTranslation();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		static ActTranslation load(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		void sove(wxFileConfig & fileConfig)const;
		
		//! \brief Préférences de l'action au format string.
		//! \todo à implémenter correctement.
		wxString getStringPreferences()const;
	
	private:
		//! \brief Lange source.
		wxString _lgsrc;
		//! \brief Lange de traduction.
		wxString _lgto;
};

#endif //ACTION_TRANSLATION_H
