//! \file **************************************************************
//! \brief Header editableByPanel.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 25.09.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef EDITABLE_BY_PANEL_H
#define EDITABLE_BY_PANEL_H

#include <wx/panel.h>

// *********************************************************************
// Class EditableByPanel
// *********************************************************************

//! \brief Pour configurer des trucs dans les préférence via un panel.
//!
//! Tout classes voulant se faire éditer via un panel dans les
//! préférences devra hériter de cette classe.
class EditableByPanel
{	
	public:
		//! \brief Constructeur.
		//! \param name non du panel.
		EditableByPanel(wxString const& name);
		//! \brief Destructeur.
		virtual ~EditableByPanel();
		
		//! \brief Cette méthode devra crées et retourner le panel.
		//!
		//! \param parent du panel.
		//! \return nullptr devra être retourner si le panel a déjà été créé. 
		virtual wxPanel* openEditPanel(wxWindow *parent)=0;
		
		//! \brief Permet de fermer le panel.
		void closeEditPanel();
		
		//! \brief Cette méthode devra vérifier la cohérence des modifications
		//! apporter par le panel.
		//! \return true si pas de problème.
		virtual bool check()const=0;
		
		//! \brief Cette méthode devra appliquer les modifications
		//! apporter par le panel.
		//! \return Si false est retourner alors les modifications du panel
		//! ne son pas valide et elle ne seront pas appliquer.
		virtual bool apply()=0;
		
		
		//! \brief Retourne le non de l'onglet (dans les préférences).
		const wxString& getName()const;
	
	protected:
		wxPanel* _panel;
		wxString _name;
		
	private:
};

#endif //EDITABLE_BY_PANEL_H
