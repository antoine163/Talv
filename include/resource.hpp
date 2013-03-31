//! \file **************************************************************
//! \brief Header ressource.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 30.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "singleton.hpp"

#include <wx/string.h>
#include <map>

// *********************************************************************
// Class Resource
// *********************************************************************

//! \brief Cette classe offre plusieurs ressources et trucs plus ou mou utiles.
class Resource : public Singleton<Resource>
{	
	friend class Singleton<Resource>;
	
	public:
		//! \brief Obtenir la liste des langues avec et leur acronymes <acronyme, langue>.
		std::map<wxString, wxString> const& getLanguages()const;
		//! \brief Obtenir la langue en fonction de sont acronyme.
		wxString const& acronymToLanguage(wxString const& acronym)const;
		//! \brief Obtenir l'acronyme en fonction de sa langue.
		wxString const& languageToAcronym(wxString const& language)const;
		
		//! \brief Obtenir la liste des actions.
		std::map<wxString, size_t> const& getActions()const;
		//! \brief Obtenir l'actions en fonction de sont hash_code.
		wxString const& hashCodeToAction(size_t hashCode)const;
		//! \brief Obtenir le hash_code en fonction du l'actions.
		size_t actionsToHashCode(wxString const& action)const;
	
	private:
		Resource();
		~Resource();
		
		//! \brief Liste des acronyme et langues <acronyme, langue>.
		std::map<wxString, wxString> _languages;
		//! \brief Liste des actions et de leur hash_code associer <action, hash_code>..
		std::map<wxString, size_t> _actions;
};

#endif //RESOURCE_H
