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
#include "shortcut.hpp"
#include "control/ctrlDataList.hpp"

// *****************************************************************************
// Class ManAction
// *****************************************************************************

//! \ingroup manager, action
//! \brief ManAction
class ManAction : public Manager, public wxEvtHandler
{
	DECLARE_MANAGER(ManAction);
	
	public:
		//! \brief newEditWindow
		//! \return  \ref WinManAction
		//! \see WinManAction
		virtual WinManager* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		void onShortcut(ShortcutEvent& event);
		
		//! \brief Gestion des raccourcis.
		Shortcut _shortcut;
};

// *****************************************************************************
// Class WinManAction
// *****************************************************************************

//! \brief WinManAction
class WinManAction : public WinManager
{
	public:
		WinManAction(wxWindow* parent);
		~WinManAction();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onPreferences(wxCommandEvent& event);
		
		CtrlDataList* _ctrlDataList;
};


#endif //MAN_ACTION_H
