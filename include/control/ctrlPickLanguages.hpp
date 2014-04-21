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
		//! \param simple permet de choisie si le contrôle dois prendre en compte
		//! deux l'engages (simple=false) ou un seul (simple=true).
		CtrlPickLanguages(wxWindow* parent, bool simple = false);
		//! \brief Constructeur.
		//! Métra implicitement simple à false.
		CtrlPickLanguages(	wxWindow* parent,
							wxLanguage lgsrc,
							wxLanguage lgto);
		//! \brief Constructeur.
		//! Métra implicitement simple à true.
		CtrlPickLanguages(	wxWindow* parent,
							wxLanguage lg);
							
		//! \brief Destructeur.
		virtual ~CtrlPickLanguages();
		
		//! \brief Obtenir les langages.
		//! Utilisable seulement en mode deux l'engages (simple=false).
		void getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const;
		//! \brief Modifier les langages.
		//! Utilisable seulement en mode deux l'engages (simple=false).
		void setLanguages(wxLanguage lgsrc, wxLanguage lgto);
		
		//! \brief Obtenir le langage.
		//! Utilisable seulement en mode un l'engage (simple=true).
		void getLanguage(wxLanguage* lg)const;
		//! \brief Modifier le langage.
		//! Utilisable seulement en mode un l'engage (simple=true).
		void setLanguage(wxLanguage lg);

	private:
		void creatCtrlPickLanguages(wxLanguage lgsrc, wxLanguage lgto);
		void creatCtrlPickLanguage(wxLanguage lg);
	
		bool _simple;
		wxComboBox* _comboBoxLgsrc;
		wxComboBox* _comboBoxLgto;
};

#endif //CTRL_PICK_LANGUAGES_H
