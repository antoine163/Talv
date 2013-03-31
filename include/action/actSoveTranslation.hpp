//! \file **************************************************************
//! \brief Header Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_TRANSLATION_H
#define ACTION_TRANSLATION_H

#include "action.hpp"
#include "action/guiPanelActSoveTranslation.h"

// *********************************************************************
// Class PanelActSoveTranslation
// *********************************************************************

class ActSoveTranslation;

class PanelActSoveTranslation : public GuiPanelActSoveTranslation
{
	public:
		PanelActSoveTranslation(wxWindow* parent, ActSoveTranslation * act);
		~PanelActSoveTranslation();
	
	private:
		//! \brief ActSoveTranslation à modifier.
		ActSoveTranslation * _act;
};


// *********************************************************************
// Class ActSoveTranslation
// *********************************************************************

class ActSoveTranslation : public Action
{
	friend PanelActTranslation;
	
	public:
		ActSoveTranslation();
						
		//! \brief Obtenir le non de l'action.
		~ActSoveTranslation();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent);
		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		static ActSoveTranslation load(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		void sove(wxFileConfig & fileConfig)const;
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
	
	private:
};

#endif //ACTION_TRANSLATION_H
