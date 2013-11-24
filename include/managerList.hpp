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
#include "listBase.hpp"

#include <wx/fileconf.h>

// *********************************************************************
// Class ManagerList
// *********************************************************************

//! \brief Gestion des listes
//! liste automatique a partir des caches
class ManagerList : public ManagerMap<wxString, ListBase>,
					public Singleton<ManagerList>,
					public EditableByPanel
{
	friend class Singleton<ManagerList>;
	
	public:	
		//! \brief Charger la configuration du manager.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde la configuration du manager.
		void save(wxFileConfig& fileConfig)const;
		
		
		List* create(	wxString const& newListName,
						wxString const& lgsrc,
						wxString const& lgto);
		
		List* create(	wxString const& newListName,
						wxArrayString const& listsNames,
						Knowledge_e KnowledgeFilter = KNOWLEDGE_ALL,
						int nbTranslationFilter = 0);//>=0
								
		List* create(	wxString const& newListName,
						std::vectore<List const*> const& lists,
						Knowledge_e KnowledgeFilter = KNOWLEDGE_ALL,
						int nbTranslationFilter); = 0);//>=0
						
		//! \brief Obtenir le nom de touts les lites.
		//! \return le nom de tout les listes.
		wxArrayString getNameLists()const;
		
		//! \brief Obtenir le nom de touts les lites en fonction de leur lange.
		//! \return le nom de tout les listes.
		wxArrayString getNameListsByLanguages(	wxString const& lgsrc,
												wxString const& lgto)const;

		virtual bool remove(wxString const& listName);
		virtual bool removeAll();
		
		
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
		
		virtual ListBase* copyNewDatas (ListBase const *inc)
		{
			return nullptr;
		}
};

#endif //MANAGER_LIST_H
