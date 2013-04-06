//! \file **************************************************************
//! \brief Header Dialogue pour les préférences d'une action et sont
//! raccourci associer.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.4
//! \date 02.01.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef DIALOG_SHORTCUT_PREFERENCES_H
#define DIALOG_SHORTCUT_PREFERENCES_H

#include "guiDialogActionPreferences.h"

#include "action.hpp"
#include "shortcut.hpp"

// *********************************************************************
// Enum RawKeyCodeModifier_e
// *********************************************************************

//! \brief Codes des modificateurs.
enum RawKeyCodeModifier_e
{
	#if defined(__UNIX__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 37,
	RAW_KEY_CODE_MODIFIER_ALT 		= 64,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 50,
	RAW_KEY_CODE_MODIFIER_SUPER		= 133,
	#elif defined(__WXMSW__)
	RAW_KEY_CODE_MODIFIER_CONTROL 	= 17,
	RAW_KEY_CODE_MODIFIER_ALT 		= 18,
	RAW_KEY_CODE_MODIFIER_SHIFT 	= 16,
	RAW_KEY_CODE_MODIFIER_SUPER		= 91,
	#endif
};

// *********************************************************************
// Class DialogActionPreferences
// *********************************************************************

//! \brief Dialogue pour les préférences d'une action et sont raccourci associer.
class DialogActionPreferences : public GuiDialogActionPreferences 
{
	public:
		
		//! \brief Constructeur.
		//! \param parent parent du dialogue.
		DialogActionPreferences(wxWindow* parent);
		//! \brief Constructeur avec une action et un raccourci par défaut.
		//! \param parent parent du dialogue.
		//! \param inShortcutKey le raccourcis de l'action.
		//! \param inAct l'action à modifier.
		DialogActionPreferences(	wxWindow* parent,
									ShortcutKey const& inShortcutKey,
									Action const& inAct);
		//! \brief Destructeur.
		~DialogActionPreferences();
		
		//! \brief Obtenir le raccourci.
		ShortcutKey getShortcutKey()const;
		
	protected:
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
		void OnLeftDown(wxMouseEvent&);
		void OnKillFocus(wxFocusEvent&);
		void OnOKButtonClick(wxCommandEvent& event);
		
		void OnChoiceAction(wxCommandEvent& event);
		
		void setUpAction(wxString const& actTypeName);
		
		//! \brief Mise a jour du texte dans le TextCtrlChortcut.
		void updateTextCtrlChortcut(wxChar key);
		
	private:
		//! \brief L'action à modifier.
		Action * _action;
		
		bool _keyCtrlIsPressed;
		bool _keyAltIsPressed;
		bool _keyShiftIsPressed;
		bool _keySuperIsPressed;
		
		//! \brief Pour savoir si le raccourci qui est presser et valide.
		bool _shortKeyIsValide;
};

#endif //DIALOG_SHORTCUT_PREFERENCES_H
