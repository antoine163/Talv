//! \file **********************************************************************
//! \brief Header Dialogue pour choisie la traduction principale d'un texte.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 06.02.2014
//!
//! ****************************************************************************

#ifndef DLG_PICK_TRANSLATION_H
#define DLG_PICK_TRANSLATION_H

//App
#include "dataText.hpp"

//WxWidgets
#include <wx/dialog.h>
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>

// *****************************************************************************
// Class DlgPickTranslation
// *****************************************************************************

class DlgPickTranslation : public wxDialog 
{
	public:
		
		//! \brief Constructeur.
		DlgPickTranslation(wxWindow* parent, wxString const& text, DataText const& translations);
		//! \brief Destructeur.
		~DlgPickTranslation();
		
		wxString getTranslation();
		
	private:
		void onButton(wxCommandEvent& event);
		
		wxTextCtrl* _textCtrlTranslation;
};

#endif //DLG_PICK_TRANSLATION_H
