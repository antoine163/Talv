//! \file **************************************************************
//! \brief Header Gestion des raccourci.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
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
#include <vector>
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
		std::map<wxString, wxString> const& getLangs();
		//! \brief Obtenir la liste des actions.
		std::vector<wxString> const& getActions();
	
	private:
		Resource();
		~Resource();
		
		//! \brief Liste des acronyme et langues <acronyme, langue>.
		std::map<wxString, wxString> _langs;
		//! \brief Liste des actions.
		std::vector<wxString> _actions;
};

#endif //RESOURCE_H
