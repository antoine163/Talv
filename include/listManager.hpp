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
		
		//! \brief Obtenir une lite en fonction de son nom.
		//!
		//! Une bonne utilisation serai d'éviter d'affecter le pointeur 
		//! retourner a une variable pour une utilisation ultérieur.
		//! Une utilisation directe du pointeur est préférable.
		//! Par exemple dans un bock de code.
		//! Tout de mois si vous ne fait pas cela, fait attention a ce que
		//! la méthode \ref remove() ne sois pas appeler avec le non de
		//! la liste que vous utilisez. Sent quoi vous vous retrouveriez
		//! avec un pointeur non valide.
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
