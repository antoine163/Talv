//version : 1.0
//02.01.2013

#ifndef DIALOG_SHORTCUT_PREFERENCES_H
#define DIALOG_SHORTCUT_PREFERENCES_H

#include "guiDialogShortcutPreferences.h"

#include "action.hpp"

class DialogShortcutPreferences : public GuiDialogShortcutPreferences 
{
	public:
		
		DialogShortcutPreferences(wxWindow* parent, Action const* inAct = nullptr);
		~DialogShortcutPreferences();
		
	protected:		
};

#endif //DIALOG_SHORTCUT_PREFERENCES_H
