//! \file **************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include "singleton.hpp"
#include "managerBase.hpp"
#include "list.hpp"

#include <wx/fileconf.h>
#include <wx/arrstr.h>
#include <vector>

// *********************************************************************
// Class ListManager
// *********************************************************************

//! \brief Gestion des listes
class ListManager : public ManagerBase<wxString, List>, public Singleton<ListManager>
{
	friend class Singleton<ListManager>;
	
	public:	
		//! \brief Charger les listes à partir du fichier de config.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde des listes dans le fichier de config.
		void save(wxFileConfig& fileConfig)const;
		
		wxString getPath()const;

	private:
		//! \brief Constructeur.
		ListManager();
		//! \brief destructeur.
		virtual ~ListManager();
};

 //*********************************************************************
 //Class EditActionManager
 //*********************************************************************

class EditListManager : public ManagerBase<wxString, List>, public Singleton<EditListManager>
{	
	friend class Singleton<EditListManager>;
	
	public:
		//! \brief Initialisation à partir de ListManager
		void init();
		
		//! \brief Applique à ListManager
		void apply();
		
		//! \brief Obtenir le nom de touts les lites.
		//! \return le nom de tout les listes.
		wxArrayString getNameLists()const;
		
		//! \brief Obtenir le nom de touts les lites en fonction de leur lange.
		//! \return le nom de tout les listes.
		wxArrayString getNameListsByLanguages(	wxString const& lgsrc,
												wxString const& lgto)const;
		wxString getPath()const;
		
	private:
		//! \brief Constructeur.
		EditListManager();
		
		//! \brief destructeur.
		virtual ~EditListManager();
};

#endif //LIST_MANAGER_H
