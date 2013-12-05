//! \file **********************************************************************
//! \brief Header TaskIcon.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
//! \date 10.12.12
//!
//! ****************************************************************************

#ifndef TASK_ICON_H
#define TASK_ICON_H

//WxWidgets
#include <wx/taskbar.h>

//! \todo implémenter avec managerGeneral
#define FILE_NAME_APP_ICONS "icons/16x16/" PROJECT_NAME ".png"

// *****************************************************************************
// Class TaskIcon
// *****************************************************************************

//! \brief Menu dans la zone de notification.
class TaskIcon : public wxTaskBarIcon
{
	public:
		TaskIcon(wxTaskBarIconType iconType=wxTBI_DEFAULT_TYPE);
		~TaskIcon();
		
	protected:
		virtual	wxMenu* CreatePopupMenu();

	private:
};

#endif //TASK_ICON_H
