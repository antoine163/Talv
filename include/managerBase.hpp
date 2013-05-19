//! \file **************************************************************
//! \brief Header Base pour la création de Manager 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
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
//! \bug les valeur ne son pas détruit.
template <typename T1, typename T2>
class ManagerBase
{
	public:			
		//! \brief Constructeur.
		ManagerBase(){};
		
		//! \brief destructeur.
		virtual ~ManagerBase()
		{
			removeAll();
		};
		
		//! \brief Ajout d'un élément.
		//! \param key c'est la clef à ajouter.
		//! \param val c'est la valeur à ajouter.
		//! \return true si réussite, false si la clef est déjà connue.
		virtual bool add(T1 const& key, T2* val)
		{
			//Si key existe déjà.
			if(exist(key))
				return false;
				
			//Sinon on l'ajoute.
			_data[key] = val;
			
			return true;
		}
		
		//! \brief Supprimer une clefs et ça valeurs.
		//! \param key c'est la clef à supprimer.
		//! \return true si réussite, false si la clef n'est pas existante.
		virtual bool remove(T1 const& key)
		{
			//Si la clé existe.
			if(exist(key))
			{
				//On le supprime
				delete _data[key];
				_data.erase(key);
				return true;
			}
			
			return false;
		}
		
		//! \brief Supprimer tout les clefs et valeurs.
		virtual void removeAll()
		{
			//Suppression de tout les données.	
			for(auto &it: _data)
				delete it.second;

			_data.clear();
		}
		
		//! \brief Pour savoir si une clef existe.
		//! \param key c'est la clef à chercher.
		//! \return true si la clef existe.
		bool exist(T1 const& key)const
		{
			//Si la clé existe.
			if(_data.count(key) > 0)
				return true;
			
			return false;
		}
		
		//! \brief Obtenir la lites des clef et valeurs.
		std::map<T1, T2*> const& getData()const
		{
			return _data;
		}
		
		//! \brief Obtenir la lites des clef et valeurs.
		T2* getValue(T1 const& key)
		{
			return _data[key];
		}
		
	protected:
		//! \brief Lites des données.
		std::map<T1, T2*> _data;	
};

#endif //MANAGER_BASE_H
