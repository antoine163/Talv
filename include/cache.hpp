//! \file **************************************************************
//! \brief Header Cache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 16.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef CACHE_H
#define CACHE_H

// *********************************************************************
// Class Cache
// *********************************************************************

//! \brief 
class Cache
{
	public:		
		//! \brief Constructeur.
		Cache();
				
		//! \brief destructeur.
		virtual ~Cache();
		
		
		
		//Pour l'idée crée des cache a partir de liste et d'autre cache
		bool creat(Cache const& cache);
		bool creat(std::vector<Cache*> caches);
		
		bool creat(List const& list);
		bool creat(std::vector<List*> lists);
		
		getRandomText();
		
	private:
};

#endif //CACHE_H
