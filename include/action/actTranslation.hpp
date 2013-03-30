//17.03.2013
//v 0.3

#ifndef ACTION_TRANSLATION_H
#define ACTION_TRANSLATION_H

#include "action.hpp"
#include "action/guiPanelActTranslation.h"

//! ********************************************************************
//! Class PanelActTranslation
//! ********************************************************************

class ActTranslation;
class PanelActTranslation : public GuiPanelActTranslation
{
	public:
		PanelActTranslation(wxWindow* parent, ActTranslation * act);
		~PanelActTranslation();
		
		void OnChoiceSrc(wxCommandEvent& event);
		void OnChoiceTo(wxCommandEvent& event);
	
	private:
		ActTranslation * _act;
};


//! ********************************************************************
//! Class ActTranslation
//! ********************************************************************

//! \brief Action de traduction.
class ActTranslation : public Action
{
	friend PanelActTranslation;
	
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
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent);
		
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
