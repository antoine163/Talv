//! \file **************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include "singleton.hpp"
#include "list.hpp"

#include <vector>

// *********************************************************************
// Class ListManager
// *********************************************************************

class ListManager : public Singleton<ListManager>
{
	friend class Singleton<ListManager>;
	
	public:	
		//! \attention utiliser la \ref List retourner mais ne pas la garder pour une utilisation ultérieur.
		List* getList(wxString const& name);
		wxArryString getNameLists();
		
		bool exist(wxString const& name);
		List* add(wxString const& name);
		//bool remove(wxString const& name);

	private:
		//Chargement des liste a partir du dossier (a appeler dans le constructeur)
		void load();
		
		//! \brief Constructeur.
		ListManager();
		//! \brief destructeur.
		virtual ~ListManager();
		
		std::vector<List> _lists;
};

#endif //LIST_MANAGER_H
