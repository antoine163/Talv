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

#ifndef ACTION_SAVE_TRANSLATION_H
#define ACTION_SAVE_TRANSLATION_H

#include "action.hpp"
#include "action/guiPanelActSaveTranslation.h"

// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************

class ActSaveTranslation;

class PanelActSaveTranslation : public GuiPanelActSaveTranslation
{
	public:
		PanelActSaveTranslation(wxWindow* parent, ActSaveTranslation * act);
		~PanelActSaveTranslation();
	
	private:
		//! \brief ActSoveTranslation à modifier.
		ActSaveTranslation * _act;
};


// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

class ActSaveTranslation : public Action
{
	friend PanelActSaveTranslation;
	
	public:
		ActSaveTranslation();
						
		//! \brief Obtenir le non de l'action.
		~ActSaveTranslation();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent);
		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		static ActSaveTranslation load(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		void sove(wxFileConfig & fileConfig)const;
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
	
	private:
};

#endif //ACTION_SAVE_TRANSLATION_H
