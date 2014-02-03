//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.01.2014
//!
//! ****************************************************************************

#ifndef CTRL_PICK_LANGUAGES_H
#define CTRL_PICK_LANGUAGES_H

//WxWidgets
#include <wx/window.h>
#include <wx/string.h>
#include <wx/combobox.h>
#include <wx/language.h>
#include <wx/arrstr.h>

// *****************************************************************************
// Class CtrlPickLanguages
// *****************************************************************************

class CtrlPickLanguages : public wxWindow
{
	public:
		//! \brief Constructeur.
		CtrlPickLanguages(wxWindow* parent);
		//! \brief Constructeur.
		CtrlPickLanguages(	wxWindow* parent,
							wxLanguage lgsrc,
							wxLanguage lgto);
		//! \brief Destructeur.
		virtual ~CtrlPickLanguages();
		
		void getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const;
		void setLanguages(wxLanguage lgsrc, wxLanguage lgto);

	private:
		wxComboBox* _comboBoxLgsrc;
		wxComboBox* _comboBoxLgto;
};

#endif //CTRL_PICK_LANGUAGES_H
