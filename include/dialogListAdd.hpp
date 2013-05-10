//! \file **************************************************************
//! \brief Header Dialogue pour ajouter une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 09.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DIALOG_LIST_ADD_H
#define DIALOG_LIST_ADD_H

#include "guiDialogListAdd.h"


// *********************************************************************
// Class DialoglistAdd
// *********************************************************************

//! \brief Dialogue pour ajouter une lise.
class DialogListAdd : public GuiDialogListAdd 
{
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parent.
		DialogListAdd(wxWindow* parent);
		
		//! \brief Destructeur.
		virtual ~DialogListAdd();
		
		//! \brief Récupérée le nom de la liste.
		wxString getNamelist()const;
		
		//! \brief Récupérée les deux langues de la liste.
		void getlanguages(wxString* lgsrc, wxString* lgto)const;

	private:
};

#endif //DIALOG_LIST_ADD_H
