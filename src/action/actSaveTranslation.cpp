//! \file **************************************************************
//! \brief Source Action de sauvegarde de traduction.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.11
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
: _fileName(fileName)
{
	//Le fichier existe ?
	if(wxFile::Exists(fileName.GetFullPath()))
	{
		//On ouvre le fichier
		_file.Open(fileName.GetFullPath());
		
		//On analyse la première ligne
		wxString firstLine = _file. GetFirstLine();
		wxString beforeComma;
		for(size_t i = 0; i<firstLine.Length(); i++)
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
		//On enregistre aussi le dernier texte trouver si il n'est pas vide
		if(!beforeComma.IsEmpty())
		{
			_FirstLine.Add(beforeComma);
		}
	}
}

ActSaveTranslationFile::~ActSaveTranslationFile()
{
	_file.Close();
}

bool ActSaveTranslationFile::exist(wxString text)
{
	//Fichier ouvert ?
	if(_file.IsOpened())
	{
		//Caractère en minuscule.
		text.MakeLower();
		
		//On recherche si le texte existe (avent la première ',' de tout les lignes)
		for (wxString line = _file.GetFirstLine(); !_file.Eof(); line = _file.GetNextLine())
		{
			if(line.BeforeFirst(',') == text)
			{
				return true;
			}
		}
	}
	
	return false;
}
		
void ActSaveTranslationFile::save(	wxString text,
									wxString mainTranslate)
{
	//Caractère en minuscule.
	text.MakeLower();
	mainTranslate.MakeLower();
	
	//Si le fichier n'est pas déjà existent
	if(!wxFile::Exists(_fileName.GetFullPath()))
	{
		//On le crée
		_file.Create(_fileName.GetFullPath());
		//On ajout la première ligne.
		_file.AddLine(_("text")+","+_("translation"));
	}
	
	//Écriture des données dans le fichier
	_file.AddLine(text+","+mainTranslate);
	_file.Write();
}

void ActSaveTranslationFile::save(
	wxString text,
	wxString mainTranslate,
	std::map<wxString, wxArrayString> const& translations)
{
	//Caractère en minuscule.
	text.MakeLower();
	mainTranslate.MakeLower();
	
	//Si le fichier n'est pas déjà existent
	if(!wxFile::Exists(_fileName.GetFullPath()))
	{
		//On le crée
		_file.Create(_fileName.GetFullPath());
		//On ajout la première ligne.
		_file.AddLine(_("text")+","+_("translation"));
		_file.Write();
		
		_FirstLine.Add(_("text"));
		_FirstLine.Add(_("translation"));
	}
	
	//Parcoure autant de ligne qu'il y en a dans la traduction.
	bool loop = true;
	for(size_t iline = 0;;iline++)
	{
		std::map<int, wxString> strline;
		int nbColumn = 0;
		
		//Parcoure tout les colonnes
		for(auto it : translations)
		{
			//On vérifie si le type du mot et connue dans la première ligne.
			int column = _FirstLine.Index(it.first, false);
			if(column == wxNOT_FOUND)
			{
				//Si il n'existe pas on l'ajoute.
				column = _FirstLine.Add(it.first);
			}
			
			//Le nombre de colonne et égale a l'index de la colonne la plus élever.
			if(nbColumn < column)
			{
				nbColumn = column;
			}
			
			//Si il n'y a plus de texte a cette colonne et a cette ligne
			if(iline >= it.second.GetCount())
			{
				//On a plus besoin de boucler pour cette ligne.
				loop = false;
			}
			else
			{
				//On a besoin de boucler pour cette ligne.
				loop = true;
				//On ajoute le texte dans la bonne colonne et la bonne ligne
				strline[column] = it.second[iline];
			}
		}
		
		//Si on ne doit plus boucler.
		if(!loop)
		{
			break;
		}
		
		//La ligne a ajouter
		wxString addLine;
		
		//Première ligne (du texte) ?
		if(iline == 0)
		{
			_file.AddLine(wxEmptyString);
			addLine << text << ',' << mainTranslate;
		}
		else
		{
			addLine << ',';
		}
		
		//On parcoure tout les colonne (soft les deux première).
		for(int iColumn = 2; iColumn <= nbColumn; iColumn++)
		{
			addLine << ',';
			if(strline.count(iColumn) > 0)
			{
				addLine << strline[iColumn];
			}
		}
		//Écriture des données dans le fichier.
		_file.AddLine(addLine);
	}
	
	//Réécriture de la première ligne du fichier.
	wxString addFirstLine;
	for(auto it : _FirstLine)
	{
		addFirstLine << it << ',';
	}
	_file.RemoveLine(0);
	_file.InsertLine(addFirstLine, 0);
	
	//Écriture des données dans le fichier.
	_file.Write();
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
		//Pas de texte à traduire.
		Notification::getInstance()->notify(_("Save clipboard translation"), _("Sorry, nothing at save."));
		return;
	}

	//On récupère le texte traduit.
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
		wxMessageBox(_("The name of file is wrong."), _("Name file invalid."), wxOK|wxICON_EXCLAMATION|wxCENTRE);
		return;
	}
	
	//Fichier de sauvegarde
	ActSaveTranslationFile file(_fileName);
	
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
	
	Notification::getInstance()->notify(_("Save clipboard translation"), _("The text has be saved."));
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
