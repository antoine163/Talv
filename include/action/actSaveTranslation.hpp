//! \file **************************************************************
//! \brief Header Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_SAVE_TRANSLATION_H
#define ACTION_SAVE_TRANSLATION_H

#include "action/guiPanelActSaveTranslation.h"
#include "action.hpp"
#include <wx/filename.h>

// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************

class ActSaveTranslation;

class PanelActSaveTranslation : public GuiPanelActSaveTranslation
{
	public:
		PanelActSaveTranslation(wxWindow* parent, wxButton* buttonOK, ActSaveTranslation * act);
		~PanelActSaveTranslation();
		
		//! \brief Méthode appeler si appuis sur bouton "ok" du parent.
		//! Elle valide les modifications et les installe dans l'action
		void OnOKButtonClick(wxCommandEvent& event);
	
	private:
		//! \brief ActSoveTranslation à modifier.
		ActSaveTranslation * _act;
		
		//! \brief bouton "OK" du dialogue parent.
		wxButton* _buttonOK;
};


// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

class ActSaveTranslation : public Action
{
	friend PanelActSaveTranslation;
	
	public:
		//! \brief Constructeur par défaut.
		ActSaveTranslation();
		
		//! \brief Constructeur.
		ActSaveTranslation(	wxString const& lgsrc,
							wxString const& lgto,
							wxFileName const& fileName,
							bool saveAll,
							bool noDoublon,
							bool showDialog);
						
		//! \brief Obtenir le non de l'action.
		~ActSaveTranslation();
		
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
		
		wxFileName _fileName;
		bool _saveAll;
		bool _noDoublon;
		bool _showDialog;
};

#endif //ACTION_SAVE_TRANSLATION_H
