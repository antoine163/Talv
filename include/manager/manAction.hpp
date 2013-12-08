//! \file **********************************************************************
//! \brief Header Gestion des actions/raccourcis
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 3.0
//! \date 20.03.2013
//!
//! ****************************************************************************

#ifndef MAN_ACTION_H
#define MAN_ACTION_H

//App
#include "manager.hpp"
#include "control/controlDataList.hpp"

// *****************************************************************************
// Class ManAction
// *****************************************************************************

//! \ingroup manager, action
//! \brief ManAction
class ManAction : public Manager
{
	DECLARE_MANAGER(ManAction);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

// *****************************************************************************
// Class WinManAction
// *****************************************************************************

//! \brief WinManAction
class WinManAction : public wxWindow
{
	public:
		WinManAction(wxWindow* parent);
		~WinManAction();
	
	private:
		ControlDataList* _controlDataList;
};


#endif //MAN_ACTION_H
