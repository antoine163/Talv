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

#include <wx/fileconf.h>
#include <wx/arrstr.h>
#include <vector>

// *********************************************************************
// Class ListManager
// *********************************************************************

class ListManager : public Singleton<ListManager>
{
	friend class Singleton<ListManager>;
	
	public:	
		void load(wxFileConfig & fileConfig);
		void save(wxFileConfig & fileConfig)const;
		
		List* getList(wxString const& name);
		wxArrayString getNameLists()const;
		
		bool exist(wxString const& name)const;
		List* add(	wxString const& name,
					wxString const& lgsrc,
					wxString const& lgto);
		bool remove(wxString const& name);

	private:
		//! \brief Constructeur.
		ListManager();
		//! \brief destructeur.
		virtual ~ListManager();
		
		std::vector<List*> _lists;
};

#endif //LIST_MANAGER_H
