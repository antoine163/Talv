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
				
		//! \brief destructeur.
		virtual ~Cache();
		
		//int addText(	wxString const& text,
						//wxString const& mainTranslation);
		
		//int addText(	wxString const& text,
						//wxString const& mainTranslation,
						//std::map<wxString, wxArrayString> const& translations);
						
		//int addText(	wxString const& text,
						//Knowledge_e knowledge,
						//unsigned int nbTranslation,
						//wxString const& mainTranslation,
						//std::map<wxString, wxArrayString> const& translations);
						
						
						
		//int getText(	wxString const& text,
						//wxString* mainTranslation);
		
		//int getText(	wxString const& text,
						//wxString* mainTranslation,
						//std::map<wxString, wxArrayString>* translations);
		
		//int getText(	wxString const& text,
						//Knowledge_e knowledge,
						//unsigned int nbTranslation,
						//wxString* mainTranslation,
						//std::map<wxString, wxArrayString>* translations);
						
						
						
		//int updateText(	wxString const& text,
						//wxString const& mainTranslation,
						//std::map<wxString, wxArrayString> const& translations);
						
		//int updateText(	wxString const& text,
						//wxString const& mainTranslation,
						//std::map<wxString, wxArrayString> const& translations);
						
		//int updateText(	wxString const& text,
						//Knowledge_e knowledge,
						//unsigned int nbTranslation,
						//wxString const& mainTranslation,
						//std::map<wxString, wxArrayString> const& translations);
						
		//int getKnowledge(wxString const& text, Knowledge_e* knowledge);
		//int updateKnowledge(wxString const& text, Knowledge_e knowledge);
		
		//int updateNbTranslation(wxString const& text, unsigned int nbTranslation);
		//int updateNbTranslation(wxString const& text, unsigned int nbTranslation);
		
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
		
		virtual bool saveFile(wxFileName const& fileName)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
		virtual bool saveMemory(wxFileName const& fileName)const;
		//! \brief Implémentassions à partir de \ref ListBase
		//! \see ListBase
};

#endif //CACHE_H
