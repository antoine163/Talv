//! \file **********************************************************************
//! \brief Header Action de traduction ver une notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 17.03.2013
//!
//! ****************************************************************************

#ifndef ACTION_TRANSLATION_TO_NOTIFICATION_H
#define ACTION_TRANSLATION_TO_NOTIFICATION_H

//App
#include "action.hpp"
#include "control/ctrlPickLanguages.hpp"

//WxWidgets
#include <wx/language.h>

// *****************************************************************************
// Class ActTranslationToNotification
// *****************************************************************************

//! \brief Action de traduction.
class ActTranslationToNotification : public Action
{	
	DECLARE_ACTION();
	
	public:
		//! \brief Constructeur par défaut.
		ActTranslationToNotification();
						
		//! \brief Destructeur.
		~ActTranslationToNotification();
		
		//! \brief Obtenir le window gui pour éditer l'action.
		//! \param parent est le parent du window.
		//! \note Cette méthode crées un window et retourne le pointeur sur se window il faudra prévoir de libérai la mémoire.
		WinAction* newEditWindow(wxWindow* parent);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Exécuter l'action.
		void execute();
		
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
};

// *****************************************************************************
// Class WinActTranslationToNotification
// *****************************************************************************

//! \brief GUI pour la modification des préférences des actions de traductions \ref ActTranslation.
class WinActTranslationToNotification : public WinAction
{
	public:
		//! \brief Constructeur.
		WinActTranslationToNotification(wxWindow* parent, ActTranslationToNotification const* act);
		//! \brief Destructeur.
		~WinActTranslationToNotification();
		
		virtual void refreshActionFromGui();
	
	private:
		CtrlPickLanguages* _ctrlPickLanguages;
};

#endif //ACTION_TRANSLATION_TO_NOTIFICATION_H
