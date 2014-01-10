//! \file **********************************************************************
//! \brief Source TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 09.01.2014
//!
//! ****************************************************************************

//App
#include "utils.hpp"

//Stl
#include <vector>

void enableWindowsFromSizer(wxSizer* sizer, bool enable)
{
	for(auto it: sizer->GetChildren())
	{
		if(it->IsWindow())
			it->GetWindow()->Enable(enable);
		else if(it->IsSizer())
			enableWindowsFromSizer(it->GetSizer(), enable);
	}
}

void disableWindowsFromSizer(wxSizer* sizer)
{
	enableWindowsFromSizer(sizer, false);
}
