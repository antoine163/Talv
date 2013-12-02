//! \file **************************************************************
//! \brief Header Singleton
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.6
//! \date 30.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef SINGLETON_H
#define SINGLETON_H

// *********************************************************************
// Class Singleton
// *********************************************************************

//! \brief Pour la création de classe singleton.
template <typename T>
class Singleton
{
	public:
		//! \brief Obtenir l'instance de la classe.
		//! Elle sera crée si elle n'existe pas.
		static T* get()
		{
			if(_singleton == nullptr)
				_singleton = new T;
				
			return _singleton;
		}
		
		//! \brief Supprimer l'instance de la classe.
		static void kill()
		{
			if(_singleton != nullptr)
				delete _singleton;
				
			_singleton = nullptr;
		}
	
	protected:
		Singleton(){}
		Singleton(Singleton const&){}
		Singleton & operator=(Singleton const&){}
		virtual ~Singleton(){}
		
	private:
		//! \brief Instance de la classe.
		static T *_singleton;
};

//Initialisation de l'instance
template <class T>
T* Singleton<T>::_singleton = nullptr;

#endif //SINGLETON_H
