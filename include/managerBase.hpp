//! \file **************************************************************
//! \brief Header Base pour la création de Manager 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef MANAGER_BASE_H
#define MANAGER_BASE_H

#include <map>

// *********************************************************************
// Class ManagerBase
// *********************************************************************

//! \brief Classe de base pour la création de Manager
template <typename T1, typename T2>
class ManagerBase
{
	public:			
		//! \brief Constructeur.
		ManagerBase(){};
		
		//! \brief destructeur.
		virtual ~ManagerBase(){};
		
		//! \brief Ajout d'un élément.
		//! \param key c'est la clé de la valeur à ajouter.
		//! \param val c'est la valeur a jouter.
		//! \return true si réussite, false si val1 est déjà connue.
		virtual bool add(T1 const& key, T2 val)
		{
			//Si key existe déjà.
			if(exist(key))
				return false;
				
			//Sinon on l'ajoute.
			_data[key] = val;
			
			return true;
		}
		
		//! \brief Supprimer une clés et ça valeurs.
		//! \param key c'est la clé à supprimer.
		//! \return true si réussite, false si la clé n'est pas existante.
		virtual bool remove(T1 const& key)
		{
			//Si la clé existe.
			if(exist(key))
			{
				//On le supprime
				_data.erase(key);
				return true;
			}
			
			return false;
		}
		
		//! \brief Supprimer tout les clés et valeurs.
		virtual void removeAll()
		{
			//Suppression de tout les données.	
			_data.clear();
		}
		
		//! \brief Pour savoir si une clé existe.
		//! \param key c'est la clé à chercher.
		//! \return true si la clé existe.
		bool exist(T1 const& key)
		{
			//Si la clé existe.
			if(_data.count(key) > 0)
				return true;
			
			return false;
		}
		
		//! \brief Obtenir la lites des clés et valeurs.
		std::map<T1, T2> const& getData()const
		{
			return _data;
		}
		
		//! \brief Obtenir un élément.
		//! \param key est le clé à rechercher.
		//! \return nullptr si la clé n'existe pas.
		T2 const* getElement(T1 const& key)const
		{
			auto it = _data.find(key);
	
			if(it == _data.end())
				return nullptr;
			
			return it->second;
		}
		
	protected:
		//! \brief Lites des données.
		std::map<T1, T2> _data;	
};

#endif //MANAGER_BASE_H
