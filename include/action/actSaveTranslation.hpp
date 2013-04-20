//! \file **************************************************************
//! \brief Header Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.13
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_SAVE_TRANSLATION_H
#define ACTION_SAVE_TRANSLATION_H

#include "action/guiPanelActSaveTranslation.h"
#include "notification.hpp"
#include "action.hpp"

#include <wx/dialog.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/arrstr.h>

#include <vector>
#include <map>

// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************

class ActSaveTranslation;

//! \brief GUI pour la modification des préférences des actions de sauvegarde de traductions \ref ActSaveTranslation.
class PanelActSaveTranslation : public GuiPanelActSaveTranslation
{
	public:
		PanelActSaveTranslation(wxWindow* parent, wxButton* buttonOK, ActSaveTranslation * act);
		~PanelActSaveTranslation();
		
		//! \brief Méthode appeler si appuis sur bouton "ok" du parent.
		//! Elle valide les modifications et les installe dans l'action
		void OnOKButtonClick(wxCommandEvent& event);
	
	private:
		//! \brief ActSoveTranslation à modifier.
		ActSaveTranslation * _act;
		
		//! \brief bouton "OK" du dialogue parent.
		wxButton* _buttonOK;
};

// *********************************************************************
// Class PanelTranslation
// *********************************************************************

class DialogPickMainTranslation;

//! \brief Panel présentent les traductions sous forme de bouton.
//! \see DialogPickMainTranslation
class PanelTranslation : public GuiPanelTranslation
{
	public:
		//! \brief Constructeur.
		//! \param parentfenêtre parant.
		//! \param kind fenêtre parant.
		//! \param translations les traductions à afficher dans les boutons.
		PanelTranslation(	DialogPickMainTranslation* parent,
							wxString const& kind,
							wxArrayString const& translations);
		
		//! \brief Destructeur.
		~PanelTranslation();
		
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
//! \see ActSaveTranslation
class DialogPickMainTranslation : public GuiDialogPickMainTranslation
{
	friend PanelTranslation;
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
// Class ActSaveTranslationFile
// *********************************************************************

//! \brief Classe permettent de sauvegarder des textes et leur traductions dans un fichier.
//! \see ActSaveTranslation
class ActSaveTranslationFile
{
	public:
		//! \brief Constructeur.
		//! \param fileName le non du fichier.
		ActSaveTranslationFile(wxFileName const& fileName);
						
		//! \brief Destructeur.
		~ActSaveTranslationFile();
	
		//! \brief Pour connaître l'existence d'un texte dans le fichier.
		//! \param text a vérifier.
		bool exist(wxString text);
		
		//! \brief Pour sauvegarder un texte et ça traduction dans le fichier.
		//! \param text le texte a sauvegarder.
		//! \param mainTranslate la traduction a sauvegarder.
		void save(	wxString text,
					wxString mainTranslate);
					
		//! \brief Pour sauvegarder un texte et c'est traductions dans le fichier.
		//! \param text le texte a sauvegarder.
		//! \param mainTranslate la traduction principale a sauvegarder.
		//! \param translations les traductions a sauvegarder.
		void save(	wxString text,
					wxString mainTranslate,
					std::map<wxString, wxArrayString> const& translations);

	private:
		//! \brief Le non nu fichier.
		wxFileName _fileName;
		//! \brief Représente la première ligne du fichier sous la forme d'un wxArrayString.
		wxArrayString _FirstLine;
		//! \brief C'est le fichier.
		wxTextFile _file;
};

// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

//! \brief Action de sauvegarde de traductions.
class ActSaveTranslation : public Action
{
	friend PanelActSaveTranslation;
	
	public:
		//! \brief Constructeur par défaut.
		ActSaveTranslation();
		
		//! \brief Constructeur.
		//! Les deux premier paramètres doive être écrit en abrégé.
		//! ex: pour le français "fr"
		//! ex: pour l'anglais "en"
		//!
		//! \param lgsrc lange source.
		//! \param lgto lange de traduction.
		//! \param fileName Le non du fichier où sauvegarder les traductions.
		//! \param saveAll true pour enregistre tout les traductions, false pour enregistre juste la traduction principale.
		//! \param noDoublon true pour ne pas enregistre de doublon.
		//! \param showDialog true pour affiche une dialogue l'or d'une sauvegarde pour choisir la traduction a sauvegarder
		ActSaveTranslation(	wxString const& lgsrc,
							wxString const& lgto,
							wxFileName const& fileName,
							bool saveAll,
							bool noDoublon,
							bool showDialog);
						
		//! \brief Destructeur.
		~ActSaveTranslation();
		
		//! \brief Exécuter l'action.
		void execute();
		
		//! \brief Obtenir le panel pour l'édition de l'action.
		//! \param parent est le parent du panel.
		//! \note Cette méthode crées un panel et retourne le pointeur sur se panel il faudra prévoir de libérai la mémoire.
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		
		//! \brief Préférences de l'action au format string.
		wxString getStringPreferences()const;
		
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
		
		wxFileName _fileName;
		bool _saveAll;
		bool _noDoublon;
		bool _showDialog;
};

#endif //ACTION_SAVE_TRANSLATION_H
