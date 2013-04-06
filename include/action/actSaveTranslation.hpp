//! \file **************************************************************
//! \brief Header Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_SAVE_TRANSLATION_H
#define ACTION_SAVE_TRANSLATION_H

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

#include "action.hpp"

class ActSaveTranslation : public Action
{
	friend PanelActSaveTranslation;
	
	public:
		ActSaveTranslation();
		ActSaveTranslation(	wxString const& lgsrc,
							wxString const& lgto,
							wxString const& location,
							wxString const& fileName,
							bool soveAll,
							bool noDoublon,
							bool showDialog);
						
		//! \brief Obtenir le non de l'action.
		~ActSaveTranslation();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSove(wxFileConfig & fileConfig)const;
		
	private:
		//! \brief Lange source.
		wxString _lgsrc;
		//! \brief Lange de traduction.
		wxString _lgto;
		
		wxString _location;
		wxString _fileName;
		bool _soveAll;
		bool _noDoublon;
		bool _showDialog;
};

#endif //ACTION_SAVE_TRANSLATION_H
