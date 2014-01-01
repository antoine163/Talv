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
#include <wx/choice.h>

// *****************************************************************************
// Class CtrlPickLanguages
// *****************************************************************************

class CtrlPickLanguages : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlPickLanguages(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~CtrlPickLanguages();

	private:
		wxChoice* _choiceLgsrc;
		wxChoice* _choiceLgto;
};

#endif //CTRL_PICK_LANGUAGES_H
