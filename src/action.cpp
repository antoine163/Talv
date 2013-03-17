//04.01.2013
//v 0.2

#include "action.hpp"

#include <wx/clipbrd.h>

Action::Action(wxString const& actName)
: _actShortcutKey(nullptr), _actName(actName)
{
}

Action::~Action()
{
}

wxString Action::getActName()const
{
	return _actName;
}

ShortcutKey Action::getShortcutKey()const
{
	return *_actShortcutKey;
}

void Action::setShortcutKey(ShortcutKey const& shortcutKey)
{
	if(_actShortcutKey != nullptr)
		delete _actShortcutKey;
		
	_actShortcutKey = new ShortcutKey(shortcutKey);
	
}		
