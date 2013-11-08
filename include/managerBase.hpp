//! \file **************************************************************
//! \brief Header Base pour la création de Manager 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
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
#include <iostream>
//! \todo renommer en ManagerMap
//! \brief Classe de base pour la création de Manager
template <typename T1, typename T2>
class ManagerBase
{
	public:			
		//! \brief Constructeur.
		ManagerBase() : _data(&_dataNormal)
		{}
		
		//! \brief destructeur.
		virtual ~ManagerBase()
		{
			removeAll();
		}
		
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
			(*_data)[key] = val;
			
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
				delete (*_data)[key];
				(*_data).erase(key);
				return true;
			}
			
			return false;
		}
		
		//! \brief Supprimer tout les clefs et valeurs.
		virtual void removeAll()
		{
			//Suppression de tout les données.	
			for(auto &it: *_data)
				delete it.second;

			(*_data).clear();
		}
		
		//! \brief Passage en mode édit.
		//!
		//! Deux cas peuvent être distinguer :
		//! - Le passage en mode édit va copier les datas actuelle de la
		//! classe pour les conserver sen leur apporter de modification.
		//! De se fait la classe peut être utiliser/modifier normalement 
		//! avec les méthode usuelle ( \ref add() , \ref remove()
		//! ,\ref removeAll() , \ref exist() ,\ref getData() ,\ref getValue()).
		//! - Le passage en mode normal va supprimer les données du mode édite
		//! et va revenir avec les données du mode normale précédâmes sauvegarder.
		//! Il faudra appeler la méthode \ref apply() aven de passer
		//! en mode normale pour que les données modifier dans le mode édite
		//! soit appliquer au mode normale.
		//! 
		//! \param val true pour activer le mode édit et false pour le désactiver.
		void edit(bool val)
		{
			////on fait rien si le mode ne change pas.
			//if(isEdit() == val)
				//return;
				
			////On passe en mode édit ?
			//if(val)
			//{
				//_data = _dataEdit;
				////Copie des données
				//for(auto it: _dataNormal)
					//add(it.first, copyNewDatas(it.second));
			//}
			////On passe en mode normale ?
			//else
			//{
				//_data = _dataNormal;
			//}
		}
				
		//! \brief Applique les modification apporter par le mode édite au
		//! data du mode normale.
		//! \note Cette méthode n'a pas d'influence en mode normale et
		//! devra être utiliser seulement en mode édite.
		//! \see isEdit()
		void apply()
		{
		}
				
		//! \brief Pour savoir si le manager est en mode édit.
		//! \return true si il est en mode édit.
		bool isEdit()
		{
			if(_data == _dataEdit)
				return true;
				
			return false;
		}
		
		//! \brief Pour savoir si une clef existe.
		//! \param key c'est la clef à chercher.
		//! \return true si la clef existe.
		bool exist(T1 const& key)const
		{
			//Si la clé existe.
			if((*_data).count(key) > 0)
				return true;
			
			return false;
		}
		
		//! \brief Obtenir la lites des clefs et valeurs.
		std::map<T1, T2*> const& getData()const
		{
			return *_data;
		}
		
		//! \brief Obtenir la valeurs d'une clef.
		//! \return nullptr si la clef n'existe pas.
		T2* getValue(T1 const& key)
		{
			if(!exist(key))
				return nullptr;
			
			return (*_data)[key];
		}
		
	protected:
	
		//! \brief Méthode pouvant copier une données.
		//! \param inc donnée a copier.
		//! \return une nouvelle instance de la donner fraîchement copier.
		//virtual T2* copyNewDatas(T2 const* inc)=0;
	
	private:
		//! \brief données en cour d'utilisation.
		std::map<T1, T2*>* _data;	
		//! \brief Lites des données en mode normale.
		std::map<T1, T2*> _dataNormal;
		//! \brief Lites des données en mode édite.
		std::map<T1, T2*> _dataEdit;	
};

#endif //MANAGER_BASE_H
