//! \file **********************************************************************
//! \brief Header 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

#ifndef EXPORTER_H
#define EXPORTER_H

//wxWidgets
#include <wx/wxWindow.h>
#include <wx/filename.h>

// *****************************************************************************
// Class Exporter
// *****************************************************************************

class Exporter
{
	public:
		//! \brief Constructeur.
		Exporter(wxFileName const& fileName);
		
		//! \brief destructeur.
		virtual ~Exporter();
		
		virtual void appendList(wxString const& listName, wxLanguage lgsrc, wxLanguage lgto)=0;
		virtual void appendText(wxString const& text, DataText const& dataText)=0;
		
	private:
};

// *****************************************************************************
// Class WinExporter
// *****************************************************************************

class WinExporter : public wxWindow 
{	
	public:
		WinExporter(wxWindow *parent, Exporter* exp);
		virtual ~WinExporter();
		
		virtual void applies()=0;
	
	protected:
		Exporter* _exp;
}; 

List for export:____________ |X|Filter:______________________________
   list1                       Nombre of Translation <= |0     |+-
   List2                       Knolege:___________________________
   Listtest                       |X|unconue   |X|unconue
                                  |X|unconue   |X|unconue
Export:____________________________________________________________
   O All.
   O The text and the main translation.
   O The text.
   
|v| Cvs (Comma-separated values) |
   Chose the tipe of seperator: |'c' (comma) |v|
   
Export in file:_____________________________________________________
   |Chose a directory to export				|
   File name: |             				|

#endif //EXPORTER_H
