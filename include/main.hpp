//! \file **********************************************************************
//! \brief Header Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.16
//! \date 12.12.12
//!
//! ****************************************************************************

#ifndef MAIN_H
#define MAIN_H

//WxWidgets
#include <wx/app.h>
#include <wx/intl.h>

// *****************************************************************************
// Class App
// *****************************************************************************

//! \brief Poins d'entrée de l'application.
class App : public wxApp
{
	public:			
		//! \brief Initialise l'application/ressources.
		bool OnInit();
		//! \brief Quitte l'application, libère les ressources.
		int OnExit();
		
		//! \brief Méthode pour récupérer l'évènement pour quitter
		//! l'application.
		void onQuit(wxCommandEvent&);
		
		//! \brief Méthode pour récupérer l'évènement pour lancer le dialogue
		//! des préférences.
		void onPreferences(wxCommandEvent&);
		
		//! \brief Méthode pour récupérer l'évènement pour lancer activer ou
		//! désactiver les actions.
		void onEnableShortcuts(wxCommandEvent& event);
		
		//! \brief Méthode pour récupérer l'évènement pour lancer le dialogue
		//! a propos.
		void onAbout(wxCommandEvent&);
	
	private:		
		//! \brief Pour la traduction de l'application.
		wxLocale* _locale;
};

#endif //MAIN_H
