//! \file **************************************************************
//! \brief Header Action, traduction et sauvegarde dans une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.21
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION__TRANSLATION_TO_LIST_H
#define ACTION__TRANSLATION_TO_LIST_H

#include "action/guiPanelActTranslationToList.h"
#include "notification.hpp"
#include "action.hpp"
#include "list.hpp"

#include <wx/dialog.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/arrstr.h>

#include <vector>
#include <map>

// *********************************************************************
// Class PanelActTranslationToList
// *********************************************************************

class ActTranslationToList;

//! \brief GUI pour la modification des préférences de l'action de traduction et sauvegarde dans une liste. \ref ActTranslationToList.
class PanelActTranslationToList : public GuiPanelActTranslationToList
{
	public:
		PanelActTranslationToList(wxWindow* parent, wxButton* buttonOK, ActTranslationToList* act);
		~PanelActTranslationToList();
		
		void updateComboBoxList();
		
		void OnChoiceSrc(wxCommandEvent&);
		void OnChoiceTo(wxCommandEvent&);
		
		//! \brief Méthode appeler si appuis sur bouton "ok" du parent.
		//! Elle valide les modifications et les installe dans l'action
		void OnOKButtonClick(wxCommandEvent& event);
	
	private:
		//! \brief ActSoveTranslation à modifier.
		ActTranslationToList* _act;
		
		//! \brief bouton "OK" du dialogue parent.
		wxButton* _buttonOK;
};

// *********************************************************************
// Class PanelPickTranslation
// *********************************************************************

class DialogPickMainTranslation;

//! \brief Panel présentent les traductions sous forme de bouton.
//! \see DialogPickMainTranslation
class PanelPickTranslation : public GuiPanelTranslation
{
	public:
		//! \brief Constructeur.
		//! \param parentfenêtre parant.
		//! \param kind fenêtre parant.
		//! \param translations les traductions à afficher dans les boutons.
		PanelPickTranslation(	DialogPickMainTranslation* parent,
								wxString const& kind,
								wxArrayString const& translations);
		
		//! \brief Destructeur.
		~PanelPickTranslation();
		
	private:
		//! \brief la fenêtre parant.
		DialogPickMainTranslation* _parent;
		//! \brief contiens tous les boutons.
		std::vector<wxButton*> _buttons;
};

// *********************************************************************
// Class DialogPickMainTranslation
// *********************************************************************

//! \brief GUI pour choisir la traduction principale à sauvegarder.
//! \see ActTranslationToList
class DialogPickMainTranslation : public GuiDialogPickMainTranslation
{
	friend PanelPickTranslation;
	public:
		//! \brief Constructeur.
		//! \param parent fenêtre parant.
		//! \param text le texte.
		//! \param mainTranslate la traduction principale.
		//! \param translations les traductions en fonction de leur genre.
		DialogPickMainTranslation(	wxWindow* parent,
									wxString text,
									wxString mainTranslate,
									std::map<wxString, wxArrayString> const& translations);
		
		//! \brief Destructeur.
		~DialogPickMainTranslation();
		
		//! \brief Obtenir la traduction principale choisi.
		wxString const& GetChoice();
	
	protected:
		//! \brief Lorsque un bouton a été cliquer cette méthode est appeler et quitte le dialogue.
		void OnButtonClick(wxCommandEvent& event);
		
	private:
		//! \brief Correspond à la traduction principale choisi.
		wxString _choice;
};

// *********************************************************************
// Class ActTranslationToList
// *********************************************************************

//! \brief Action de traduction et sauvegarde la traduction dans une liste.
class ActTranslationToList : public Action
{
	friend PanelActTranslationToList;
	
	public:
		//! \brief Constructeur par défaut.
		ActTranslationToList();
		
		//! \brief Constructeur.
		//! Les deux premier paramètres doive être écrit en abrégé.
		//! ex: pour le français "fr"
		//! ex: pour l'anglais "en"
		//!
		//! \param lgsrc lange source.
		//! \param lgto lange de traduction.
		//! \param listName Le non de la liste où sauvegarder les traductions.
		//! \param saveAll true pour enregistre tout les traductions, false pour enregistre juste la traduction principale.
		//! \param showDialog true pour affiche une dialogue l'or d'une sauvegarde pour choisir la traduction a sauvegarder
		ActTranslationToList(	wxString const& lgsrc,
								wxString const& lgto,
								wxString const& listName,
								bool showDialog);
						
		//! \brief Destructeur.
		~ActTranslationToList();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
		//! \brief Obtenir le nom de la liste utiliser.
		wxString getLisNameUsed()const;
		
	protected:		
		//! \brief Permet de charger les préférences de l'action à partir du wxFileConfig.
		//! \param fileConfig fichier à partir du quelle l'action doit être charger.
		void actLoad(wxFileConfig & fileConfig);
		
		//! \brief Permet de sauvegarder les préférences de l'action dans le wxFileConfig.
		//! \param fileConfig fichier où l'action doit être sauvegarder.
		void actSave(wxFileConfig & fileConfig)const;
		
	private:
		//! \brief Lange source.
		wxString _lgsrc;
		//! \brief Lange de traduction.
		wxString _lgto;
		
		wxString _listName;
		bool _showDialog;
};

#endif //ACTION__TRANSLATION_TO_LIST_H
