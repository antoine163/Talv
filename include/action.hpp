//! \file **************************************************************
//! \brief Header Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.5
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
#include <wx/panel.h>

// *********************************************************************
// Class Action
// *********************************************************************

//! \brief Class de base pour les actions.
//! La classe \ref ActTranslation peut être pris comme exemple pour fait d'autre type d'action.
//! \attention Dans les classes fille il faudra probablement prévoie un constructeur par recopie et redéfinie l'opérateur =.
//! \attention Dans les classes fille il faudra prévoie une méthode de prototype -> static TypeDeAction load(wxFileConfig & fileConfig).
//! \todo ajouter la méthode getActName et un constructeur avec ficher de config
class Action
{
	public:
		//! \brief Constructeur par défaut.
		Action();
		//! \brief Constructeur.
		Action(wxString const& actName, wxString const& actDescription);
		
		//! \brief destructeur.
		virtual ~Action();
		
		//! \brief Permet d'exécuter l'action.
		virtual void execute()=0;
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		virtual void sove(wxFileConfig & fileConfig)const=0;
		
		//! \brief Permet d'extraire les préférences de l'action au format string,
		//! dans le but des les affichées à l'utilisateur.
		virtual wxString getStringPreferences()const=0;
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! Pour les classes filles le but est d'éditer directement les paramètre (attribut) de l'action via directement le panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		virtual wxPanel* getPanelPreferences(wxWindow* parent)=0;
		
		//! \brief Obtenir la description de l'action.
		//! \return La description.
		wxString const& getDescription()const;
		
		//! \brief Obtenir le non de l'action.
		//! \return Le non de l'action.
		wxString const& getName()const;
	
	private:
		//! \brief Le non de l'action.
		wxString _actName;
		
		//! \brief Le non de l'action.
		wxString _actDescription;
};

#endif //ACTION_H
