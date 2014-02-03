//! \file **********************************************************************
//! \brief Header Action exécute une ligne de commande.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 03.02.2014
//!
//! ****************************************************************************

#ifndef ACTION_LAUNCHER_H
#define ACTION_LAUNCHER_H

//App
#include "action.hpp"

//WxWidgets
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/button.h>

// *****************************************************************************
// Class ActLauncher
// *****************************************************************************

//! \brief Action exécute une ligne de commande.
class ActLauncher : public Action
{	
	DECLARE_ACTION();
	
	public:
		//! \brief Constructeur par défaut.
		ActLauncher();
						
		//! \brief Destructeur.
		~ActLauncher();
		
		//! \brief Obtenir le window gui pour éditer l'action.
		//! \param parent est le parent du window.
		//! \note Cette méthode crées un window et retourne le pointeur sur se window, il faudra prévoir de libérai la mémoire.
		WinAction* newEditWindow(wxWindow* parent);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Exécuter l'action.
		void execute();
		
		wxString getCommand()const;
		void setCommand(wxString const& command);
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig& fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig& fileConfig)const;
		
	private:
		wxString _command;
};

// *****************************************************************************
// Class WinActLauncher
// *****************************************************************************

//! \brief GUI pour la modification des préférences des actions de lancement \ref ActLauncher.
class WinActLauncher : public WinAction
{
	public:
		//! \brief Constructeur.
		WinActLauncher(wxWindow* parent, ActLauncher const* act);
		//! \brief Destructeur.
		~WinActLauncher();
		
		virtual void refreshActionFromGui();
	
	private:
		void onPickExeFile(wxCommandEvent& event);
	
		wxTextCtrl* _textCtrlCommand;
		wxButton* _buttonPickExeFile;
};

#endif //ACTION_LAUNCHER_H
