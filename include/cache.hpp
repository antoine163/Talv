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

#include "listBase.hpp"

// *********************************************************************
// Class Cache
// *********************************************************************

//! \brief 
class Cache : public ListBase
{
	public:		
		//! \brief Constructeur.
		Cache();
				
		//! \brief Destructeur.
		virtual ~Cache();
		
		int addText(wxString const& text, DataText const& dataText);
		int getText(wxString const& text, DataText* dataText);
		int updateText(wxString const& text, DataText const& dataText);
		
		//! \brief Pour obtenir le cache sous forme de liste.
		Liste* getListe();
		
	private:
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool isEmptyFile()const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool isEmptyMemory()const;
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual void clearFile();
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual void clearMemory();
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool removeTextFile(wxString const& text);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool removeTextMemory(wxString const& text);
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool existTextFile(wxString const& text)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool existTextMemory(wxString const& text)const;
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool loadFile(wxFileName const& fileName);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool loadMemory(wxFileName const& fileName);
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool saveFile(wxFileName const& fileName)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool saveMemory(wxFileName const& fileName)const;
		
		std::vector<DataText> _texts;
};

#endif //CACHE_H
