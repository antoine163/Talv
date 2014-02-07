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

// *****************************************************************************
// Class CtrlTextFilter
// *****************************************************************************

class CtrlTextFilter : public wxWindow
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		CtrlTextFilter(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~CtrlTextFilter();

	private:
};

#endif //CTRL_TEXT_FILTER_H
