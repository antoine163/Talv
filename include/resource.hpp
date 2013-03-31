//! \file **************************************************************
//! \brief Header ressources.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
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
		std::map<wxString, wxString> const& getLangs();
		//! \brief Obtenir la liste des actions.
		std::map<wxString, size_t> const& getActions();
	
	private:
		Resource();
		~Resource();
		
		//! \brief Liste des acronyme et langues <acronyme, langue>.
		std::map<wxString, wxString> _langs;
		//! \brief Liste des actions et de leur hash_code associer <action, hash_code>..
		std::map<wxString, size_t> _actions;
};

#endif //RESOURCE_H
