//! \file **************************************************************
//! \brief Header Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.11
//! \date 12.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#ifndef MAIN_H
#define MAIN_H

#include <wx/app.h>
#include <wx/intl.h>

#include "menuIcon.hpp"

// *********************************************************************
// Class App
// *********************************************************************

//! \brief Poins d'entrée de l'application.
//! Initialise l'application et libère les ressources à la fin de vie de celle ci.
//! \bug Trop de possesseur utiliser au bout d'un certain moment.
//! \todo Déplacer le getInstande de ressource et le créée que on en a besoin (dans les préférence).
class App : public wxApp
{
	public:			
		//! \brief Initialise l'application/ressources.
		bool OnInit();
		//! \brief Quitte l'application, libère les ressources.
		int OnExit();
		
		//! \brief Créés un menue dans la zone de notification.
		void creatMenuItem();
		//! \brief Supprime le menue dans la zone de notification.
		void deleteMenuItem();
		
		//! \brief Méthode appeler lorsque l'item Preference dans le menu à été cliquer.
		//! Cette méthode lance le dialogue des préférences.
		void OnPreferences(wxCommandEvent&);
		//! \brief Méthode appeler lorsque l'item EnableShortcuts dans le menu à été cliquer.
		//! Cette méthode désactive ou active tout les raccourcis qui on été enregistre auprès de \ref _actionManager.
		void OnEnableShortcuts(wxCommandEvent& event);
		//! \brief Méthode appeler lorsque l'item EnableActions dans le menu à été cliquer.
		//! Cette méthode désactive ou active tout les actions qui on été enregistre auprès de \ref _actionManager.
		void OnEnableActions(wxCommandEvent& event);
		//! \brief Méthode appeler lorsque l'item About dans le menu à été cliquer.
		//! Cette méthode lance le dialogue About.
		void OnAbout(wxCommandEvent&);
		//! \brief Méthode appeler lorsque l'item Exit dans le menu à été cliquer.
		//! Cette méthode fais en sort de quitter l'application.
		void OnExit(wxCommandEvent&);
	
	private:
		//! \brief Menu dans la zone de notification.
		MenuIcon* _menuIcon;
		//! \brief Pour la traduction de l'application.
		wxLocale* _locale;
		
		bool _enableShortcuts;
		bool _enableActions;
};

DECLARE_APP(App);

#endif //MAIN_H
