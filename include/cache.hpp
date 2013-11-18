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
		
		
		void getLanguages(wxString* lgsrc, wxString* lgto)const;
		void setLanguages(wxString const& lgsrc, wxString const& lgto);
		
		void clear();
		
		//! \brief Pour savoir si le cache est vide ou pas.
		bool isEmpty();
		
		int addText(	wxString const& text,
						wxString const& mainTranslation);
		
		int addText(	wxString const& text,
						wxString const& mainTranslation,
						std::map<wxString, wxArrayString> const& translations);
		
		bool removeText(wxString const& text);
		
	private:
};

#endif //CACHE_H
