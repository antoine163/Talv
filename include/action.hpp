//04.01.2013
//v 0.2

#ifndef ACTION_H
#define ACTION_H

#include <wx/string.h>
#include "shortcut.hpp"

//! \brief Class de base pour les actions.
//! Une action est exécuter par l'intermédiaire d'un raccourci (ShortcutKey).
class Action
{
	public:		
		//! \brief Constructeur.
		//! \param actName c'est le non de l'action au forma string. Les classe enfant ne devrai pas le passer en paramètre mais juste l'initialiser.
		//! \param actName c'est le non de l'action au forma string. Les classe enfant ne devrai pas le passer en paramètre mais juste l'initialiser.
		Action(wxString const& actName);
		
		//! \brief destructeur.
		//! \todo à implémenter correctement avec la gestion mémoire de _actShortcutKey.
		virtual ~Action();
		
		//! \brief Obtenir le non de l'action.
		//! \return Le non de l'action.
		wxString getActName()const;
		
		//! \brief Permet d'exécuter l'action.
		virtual void execute()=0;
		
		//! \brief Permet d'extraire les préférences de l'action au format string,
		//! dans le but des les affichées à l'utilisateur.
		virtual wxString getStringPreferences()=0;
		
		//! \brief Obtenir le raccourci (ShortcutKey).
		ShortcutKey getShortcutKey()const;
		
		//! \brief Modifier le raccourci (ShortcutKey).
		void setShortcutKey(ShortcutKey const& shortcutKey);
	
	private:
		//! \brief Le accourci.
		ShortcutKey* _actShortcutKey;
		
		//! \brief Le non de l'action.
		wxString _actName;
};

#endif //ACTION_H
