//! \file **************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.17
//! \date 02.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include "editableByPanel.hpp"
#include "singleton.hpp"
#include "managerBase.hpp"
#include "list.hpp"
#include "panelList.hpp"

#include <wx/fileconf.h>

// *********************************************************************
// Class PanelListLists
// *********************************************************************

//! \brief Panel la liste de listes.
class PanelListLists : public PanelList 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		PanelListLists(wxWindow* parent);
		//! \brief Destructeur.
		virtual ~PanelListLists();
		
		//! \brief Mise à jour de l'affichage de la liste avec \ref EditListManager
		virtual void Update();
		
	private:		
		//! \brief Suppression de la liste.
		bool OnDeleteItem(wxString const& item);
		//! \brief Préférence de la liste.
		wxArrayString OnPreferencesItem(wxString const& item);
		//! \brief Ajouter d'une liste.
		wxArrayString OnAddItem();
		
		//! \brief Les liste nouvellement ajouter.
		wxArrayString _newLists;
		//! \brief Les liste nouvellement supprimer.
		wxArrayString _deleteLists;
};

// *********************************************************************
// Class ListManagerBase
// *********************************************************************

//! \brief Gestion des listes
class ListManagerBase : public ManagerBase<wxString, List>
{	
	public:	
		//! \brief Constructeur.
		ListManagerBase();
		//! \brief destructeur.
		virtual ~ListManagerBase();

		//! \brief Crées et ajout à la liste.
		//! \param ListName le non de la liste.
		//! \param lgsrc le langage source de la liste.
		//! \param lgto le langage de traduction de la liste.
		//! \return true si la liste à put être crée et ajouter.
		bool createAndAddList(	wxString const &listName,
								wxString const &lgsrc,
								wxString const &lgto);
		
		//! \brief Obtenir le nom de touts les lites.
		//! \return le nom de tout les listes.
		wxArrayString getNameLists()const;
		
		//! \brief Obtenir le nom de touts les lites en fonction de leur lange.
		//! \return le nom de tout les listes.
		wxArrayString getNameListsByLanguages(	wxString const& lgsrc,
												wxString const& lgto)const;
		
		//! \brief Path de travaille du manager.					
		virtual wxString getPath()=0;

	private:
};

// *********************************************************************
// Class ListManager
// *********************************************************************

//! \brief Gestion des listes
class ListManager : public ListManagerBase,
					public Singleton<ListManager>,
					public EditableByPanel
{
	friend class Singleton<ListManager>;
	
	public:	
		//! \brief Charger les listes à partir du fichier de config.
		void load(wxFileConfig& fileConfig);
		
		//! \brief Sauvegarde des listes dans le fichier de config.
		void save(wxFileConfig& fileConfig)const;
		
		//! \brief Pour obtenir une liste. Avec affichage d'un dialogue
		//! si la liste n'excite pas. (A appeler dans les Actions).
		//!
		//! Dans le cas où la liste n'exciterais pas, un dialogue
		//! apparentera en demandent à l'utilisateur de bien vouloir
		//! surprime l'action qui demande la liste.
		//!
		//! \param listName le nom de la liste.
		//! \param actionName le non de l'action dans le cas où la liste 
		//! n'existe pas.
		//! \return nullptr si la liste n'existe pas.
		List* getListCheckDialog(	wxString const& listName,
									wxString const& actionName);
		
		//! \brief Path de travaille du manager.
		//! C'est un dossier utilisateur.
		wxString getPath();
		
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual wxPanel* newEditPanel(wxWindow *parent);
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelCheck()const;
		//! \brief Implémentassions de \ref EditableByPanel.
		virtual bool panelApply();

	private:
		//! \brief Constructeur.
		ListManager();
		//! \brief destructeur.
		virtual ~ListManager();
};

 //*********************************************************************
 //Class EditActionManager
 //*********************************************************************

class EditListManager : public ListManagerBase, public Singleton<EditListManager>
{	
	friend class Singleton<EditListManager>;
	
	public:
		//! \brief Initialisation à partir de ListManager
		void init();
		
		//! \brief Applique à ListManager
		void apply();

		//! \brief Path de travaille du manager.
		//! C'est un dossier temporaire.
		wxString getPath();
		
	private:
		//! \brief Constructeur.
		EditListManager();
		
		//! \brief destructeur.
		virtual ~EditListManager();
};

#endif //LIST_MANAGER_H
