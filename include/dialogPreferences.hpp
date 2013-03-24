//version : 1.1
//02.01.2013

#ifndef DIALOG_PREFERENCES_H
#define DIALOG_PREFERENCES_H

#include "guiDialogPreferences.h"
#include "actionManager.hpp"

#include <map>

class DialogPreferences : public GuiDialogPreferences 
{
	public:
		
		DialogPreferences(ActionManager *actionManager);
		~DialogPreferences();
		
		//! \brief Supprimer une action.
		void OnButtonClickActDelete(wxCommandEvent&);
		//! \brief Configurai une action une action.
		void OnButtonClickActPreferences(wxCommandEvent&);
		//! \brief Ajouter une action une action.
		void OnButtonClickActAdd(wxCommandEvent&);
		
		//! \brief Applique les modifications.
		void OnButtonClickApply(wxCommandEvent&);
		//! \brief Applique les modifications est quitte le dialog.
		void OnButtonClickOK(wxCommandEvent&);
		
		//! \brief Pour savoir si le bouton shutdown et actionner.
		bool shutdownIsToggle()const;
		
		//! \brief Pour savoir si le boite de l'afficha de l'icône de l'application est cocher ou pas.
		bool showIcon()const;
		
	protected:		
		ActionManager *_actionManager;
};

#endif //DIALOG_PREFERENCES_H
