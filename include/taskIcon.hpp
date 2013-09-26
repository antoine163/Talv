//! \file **************************************************************
//! \brief Header TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.7
//! \date 10.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#ifndef TASK_ICON_H
#define TASK_ICON_H

#include <wx/menu.h>
#include <wx/taskbar.h>

// *********************************************************************
// Class TaskIcon
// *********************************************************************

//! \brief Menu dans la zone de notification.
class TaskIcon : public wxTaskBarIcon
{
	public:
		TaskIcon(wxTaskBarIconType iconType=wxTBI_DEFAULT_TYPE);
		~TaskIcon();
		
		//! \brief Méthode appeler lorsque l'item Preference dans le menu à été cliquer.
		//! Cette méthode lance le dialogue des préférences.
		void OnPreferences(wxCommandEvent&);
		//! \brief Méthode appeler lorsque l'item EnableShortcuts dans le menu à été cliquer.
		//! Cette méthode désactive ou active tout les raccourcis qui on été enregistre auprès de \ref _actionManager.
		void OnEnableShortcuts(wxCommandEvent& event);
		//! \brief Méthode appeler lorsque l'item About dans le menu à été cliquer.
		//! Cette méthode lance le dialogue About.
		void OnAbout(wxCommandEvent&);
		
	protected:
		virtual	wxMenu* CreatePopupMenu();

	private:
		int _idEnableShortcuts;
		bool _enableShortcuts;
};

#endif //TASK_ICON_H
