//! \file **********************************************************************
//! \brief Header Action, traduction et sauvegarde dans une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.21
//! \date 31.03.2013
//!
//! ****************************************************************************

#ifndef ACTION_TRANSLATION_TO_LIST_H
#define ACTION_TRANSLATION_TO_LIST_H

//App
#include "action.hpp"

//WxWidgets
#include <wx/language.h>

// *****************************************************************************
// Class ActTranslationToList
// *****************************************************************************

//! \brief Action de traduction et sauvegarde la traduction dans une liste.
class ActTranslationToList : public Action
{	
	DECLARE_ACTION();
	
	public:
		//! \brief Constructeur par défaut.
		ActTranslationToList();
						
		//! \brief Destructeur.
		~ActTranslationToList();
		
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

#endif //ACTION_TRANSLATION_TO_LIST_H
