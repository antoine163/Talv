//! \file **********************************************************************
//! \brief Header Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.17
//! \date 12.12.12
//!
//! ****************************************************************************

#ifndef MAIN_H
#define MAIN_H

//App
#include "dialog/dlgPreferences.hpp"

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
		
		//! \brief CallBack pour quitter l'application.
		void onQuit(wxCommandEvent& event);
		
		//! \brief CallBack pour lancer le dialogue préférences.
		void onPreferences(wxCommandEvent& event);
		//! \brief CallBack appeler lorsque le dialogue préférences et fermer.
		void onPreferencesColse(wxCloseEvent& event);
		
		//! \brief CallBack pour activer/désactiver les raccourcis.
		void onEnableShortcuts(wxCommandEvent& event);
		
		//! \brief CallBack pour lancer le dialogue a propos.
		void onAbout(wxCommandEvent& event);
	
	private:		
		//! \brief Pointeur sur le dialogue des préférence.
		DlgPreferences* _dlgPrefPtr;
		
		//! \brief Pour la traduction de l'application.
		wxLocale* _locale;
};

#endif //MAIN_H
