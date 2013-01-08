//02.01.2013

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include "gui/guiDialogPreferences.h"
#include "shortcut.hpp"
#include "action.hpp"

class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		DialogPreferences(std::map<ShortcutKey, Action*> const& shortcutAction);
		~DialogPreferences();
		
	private:
};

#endif //DIALOG_PREFERENCES_H
