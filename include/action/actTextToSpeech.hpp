//! \file **********************************************************************
//! \brief Header Action texte à la parole.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 25.04.2013
//!
//! ****************************************************************************

#ifndef ACTION_TEXT_TO_SPEECH_H
#define ACTION_TEXT_TO_SPEECH_H

//App
#include "action.hpp"

//WxWidgets
#include <wx/language.h>
#include "control/ctrlPickLanguages.hpp"

// *****************************************************************************
// Class ActTextToSpeech
// *****************************************************************************

//! \brief Action de texte à la parole.
class ActTextToSpeech : public Action
{	
	DECLARE_ACTION();
	
	public:
		//! \brief Constructeur par défaut.
		ActTextToSpeech();
						
		//! \brief Destructeur.
		~ActTextToSpeech();
		
		//! \brief Obtenir le window gui pour éditer l'action.
		//! \param parent est le parent du window.
		//! \note Cette méthode crées un window et retourne le pointeur sur se window il faudra prévoir de libérai la mémoire.
		WinAction* newEditWindow(wxWindow* parent);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Exécuter l'action.
		void execute();
		
		void getLanguage(wxLanguage* lg)const;
		void setLanguage(wxLanguage lg);
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig& fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig& fileConfig)const;
		
	private:
		//! \brief Lange.
		wxLanguage _lg;
};

// *****************************************************************************
// Class WinActTextToSpeech
// *****************************************************************************

//! \brief GUI pour la modification des préférences des actions de traductions \ref ActTranslation.
class WinActTextToSpeech : public WinAction
{
	public:
		//! \brief Constructeur.
		WinActTextToSpeech(wxWindow* parent, ActTextToSpeech const* act);
		//! \brief Destructeur.
		~WinActTextToSpeech();
		
		virtual void refreshActionFromGui();
	
	private:
		CtrlPickLanguages* _ctrlPickLanguages;
};

#endif //ACTION_TEXT_TO_SPEECH_H
