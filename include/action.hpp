//! \file **************************************************************
//! \brief Header Interface Action
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.16
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

//
#define SHOW_ACTION(action)
		_actions[action::action.getName()] = #action;
#define NEW_ACTION(action)\
		if(actTypeName == #action)return new action();
#include "actionDef.hpp"		
//

//! \brief permet de déclarer 
//! A appeler dans las classes fille de \ref Action 
#define DECLARE_ACTION()\
	public:\
	virtual wxString const& getName()const;\
	virtual wxString const& getDescription()const;\
	virtual wxString const& getActTypeName()const;\
	virtual Action* newClone()const
	
//! \brief Obtenir 
#define IMPLEMENT_ACTION(action, name, description)\
	wxString const& action::getName()const{static wxString r=name; return r;}\
	wxString const& action::getDescription()const{static wxString r=description; return r;}\
	wxString const& action::getActTypeName()const{static wxString r=#action; return r;}\
	Action* action::newClone()const{return new action(*this);}
	
//! \defgroup action Actions
//! \brief Liste des actions
//!
//! Les classes dans cette section sont des actions.
//! Les classes préfixer par \b Act sont touts basée sur la classe \ref Action.


// *********************************************************************
// Class Action
// *********************************************************************

//! \brief Class de base pour les actions.
//! \see \ref pageCreateAction
class Action
{
	public:
		//! \brief Constructeur.
		Action();
		
		//! \brief destructeur.
		virtual ~Action();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! Pour les classes filles, le but est d'éditer directement les paramètre (attribut) de l'action via le panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		//! \param parent le wxWindow parent.
		virtual window* getWindowPreferences(wxWindow* parent)=0;
		
		//! \brief Permet d'extraire les préférences de l'action au format string,
		//! dans le but des les affichées à l'utilisateur.
		virtual wxString getStringPreferences()const=0;
		
		//! \brief Permet d'exécuter l'action.
		virtual void execute()=0;
		
		//! \brief Obtenir le nom de la liste utiliser.
		//! \return wxEmptyString si l'action n'utilise pas de liste.
		virtual wxString getListNameUsed()const;
	
	
		//! @name Auto implémenter
		//!
		//! Dans les casses filles c'est méthode son auto implémenter
		//! par l'appelle des macros \ref DECLARE_ACTION et \ref IMPLEMENT_ACTION
		//! @{

		//! \brief Obtenir le non de l'action.
		//! \return Le non de l'action.
		virtual wxString const& getName()const=0;
		
		//! \brief Obtenir la description de l'action.
		//! \return La description.
		virtual wxString const& getDescription()const=0;
		
		//! \brief Obtenir le non de la class de l'action.
		//! \return Le non de la classe.
		virtual wxString const& getActTypeName()const=0;
		
		//! \brief Crée un clone de la classe
		//! \param act est l'action a copier
		//! \return nullptr si l'action n'a pas pu être créé.
		virtual Action* newClone()const=0;
		
		//! @} //Auto implémenter

	
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void save(wxFileConfig& fileConfig)const;
		
		
		//! \brief Crée une nouvelle action à partir de son nom de class.
		//! \param actTypeName le non de la class de l'action.
		//! \return nullptr si l'action n'a pas pu être créé.
		//! \see getActTypeName()
		static Action* newAction(wxString const& actTypeName);
	
	protected:
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig (appelé par \ref load()).
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		virtual void actLoad(wxFileConfig& fileConfig)=0;
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig(appelé par \ref sove()).
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		virtual void actSave(wxFileConfig& fileConfig)const=0;
		
	private:
		
};

#endif //ACTION_H
