//! \file **************************************************************
//! \brief Source Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.9
//! \date 31.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "action/actSaveTranslation.hpp"
#include "resource.hpp"

#include <wx/wfstream.h>
#include <wx/msgdlg.h> 
#include <wx/file.h>
#include <wx/log.h> 


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
	
	//Sélectionne le bon fichier.
	_filePickerFile->SetFileName(_act->_fileName);
	
	//Tout sauvegarder ?
	if(_act->_saveAll)
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
	//Vérifie si il y a un fichier de sélectionner.
	if(_filePickerFile->GetFileName().GetFullName().IsEmpty())
	{
		wxMessageBox(_("The name of file is empty."), _("Name file invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE, this);
		return;
	}
	
	//Récupérer le nom du fichier.
	wxFileName tmpFileName = _filePickerFile->GetFileName();
		
	//Si fichier a été modifier ?
	if(_act->_fileName != tmpFileName)
	{
		//Le fichier est déjà existent ?
		if(tmpFileName.Exists() && tmpFileName != _act->_fileName)
		{
			//Si il existe, on demande si il faut remplacer le fichier.
			wxString message = _("The file \"") + tmpFileName.GetFullPath() + _("\" already exists.\n") + _("Do you want delete this file?");
			wxMessageDialog *dlg = new wxMessageDialog(this, message, _("Delete a file"), wxYES_NO|wxICON_QUESTION|wxICON_EXCLAMATION|wxCENTRE);
			if(dlg->ShowModal() != wxID_YES)
			{
				dlg->Destroy();
				return;
			}
			else
			{
				//Suppression du fichier.
				if(!wxRemoveFile(_filePickerFile->GetPath()))
				{
					wxLogError(_("Could not remove the file : ")+tmpFileName.GetFullPath());
				}
				
				dlg->Destroy();
			}
		}
	}
	
	//Affect le langage source.
	int n = _choiceLanguageSource->GetSelection();
	wxString s = _choiceLanguageSource->GetString(n);
	_act->_lgsrc = Resource::getInstance()->languageToAbbreviation(s);
	
	//Affect le langage de destination.
	n = _choiceLanguageOfTranslation->GetSelection();
	s = _choiceLanguageOfTranslation->GetString(n);
	_act->_lgto = Resource::getInstance()->languageToAbbreviation(s);
	
	//Affect les autres arguments.
	_act->_fileName = tmpFileName;
	_act->_saveAll = _radioBtnSaveAllTranslations->GetValue();
	_act->_noDoublon = _checkBoxNoDoublon->IsChecked();
	_act->_showDialog = _checkBoxShowDialog->IsChecked();
		
	//Propage l'événement.
	event.Skip();
}

// *********************************************************************
// Class ActSaveTranslationFile
// *********************************************************************
ActSaveTranslationFile::ActSaveTranslationFile(wxFileName const& fileName)
: _fileName(fileName), _isOk(true)
{
	//Si le fichier existe on le charge
	if(wxFile::Exists(fileName.GetFullPath()))
	{
		//Ouverture du fichier
		wxFileInputStream file(fileName.GetFullPath());
		_isOk = file.IsOk();
		
		//OK ?
		if(_isOk)
		{	
			//Le buffer pour stoker le tout contenue fichier
			wxMemoryBuffer buffer;
			//data temporaire.
			uint8_t tmpData[1024];
			
			//Lie des données temps qu'il y en a.
			while(file.CanRead() && !file.Eof())
			{
				file.Read(tmpData, 1024);
				buffer.AppendData(tmpData, file.LastRead());
			}
			
			//Ajouter les données dans un wxString.
			wxString stringFile;
			stringFile.Append((const char *)buffer.GetData(), buffer.GetDataLen());
			
			//On récupère la première ligne et on sauvegarde le reste
			wxString firstLine = stringFile.BeforeFirst('\n', &_texts);
			
			//On analyse la première ligne
			wxString beforeComma;
			for(size_t i; i<firstLine.Length(); i++)
			{
				if(firstLine[i] == ',')
				{
					_FirstLine.Add(beforeComma);
					beforeComma.Clear();
				}
				else
				{
					beforeComma << firstLine[i];
				}
			}
		}
	}	
}

ActSaveTranslationFile::~ActSaveTranslationFile()
{
	
}

bool ActSaveTranslationFile::isOk()
{
	return _isOk;
}

bool ActSaveTranslationFile::exist(wxString const& text)
{
	//Taille des wxString
	size_t sizeStringFile = _texts.Length();
	size_t sizeText = text.Length();
	//Index pour le text
	size_t indexText = 0;
	
	//Variable pour savoir si on doit comparer les caractères.
	bool compare = true;
	
	//Parcoure touts les caractères (avec la ',') temps que l'on a pas trouver le "text"
	for(size_t i = 0; i < sizeStringFile; i++)
	{
		//Doit-ont comparer les caractères ?
		if(compare)
		{
			//Les caractères sont égaux.
			if(text[indexText] == _texts[i])
			{
				//Si le caractères suivent est une ',' alors le text existe
				if(_texts[i+1] == ',')
				{
					return true;
				}
				
				indexText++;
			}
			//On arrête de comparer pour cette ligne.
			else
			{
				compare = false;
			}
		}
		
		//On arrête de comparer si ','
		if(_texts[i] == ',')
		{
			compare = false;
		}
		//On repent la comparaison si nouvelle ligne ?
		else if(_texts[i] == '\n')
		{
			compare = true;
			sizeText = 0;
		}
	}
	
	return false;
}
		
void ActSaveTranslationFile::save(	wxString const& text,
									wxString const& mainTranslate)
{
	//const wxCharBuffer buffer = text.fn_str();
	//_file.
	//_file.Write(buffer.data(), buffer.length());
}

void ActSaveTranslationFile::save(
	wxString const& text,
	wxString const& mainTranslate,
	std::map<wxString, wxArrayString> const& translations)
{
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
_saveAll(soveAll), _noDoublon(noDoublon), _showDialog(showDialog)
{
}

ActSaveTranslation::~ActSaveTranslation()
{
}

void ActSaveTranslation::execute()
{
	//On récupère le contenue de la presse papier.
	wxString clipboard = Resource::getClipboard();
	
	//La presse papier est t'elle vide ?
	if(clipboard.IsEmpty())
	{
		//Pas de texte à traduire
		Notification::getInstance()->notify(_("Save clipboard translation"), _("Sorry, nothing at save."));
		return;
	}

	//On récupère le texte traduit
	std::map<wxString, wxArrayString> translations;
	wxString mainTranslate = Resource::getTranslations(&translations, clipboard, _lgsrc, _lgto);
	//On vérifie si une traduction existe.
	if(mainTranslate.IsEmpty())
	{
		Notification::getInstance()->notify(_("Save clipboard translation"), _("Sorry, nothing at save."));
		return;
	}
	
	//On vérifie la validités du fichier.
	if(_fileName.GetFullName().IsEmpty())
	{
		wxMessageBox(_("The name of file is wrong."), _("Name file invalid"), wxOK|wxICON_EXCLAMATION|wxCENTRE);
		return;
	}
	
	//Fichier de sauvegarde
	ActSaveTranslationFile file(_fileName);
	
	//Vérifie si ok
	if(!file.isOk())
		return;
	
	//Si on dois vérifier l'existence du texte dans le fichier
	if(_noDoublon)
	{
		if(file.exist(clipboard))
		{
			Notification::getInstance()->notify(_("Save clipboard translation"), _("The text is already existing in ")+_fileName.GetFullPath());
			return;
		}
	}
	
	//Sinon on le sauvegarde.
	if(_saveAll)//Doit ton tout sauvegarder ?
	{
		file.save(clipboard, mainTranslate, translations);
	}
	else
	{
		file.save(clipboard, mainTranslate);
	}
}

wxPanel* ActSaveTranslation::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	return new PanelActSaveTranslation(parent, buttonOK, this);
}

void ActSaveTranslation::actLoad(wxFileConfig & fileConfig)
{	
	//On récupère les langages.
	fileConfig.Read("lgsrc", &_lgsrc);
	fileConfig.Read("lgto", &_lgto);
	
	//On récupère le fichier.
	wxString file;
	fileConfig.Read("fileName", &file);
	_fileName.Assign(file);
	
	//On récupère le reste
	fileConfig.Read("saveAll", &_saveAll);		
	fileConfig.Read("noDoublon", &_noDoublon);
	fileConfig.Read("showDialog", &_showDialog);
}
		
void ActSaveTranslation::actSave(wxFileConfig & fileConfig)const
{	
	//On sauvegarde les langages.
	fileConfig.Write("lgsrc", _lgsrc);
	fileConfig.Write("lgto", _lgto);
	
	//On sauvegarde le fichier.
	fileConfig.Write("fileName", _fileName.GetFullPath());
	
	//On sauvegarde le reste
	fileConfig.Write("saveAll", _saveAll);		
	fileConfig.Write("noDoublon", _noDoublon);
	fileConfig.Write("showDialog", _showDialog);
}

wxString ActSaveTranslation::getStringPreferences()const
{
	return 	Resource::getInstance()->abbreviationToLanguage(_lgsrc) +
			_(" to ") +
			Resource::getInstance()->abbreviationToLanguage(_lgto) +
			_(" in ") + _fileName.GetFullPath();
}
