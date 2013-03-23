//04.01.2013
//v 0.3

#ifndef ACTION_H
#define ACTION_H

#include <wx/string.h>

//! \brief Class de base pour les actions.
//! \attention Dans les classes fille il faudra probablement prévoie un constructeur par recopie.
class Action
{
	public:		
		//! \brief Constructeur.
		Action();
		
		//! \brief destructeur.
		//! \todo à implémenter correctement avec la gestion mémoire de _actShortcutKey.
		virtual ~Action();
		
		//! \brief Permet d'exécuter l'action.
		virtual void execute()=0;
		
		//! \brief Permet d'extraire les préférences de l'action au format string,
		//! dans le but des les affichées à l'utilisateur.
		virtual wxString getStringPreferences()=0;
	
	private:
};

#endif //ACTION_H
