//! \file **************************************************************
//! \brief Header Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.11
//! \date 04.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_H
#define ACTION_H

#include <wx/string.h>
#include <wx/fileconf.h>
#include <wx/button.h>
#include <wx/panel.h>

// *********************************************************************
// Class Action
// *********************************************************************

//! \brief Class de base pour les actions.
//! \see \ref pageCreateAction
class Action
{
	public:
		//! \brief Constructeur.
		Action(wxString const& name, wxString const& actTypeName, wxString const& actDescription);
		
		//! \brief destructeur.
		virtual ~Action();
		
		//! \brief Permet d'exécuter l'action.
		virtual void execute()=0;
		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void save(wxFileConfig& fileConfig)const;
		
		//! \brief Permet d'extraire les préférences de l'action au format string,
		//! dans le but des les affichées à l'utilisateur.
		virtual wxString getStringPreferences()const=0;
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! Pour les classes filles le but est d'éditer directement les paramètre (attribut) de l'action via le panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		//! \param parent le wxWindow parent.
		//! \param buttonOK bouton "OK" du dialogue parent.
		virtual wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK)=0;
		
		//! \brief Obtenir la description de l'action.
		//! \return La description.
		wxString const& getDescription()const;
		
		//! \brief Obtenir le non de l'action.
		//! Peut être utiliser avec les GUI.
		//! \return Le non de l'action.
		wxString const& getName()const;
	
		//! \brief Obtenir le non de la class de l'action.
		//! La différence avec \ref getName() est que cette méthode n'est pas influencer par la traduction de l'application.
		//! \return Le non de l'action.
		wxString const& getActTypeName()const;
		
		//! \brief Crée une nouvelle action à partir de son nom (invariant).
		//! \param actTypeName le non de l'action (invarient)
		//! \return nullptr si l'action n'a pas pu être créé.
		//! \see getActName()
		static Action* newAction(wxString const& actTypeName);
		
		//! \brief Crée une nouvelle action à partir d'une autre action (création d'une copie).
		//! \param act est l'action a copier
		//! \return nullptr si l'action n'a pas pu être créé.
		static Action* newAction(Action const* act);
	
	protected:
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig (appelé par \ref load()).
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		virtual void actLoad(wxFileConfig& fileConfig)=0;
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig(appelé par \ref sove()).
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		virtual void actSave(wxFileConfig& fileConfig)const=0;
		
	private:
		//! \brief Le non de l'action.
		wxString _name;
		
		//! \brief Le non de l'action (invariant).
		wxString _actTypeName;
		
		//! \brief Le non de l'action.
		wxString _actDescription;
};

#endif //ACTION_H
