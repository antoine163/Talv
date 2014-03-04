//! \file **********************************************************************
//! \brief Header Action de traduction ver la presse papier.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.03.2014
//!
//! ****************************************************************************

#ifndef ACTION_TRANSLATION_TO_CLIBOARD_H
#define ACTION_TRANSLATION_TO_CLIBOARD_H

//App
#include "action.hpp"
#include "control/ctrlPickLanguages.hpp"

//WxWidgets
#include <wx/language.h>
#include <wx/checkbox.h>

// *****************************************************************************
// Class ActTranslationToClipboard
// *****************************************************************************

//! \brief Action de traduction ver la presse papier.
class ActTranslationToClipboard : public Action
{	
	DECLARE_ACTION();
	
	public:
		//! \brief Constructeur par défaut.
		ActTranslationToClipboard();
						
		//! \brief Destructeur.
		~ActTranslationToClipboard();
		
		//! \brief Obtenir le window gui pour éditer l'action.
		//! \param parent est le parent du window.
		//! \note Cette méthode crées un \ref WinAction et retourne le pointeur sur se \ref WinAction il faudra prévoir de libérai la mémoire.
		WinAction* newEditWindow(wxWindow* parent);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Exécuter l'action.
		void execute();
		
		void getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const;
		void setLanguages(wxLanguage lgsrc, wxLanguage lgto);
		
		bool IsUsedDlgPick()const;
		void UseDlgPick(bool use = true);
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig& fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig& fileConfig)const;
		
	private:
		//! \brief Lange source.
		wxLanguage _lgsrc;
		//! \brief Lange de traduction.
		wxLanguage _lgto;
		//! \brief true pour dessiner le dialogue de chois de la traduction.
		bool _dlgPick;
};

// *****************************************************************************
// Class WinActTranslationToClipboard
// *****************************************************************************

//! \brief GUI pour la modification des préférences des actions de traductions ver la presse papier. \ref ActTranslationToClipboard.
class WinActTranslationToClipboard : public WinAction
{
	public:
		//! \brief Constructeur.
		WinActTranslationToClipboard(wxWindow* parent, ActTranslationToClipboard const* act);
		//! \brief Destructeur.
		~WinActTranslationToClipboard();
		
		virtual void refreshActionFromGui();
	
	private:
		wxCheckBox* _checkBoxShowDlgPick;
		CtrlPickLanguages* _ctrlPickLanguages;
};

#endif //ACTION_TRANSLATION_TO_CLIBOARD_H
