//! \file **************************************************************
//! \brief Header Action pour apprendre une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.4
//! \date 15.05.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_LEARN_H
#define ACTION_LEARN_H

#include "action.hpp"
#include "action/guiPanelActLearn.h"

#include <wx/event.h>
#include <wx/timer.h>

// *********************************************************************
// Class PanelActLearn
// *********************************************************************

class ActLearn;

//! \brief GUI pour la modification des préférences des actions pour apprendre une liste.
class PanelActLearn : public GuiPanelActLearn
{
	public:
		//! \brief Constructeur.
		//! \param parent wxWindow parent.
		//! \param buttonOK bouton "OK" du dialogue parent.
		//! \param act action a modifier.
		PanelActLearn(wxWindow* parent, wxButton* buttonOK, ActLearn* act);
		//! \brief Destructeur.
		~PanelActLearn();
		
		//! \brief Méthode appeler si appuis sur bouton "ok" du parent.
		//! Elle valide les modifications et les installe dans l'action
		void OnOKButtonClick(wxCommandEvent& event);
		
		void OnCheckBox(wxCommandEvent& event);
	
	private:
		//! \brief ActLearn à modifier.
		ActLearn* _act;
		
		//! \brief bouton "OK" du dialogue parent.
		wxButton* _buttonOK;
};


// *********************************************************************
// Class ActLearn
// *********************************************************************

//! \brief Action pour apprendre une liste.
class ActLearn : public wxTimer, public Action
{
	friend PanelActLearn;
	
	public:
		//! \brief Constructeur par défaut.
		ActLearn();
		//! \brief Constructeur.
		//! \param listName le non de la liste à apprendre.
		//! \param callTime temps d'appelle pour exécuter l'action.
		//! En minute et 0 pour ne jamais exécuter l'action au bout d'un temps.
		ActLearn(wxString const& listName, unsigned int callTime);
		//! \brief Constructeur par recopie.
		ActLearn(ActLearn const& other);
						
		//! \brief Destructeur.
		~ActLearn();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Obtenir le nom de la liste utiliser.
		wxString getListNameUsed()const;
		
		//! \brief Permet à l'action de s'auto exécuter.
		virtual void enable(bool enable = true);
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig & fileConfig)const;
		
		void Notify();
		
	private:
		//! \brief Nom de la liste de révision.
		wxString _listName;
		//! \brief Temps pour laquelle l'action est exécuter. En minute.
		unsigned int _callTime;
};

#endif //ACTION_LEARN_H