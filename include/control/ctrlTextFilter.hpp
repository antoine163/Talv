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

#ifndef CTRL_TEXT_FILTER_H
#define CTRL_TEXT_FILTER_H

//App
#include "textFilter.hpp"

//WxWidgets
#include <wx/window.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>

// *****************************************************************************
// Class CtrlTextFilter
// *****************************************************************************

class CtrlTextFilter : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlTextFilter(wxWindow* parent, TextFilter const& filter = TextFilter(KNOWLEDGE_ALL, 0));
		//! \brief Destructeur.
		virtual ~CtrlTextFilter();
		
		void setFilter(TextFilter const& filter);
		TextFilter getFilter();

	private:
		wxSpinCtrl* _spinCtrlWeight;
		wxCheckBox* _checkBoxUnknown;
		wxCheckBox* _checkBoxLittleKnown;
		wxCheckBox* _checkBoxKnown;
		wxCheckBox* _checkBoxVeryKnown;
};

#endif //CTRL_TEXT_FILTER_H
