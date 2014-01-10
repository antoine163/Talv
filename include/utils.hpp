//! \file **********************************************************************
//! \brief Header TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 09.01.2014
//!
//! ****************************************************************************

#ifndef UTILS_H
#define UTILS_H

//WxWidgets
#include <wx/sizer.h>
#include <wx/window.h>

void enableWindowsFromSizer(wxSizer* sizer, bool enable = true);
void disableWindowsFromSizer(wxSizer* sizer);

#endif //UTILS_H
