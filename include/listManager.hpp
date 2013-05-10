//! \file **************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include "singleton.hpp"
#include "list.hpp"

#include <wx/fileconf.h>
#include <wx/arrstr.h>
#include <vector>

// *********************************************************************
// Class ListManager
// *********************************************************************

//! \brief Gestion des listes
class ListManager : public Singleton<ListManager>
{
	friend class Singleton<ListManager>;
	
	public:	
		//! \brief Charger les listes à partir du fichier de config.
		void load(wxFileConfig & fileConfig);
		
		//! \brief Sauvegarde des listes dans le fichier de config.
		void save(wxFileConfig & fileConfig)const;
		
		//! \brief Obtenir une lite en fonction de son nom.
		//!
		//! Une bonne utilisation serai d'éviter d'affecter le pointeur 
		//! retourner a une variable pour une utilisation ultérieur.
		//! Une utilisation directe du pointeur est préférable.
		//! Par exemple dans un bock de code.
		//! Tout de mois si vous ne fait pas cela, fait attention a ce que
		//! la méthode \ref remove() ne sois pas appeler avec le non de
		//! la liste que vous utilisez. Sent quoi vous vous retrouveriez
		//! avec un pointeur non valide.
		//! \param name le non de la liste à obtenir.
		//! \return nullptr si la liste n'a pas été trouver.
		List* getList(wxString const& name);
		
		//! \brief Obtenir le nom de touts les lites.
		//! \return le nom de tout les listes.
		wxArrayString getNameLists()const;
		
		//! \brief Obtenir le nom de touts les lites en fonction de leur lange.
		//! \return le nom de tout les listes.
		wxArrayString getNameListsByLanguages(	wxString const& lgsrc,
												wxString const& lgto)const;
		
		//! \brief Pour connaître si une liste existe.
		//! \return true si elle existe, sinon false.
		bool exist(wxString const& name)const;
		
		//! \brief Créer une nouvelle liste.
		//! Les paramètres \b lgsrc et \b lgto doive être écrit en abrégé.
		//! ex: pour le français "fr" ex: pour l'anglais "en".
		//! \param name le non de la liste à créer.
		//! \param lgsrc langue de source.
		//! \param lgto langue de traduction.
		//! \return nullptr si la liste n'a pas été créé. Dans ce cas 
		//! Il est probable que la liste est déjà existent.
		List* create(	wxString const& name,
						wxString const& lgsrc,
						wxString const& lgto);
					
		//! \brief Supprimer une liste.
		//!
		//! Supprimer aussi le fichier associer à la liste.
		//! \param name le non de la liste à supprimer.
		//! \return true si la liste a bien été supprimer. false si la
		//! liste n'est pas existante.
		bool remove(wxString const& name);

	private:
		//! \brief Constructeur.
		ListManager();
		//! \brief destructeur.
		virtual ~ListManager();
		
		//! \brief Les différente listes.
		std::vector<List*> _lists;
};

#endif //LIST_MANAGER_H
