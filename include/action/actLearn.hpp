//! \file **************************************************************
//! \brief Header Action pour apprendre une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.8
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
#include "list.hpp"

#include <wx/event.h>
#include <wx/timer.h>

// *********************************************************************
// Lnum StatusAnswer_e
// *********************************************************************
//! \brief Les différentes connaissances.
enum StatusAnswer_e
{
	STATUS_ANSWER_NO_CHECK	= 0,
	STATUS_ANSWER_NO		= 1,
	STATUS_ANSWER_CORRECT	= 2,
	STATUS_ANSWER_BAD		= 3
};

// *********************************************************************
// Class DialogActLearn
// *********************************************************************

class DialogActLearn : public GuiDialogActLearn
{
	public:
		//! \brief Constructeur.
		//! \param parent wxWindow parent.
		//! \param listName le non de la liste à apprendre.
		//! \param nbText Le nombre de texte a apprendre.
		//! Valeur minimum 1. Si vous préciser 0 c'est comme si vous préciser 1.
		DialogActLearn(wxWindow* parent, wxString const& listName, unsigned int nbText);
		//! \brief Destructeur.
		~DialogActLearn();
		
		int ShowModal();
		
	protected:
	
		bool nextText();
		void checkNextAnswer();
		
		void OnButtonClickPropose(wxCommandEvent& event);
		void OnTextAnswer(wxCommandEvent& event);
		void OnTextEnterAnswer(wxCommandEvent& event);
		void OnChoiceKnowledge(wxCommandEvent& event);
		void OnButtonClickDelete(wxCommandEvent& event);
		void OnButtonClickCheck(wxCommandEvent& event);
		
	private:
		//! \brief Nom de la liste de révision.
		wxString _listName;
		
		//! \brief Le nombre de texte à apprendre.
		//! \note La valeur minimum est 1.
		unsigned int _nbText;
		
		//! \brief Le numéro du texte actuellement afficher.
		unsigned int _iNbText;
		
		wxString _lgsrc;
		wxString _lgto;
		wxString _guilgsrc;
		wxString _guilgto;
		
		wxString _textAnswer;
		
		bool _choiceSrc;
		StatusAnswer_e _statusAnswer;
		
		wxString _text;
		wxString _mainTranslate;
		int _indexTextKnowledge;
		Knowledge_e _knowledge;
};

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
class ActLearn : protected wxTimer, public Action
{
	friend PanelActLearn;
	
	public:
		//! \brief Constructeur par défaut.
		ActLearn();
		//! \brief Constructeur.
		//! \param listName le non de la liste à apprendre.
		//! \param nbText Le nombre de texte a apprendre pour chaque exécution de cette action.
		//! Valeur minimum 1. Si vous préciser 0 c'est comme si vous préciser 1.
		//! \param callTime temps d'appelle pour exécuter l'action.
		//! En minute et 0 pour ne jamais exécuter l'action au bout d'un temps.
		ActLearn(wxString const& listName, unsigned int nbText, unsigned int callTime);
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
		//! \brief Le nombre de texte a apprendre pour chaque exécution de cette action.
		//! \note La valeur minimum est 1.
		unsigned int _nbText;
		//! \brief Temps pour laquelle l'action est exécuter. En minute.
		unsigned int _callTime;
};

#endif //ACTION_LEARN_H
