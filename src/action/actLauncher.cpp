//! \file **********************************************************************
//! \brief Source Action exécute une ligne de commande.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.0
//! \date 03.02.2014
//!
//! ****************************************************************************

//App
#include "action/actLauncher.hpp"
#include "staticBox.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/utils.h> 
#include <wx/sizer.h>
#include <wx/filedlg.h>

// *****************************************************************************
// Class ActLauncher
// *****************************************************************************

ActLauncher::ActLauncher()
{
}

ActLauncher::~ActLauncher()
{
}

IMPLEMENT_ACTION(ActLauncher, _("Launch commend"), _("Launcher a application/script/..."));

WinAction* ActLauncher::newEditWindow(wxWindow* parent)
{
	return new WinActLauncher(parent, this);
}

wxString ActLauncher::getStringPreferences()const
{
	return 	_("Launch of ")+_command;
}

void ActLauncher::execute()
{
	wxShell(_command);
}

wxString ActLauncher::getCommand()const
{
	return _command;
}

void ActLauncher::setCommand(wxString const& command)
{
	_command = command;
}

void ActLauncher::actLoad(wxFileConfig& fileConfig)
{
	//On récupère les préférences.
	_command = fileConfig.Read("command", wxEmptyString);
}

void ActLauncher::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("command", _command);
}

// *****************************************************************************
// Class WinActLauncher
// *****************************************************************************

WinActLauncher::WinActLauncher(wxWindow* parent, ActLauncher const* act)
: WinAction(parent, act)
{
	wxString command = static_cast<ActLauncher*>(_act)->getCommand();
	
	StaticBox* staticBoxCommand = new StaticBox(this, wxID_ANY, _("Chose your commend line:"));
	_textCtrlCommand = 		new wxTextCtrl	(staticBoxCommand, wxID_ANY, command);
	_buttonPickExeFile =	new wxButton	(staticBoxCommand, wxID_ANY, _("Pick a executable"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	
	wxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);
	sizerMain->Add(_textCtrlCommand, 	1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 	SIZE_BORDER);
	sizerMain->Add(_buttonPickExeFile, 	0, wxALIGN_CENTER_VERTICAL);
	staticBoxCommand->SetSizer(sizerMain);
	
	GetSizer()->Add(staticBoxCommand, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	
	//Bind
	_buttonPickExeFile->Bind(wxEVT_BUTTON, &WinActLauncher::onPickExeFile, this);
}

WinActLauncher::~WinActLauncher()
{
	//Unbind
	_buttonPickExeFile->Unbind(wxEVT_BUTTON, &WinActLauncher::onPickExeFile, this);
}

void WinActLauncher::refreshActionFromGui()
{
	static_cast<ActLauncher*>(_act)->setCommand(_textCtrlCommand->GetValue());
}

void WinActLauncher::onPickExeFile(wxCommandEvent&)
{
	wxFileDialog dlg(this, _("Pick a executable file"), wxEmptyString, wxEmptyString, wxEmptyString, wxFD_FILE_MUST_EXIST);
	
	if(dlg.ShowModal() == wxID_OK)
		_textCtrlCommand->SetValue(dlg.GetPath());
}

