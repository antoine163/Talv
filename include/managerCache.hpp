//! \file **************************************************************
//! \brief Header ManagerCache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 19.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef MANAGER_CACHE_H
#define MANAGER_CACHE_H

#include "singleton.hpp"
#include "managerMap.hpp"
#include "cache.hpp"

// *********************************************************************
// Class ManagerCache
// *********************************************************************

//! \brief Interface utilisateur pour les gestions des caches.
class ManagerCache : 	public ManagerMap<ShortcutKey, Cache>,
						public Singleton<ManagerCache>
{	
	friend class Singleton<ManagerCache>;
	
	public:
	
		//! \brief Charger la configuration du manager.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde la configuration du manager.
		void save(wxFileConfig& fileConfig)const;
		
		Cache getCache(	wxString const& lgsrc,
						wxString const& lgto);
		
		//! \brief Obtenir le nom de touts les caches.
		//! \return le nom de tout les caches.
		wxArrayString getNameCaches()const;
		
		
	private:
		//! \brief Constructeur.
		ManagerCache();
		
		//! \brief Destructeur.
		virtual ~ManagerCache();
		
		//! \brief Implémentassions de \ref ManagerMap.
		virtual Cache* copyNewDatas(Cache const* inc);
};

#endif //MANAGER_CACHE_H
