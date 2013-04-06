//! \file **************************************************************
//! \brief Source Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actSaveTranslation.hpp"
#include "resource.hpp"

#include <wx/filename.h>
#include <wx/file.h>
#include <wx/msgdlg.h>

//TEST
#include <iostream>

// *********************************************************************
// Class PanelActSaveTranslation
// *********************************************************************

PanelActSaveTranslation::PanelActSaveTranslation(wxWindow* parent, wxButton* buttonOK, ActSaveTranslation * act)
: GuiPanelActSaveTranslation(parent), _act(act), _buttonOK(buttonOK)
{
	std::map<wxString, wxString> const& languages = Resource::getInstance()->getLanguages();	
	
	//Ajout des langues.
	for(auto &it: languages)
	{
		_choiceLanguageSource->Append(it.second);
		_choiceLanguageOfTranslation->Append(it.second);
	}
	
	//Sélectionne les bonnes langues.
	int n = _choiceLanguageSource->FindString(languages.at(_act->_lgsrc));
	_choiceLanguageSource->SetSelection(n);
	n = _choiceLanguageOfTranslation->FindString(languages.at(_act->_lgto));
	_choiceLanguageOfTranslation->SetSelection(n);
	
	//Sélectionne le bon répertoire.
	_dirPickerFolder->SetPath(_act->_fileName.GetPath());
	//Sélectionne le bon fichier.
	_textCtrlFile->SetValue(_act->_fileName.GetName());
	
	//Tout sauvegarder ?
	if(_act->_soveAll)
		_radioBtnSaveAllTranslations->SetValue(true);
	else
		_radioBtnSaveATranslation->SetValue(true);
		
	//Pas de doublon
	if(_act->_noDoublon)
		_checkBoxNoDoublon->SetValue(true);
	else
		_checkBoxNoDoublon->SetValue(false);
		
	//Dessiner un dialogue
	if(_act->_showDialog)
		_checkBoxShowDialog->SetValue(true);
	else
		_checkBoxShowDialog->SetValue(false);
		
		
	//Lier l'événement du bouton OK du wxWindow parent.
	_buttonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSaveTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

PanelActSaveTranslation::~PanelActSaveTranslation()
{
	_buttonOK->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &PanelActSaveTranslation::OnOKButtonClick, this, _buttonOK->GetId());
}

void PanelActSaveTranslation::OnOKButtonClick(wxCommandEvent& event)
{
	//Vérifie si le non du fichier est valide.
	if(_textCtrlFile->IsEmpty())
	{
		wxMessageDialog dlg(this, _("The name of file is empty."), _("Name file invalid"), wxOK);
		dlg.ShowModal();
		
		return;
	}
	
	//Réoccuper le non complet du fichier.
	wxFileName tmpFileName(wxGetUserHome(_dirPickerFolder->GetPath()), _textCtrlFile->GetValue());
	
	//Vérifier si le fichier existe.
	if(tmpFileName.Exists() && tmpFileName != _act->_fileName)
	{
		//Si il existe, on demande si il faut remplacer le fichier.
		wxString message = _("The file \"") + tmpFileName.GetFullPath() + _("\" already exists.\n") + _("Do you want replace this file?");
		wxMessageDialog *dlg = new wxMessageDialog(this, message, _("Replace a file"), wxYES_NO|wxICON_QUESTION);
		if(dlg->ShowModal() != wxID_YES)
			return;
		
		dlg->Destroy();
	}
	
	//Si le non du fichier a été modifier
	if(tmpFileName != _act->_fileName)
	{
		//Création du fichier, si il n'existe pas ou si on doit le remplacer.
		wxFile file(tmpFileName.GetFullPath(), wxFile::OpenMode::write);
		if(!file.IsOpened())
		{
			wxMessageDialog dlg(this, _("Cannot create or open the file : ")+tmpFileName.GetFullPath(), _("No open file"), wxOK);
			dlg.ShowModal();
			
			return;
		}

		//Écrie la première ligne
		file.Write(_("word")+","+_("translation")+","+_("adverbe")+","+_("adjectif")+","+_("nom")+","+_("verbe")+","+_("pronom"));
		//Fermeture du fichier
		file.Close();
	}
	
	//Affect le langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	_act->_lgsrc = Resource::getInstance()->languageToAcronym(s);
	
	//Affect le langage de destination.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	_act->_lgto = Resource::getInstance()->languageToAcronym(s);
	
	//Affect les autres arguments.
	_act->_fileName = tmpFileName;
	_act->_soveAll = _radioBtnSaveAllTranslations->GetValue();
	_act->_noDoublon = _checkBoxNoDoublon->IsChecked();
	_act->_showDialog = _checkBoxShowDialog->IsChecked();
		
	//Propage l'événement.
	event.Skip();
}

// *********************************************************************
// Class ActSaveTranslation
// *********************************************************************

//! \todo a compléter avec les local
ActSaveTranslation::ActSaveTranslation()
: ActSaveTranslation(	"en", "fr", wxFileName(wxGetUserHome(), ""),
						true, true, true)
{
}

ActSaveTranslation::ActSaveTranslation(wxString const& lgsrc,
							wxString const& lgto,
							wxFileName const& fileName,
							bool soveAll,
							bool noDoublon,
							bool showDialog)
: Action(_("Save a translation"), "ActSaveTranslation",
_("Translation a word or a group words from google and save in a file.")),
_lgsrc(lgsrc), _lgto(lgto), _fileName(fileName),
_soveAll(soveAll), _noDoublon(noDoublon), _showDialog(showDialog)
{
}

ActSaveTranslation::~ActSaveTranslation()
{
}

void ActSaveTranslation::execute()
{
	std::cout << "ActSaveTranslation::execute" << std::endl;
	std::cout << "-- " << getStringPreferences() << std::endl;
}

wxPanel* ActSaveTranslation::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActSaveTranslation(parent, buttonOK, this);
}

//! \todo a compléter avec les valeurs écrites dans le fichier.
void ActSaveTranslation::actLoad(wxFileConfig & fileConfig)
{	
	std::cout << "ActSaveTranslation::load" << std::endl;
}
		
void ActSaveTranslation::actSove(wxFileConfig & fileConfig)const
{
}

wxString ActSaveTranslation::getStringPreferences()const
{
	return "ActSoveTranslation::getStringPreferences";
}