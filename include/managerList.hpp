//! \file **************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef MANAGER_LIST_H
#define MANAGER_LIST_H

#include "editableByPanel.hpp"
#include "singleton.hpp"
#include "managerMap.hpp"

#include <wx/fileconf.h>

// *********************************************************************
// Class ManagerList
// *********************************************************************

//! \brief Gestion des listes
class ManagerList : public ManagerMap<wxString, wxString>,
					public Singleton<ManagerList>,
					public EditableByPanel
{
	friend class Singleton<ManagerList>;
	
	public:	
		//! \brief Charger les listes à partir du fichier de config.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde des listes dans le fichier de config.
		void save(wxFileConfig& fileConfig)const;
		
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual wxPanel* newEditPanel(wxWindow *parent);
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelCheck()const;
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelApply();

	private:
		//! \brief Constructeur.
		ManagerList();
		//! \brief destructeur.
		virtual ~ManagerList();
};

#endif //MANAGER_LIST_H
