//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.01.2014
//!
//! ****************************************************************************

#ifndef STATIC_BOX_H
#define STATIC_BOX_H

//WxWidgets
#include <wx/control.h>

// *****************************************************************************
// Class StaticBox
// *****************************************************************************

class StaticBox : public wxControl
{	
	public:
		StaticBox(	wxWindow *parent,
					wxWindowID id,
					const wxString &label,
					const wxPoint &pos=wxDefaultPosition,
					const wxSize &size=wxDefaultSize,
					long style=0,
					const wxString &name=wxStaticBoxNameStr);
		virtual ~StaticBox();
	private:
};

#endif //STATIC_BOX_H
