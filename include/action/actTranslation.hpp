//! \file **************************************************************
//! \brief Header Action de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
//! \date 17.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_TRANSLATION_H
#define ACTION_TRANSLATION_H

#include "action.hpp"
#include "action/guiPanelActTranslation.h"

// *********************************************************************
// Class PanelActTranslation
// *********************************************************************

class ActTranslation;

//! \brief GUI pour la modification des préférences des actions de traductions \ref ActTranslation.
class PanelActTranslation : public GuiPanelActTranslation
{
	public:
		//! \brief Constructeur.
		//! \param parent wxWindow parent.
		//! \param buttonOK bouton "OK" du dialogue parent.
		//! \param act action de traduction a modifier.
		PanelActTranslation(wxWindow* parent, wxButton* buttonOK, ActTranslation* act);
		//! \brief Destructeur.
		~PanelActTranslation();
		
		//! \brief Méthode appeler si appuis sur bouton "ok" du parent.
		//! Elle valide les modifications et les installe dans l'action
		void OnOKButtonClick(wxCommandEvent& event);
	
	private:
		//! \brief ActTranslation à modifier.
		ActTranslation * _act;
		
		//! \brief bouton "OK" du dialogue parent.
		wxButton* _buttonOK;
};


// *********************************************************************
// Class ActTranslation
// *********************************************************************

//! \brief Action de traduction.
class ActTranslation : public Action
{
	friend PanelActTranslation;
	
	public:
		//! \brief Constructeur par défaut.
		ActTranslation();
		
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
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig & fileConfig)const;
		
		
	
	private:
		//! \brief Lange source.
		wxString _lgsrc;
		//! \brief Lange de traduction.
		wxString _lgto;
};

#endif //ACTION_TRANSLATION_H
