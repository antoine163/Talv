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


#include "def.hpp"
#include "dataText.hpp"

#include <wx/filename.h>
#include <wx/file.h>

#include <map>

// *********************************************************************
// Class Cache
// *********************************************************************

//! \brief 
class Cache
{
	public:		
		//! \brief Constructeur.
		Cache();
				
		//! \brief Destructeur.
		virtual ~Cache();
		
		Status_e getLanguages(wxString* lgsrc, wxString* lgto)const;
		Status_e setLanguages(wxString const& lgsrc, wxString const& lgto);
		Status_e isEmpty()const;
		Status_e clear();
		
		Status_e existText(wxString const& text)const;
		Status_e addText(wxString const& text, DataText const& dataText);
		Status_e updateText(wxString const& text, DataText const& dataText);
		
		Status_e replaceTexts(std::map<wxString, DataText> const& texts);
		
		Status_e getTexts(wxArrayString* texts);//+ les filtres
		Status_e getDataTexts(std::map<wxString, DataText>* texts);//+ les filtres
		
	private:
		Status_e readTextInFile(	wxFile& file,
									wxString* text,
									DataText* data)const;
		Status_e writeTextInFile(	wxFile& file,
									wxString const&text,
									DataText const& data);

		//! \brief Fichier du cache.
		wxFileName _fileName;
};

#endif //CACHE_H
