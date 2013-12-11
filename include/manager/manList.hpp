//! \file **********************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ****************************************************************************

#ifndef MAN_LIST_H
#define MAN_LIST_H

//App
#include "manager.hpp"
#include "control/ctrlDataList.hpp"

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup manager
//! \brief ManList
class ManList : public Manager
{
	DECLARE_MANAGER(ManList);
	
	public:
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

// *****************************************************************************
// Class WinManList
// *****************************************************************************

//! \brief WinManList
class WinManList : public WinManager
{
	public:
		WinManList(wxWindow* parent);
		~WinManList();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		CtrlDataList* _ctrlDataList;
};

#endif //MAN_LIST_H
