//! \file **********************************************************************
//! \brief Source Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.17
//! \date 12.12.12
//!
//! ****************************************************************************

//App
#include "main.hpp"
#include "defs.hpp"
#include "manager.hpp"
#include "manager/manGeneral.hpp"

//Stl
#include <csignal>
#include <iostream>

//WxWidgets
#include <wx/image.h> 
#include <wx/stdpaths.h>
#include <wx/aboutdlg.h>
#include <wx/event.h>
#include <wx/file.h>
#include <wx/filefn.h>
#include <wx/log.h> 

//Récupération du signale USER1.
static wxEvtHandler* evtHandlerMain = nullptr;
void signal_user1(int)
{	
	//Envoi d'un évènement pour afficher les preferences.
	wxCommandEvent *event =
		new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, ID_PREFERENCES);
	wxQueueEvent(evtHandlerMain, event);
}

// *****************************************************************************
// Class App
// *****************************************************************************

wxIMPLEMENT_APP(App);

bool App::OnInit()
{  	
	_dlgPrefPtr = nullptr;
	
	//Re direction des logs ver la sorti standard.
	wxLog* logger = new wxLogStream(&std::cout);
	wxLog::SetActiveTarget(logger);
		
	//Changement du préfixe seulement sous unix
	#if defined(__UNIX__)
	wxStandardPaths::Get().SetInstallPrefix("/usr");
	#endif
	
	//Chemin vair le fichier d'instance du programme.
	wxString fileSingleInstance = wxStandardPaths::Get().GetTempDir()+'/'+PROJECT_NAME+'-'+wxGetUserId();
	//Si le fichier existe ceci veux dire qu'il y a une autre instances de ce 
	//programme en cour d'exécution.
	if(wxFileExists(fileSingleInstance))
	{	
		//On lis le pid de l'autre instances.
		int pid;
		wxFile file(fileSingleInstance);
		file.Read(&pid, sizeof pid);
		file.Close();
		
		//Et on luis envois le signale USER1.
		if(wxKill(pid, (wxSignal)SIGUSR1) == 0)
		{
			wxLogMessage(PROJECT_NAME" is already running ...");
			return false;
		}
	}
	
	//Si le fichier n'existe pas, alors on le crée avec le pid de
	//cette instances.
	int pid = getpid();
	wxFile file(fileSingleInstance, wxFile::write);
	file.Write(&pid, sizeof pid);
	file.Close();
	
	//Installassions du gestionnaire de signale.
	//Pour récupère le signale USER1.
	std::signal(SIGUSR1, signal_user1);
	evtHandlerMain = this;
	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	
	//Création de tout les managers.
	Manager::createManagers();
	
	//Chargement de la confige de tous les manager.
	Manager::loadManagers();
	
	//Bind.
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::onQuit, this, ID_QUIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::onAbout, this, ID_ABOUT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::onPreferences, this, ID_PREFERENCES);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::onEnableShortcuts, this, ID_ENABLE_SHORTKUT);
	
	return true;
}

int App::OnExit()
{	
	//Unbind.
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::onQuit, this, ID_QUIT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::onAbout, this, ID_ABOUT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::onPreferences, this, ID_PREFERENCES);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::onEnableShortcuts, this, ID_ENABLE_SHORTKUT);
	
	//Suppression de tout les managers.
	Manager::killManagers();
	
	//Suppression des locale
	//delete _locale;
	
	//Suppression du fichier d'instance du programme.
	wxString fileSingleInstance = wxStandardPaths::Get().GetTempDir()+'/'+PROJECT_NAME+'-'+wxGetUserId();
	wxRemoveFile(fileSingleInstance);
	
	return 0;
}

void App::onQuit(wxCommandEvent&)
{
	ExitMainLoop();
}

void App::onAbout(wxCommandEvent&)
{	
	wxAboutDialogInfo info;

	info.SetName(PROJECT_NAME);
	info.SetVersion(PROJECT_VERSION);
	
	info.SetIcon(ManGeneral::get().getIconApp(ICON_SIZE_32X32));
	
	wxString msg;
	msg << wxString::FromUTF8Unchecked("Traduction A La Volées.");
	msg << _("\n Translation on the fly in English.") << "\n\n";
	msg << _("Build on") << " ";
	#if defined(__UNIX__)
	msg << "Unix";
	#elif defined(__WXMSW__)
	msg << "Windows";
	#endif
	#ifdef __i386
	msg << " " << _("in") << " " << " i386\n";
	#elif __amd64
	msg << " " << _("in") << " " << " x86_64\n";
	#endif
	msg << _("Date") <<  " : " << __DATE__;
	
	info.SetDescription(msg);
	
	info.SetCopyright("(C) 2012-1013");
	info.SetWebSite("http://antoine163.github.com/talv/");
	
	info.AddDeveloper("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	info.AddDocWriter("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	//info.AddTranslator("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
	
	info.SetLicence(
	"The MIT License (MIT)\n\n"\
	
	"Copyright (c) 2012-2013 - Antoine Maleyrie.\n\n"\

	"Permission is hereby granted, free of charge, to any person obtaining a copy\n"\
	"of this software and associated documentation files (the \"Software\"), to deal\n" \
	"in the Software without restriction, including without limitation the rights\n" \
	"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n" \
	"copies of the Software, and to permit persons to whom the Software is\n"\
	"furnished to do so, subject to the following conditions:\n\n"\

	"The above copyright notice and this permission notice shall be included in all\n"\
	"copies or substantial portions of the Software.\n\n"\

	"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"\
	"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"\
	"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"\
	"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"\
	"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"\
	"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"\
	"SOFTWARE.");
	
	wxAboutBox(info);
}

void App::onPreferences(wxCommandEvent&)
{	
	if(_dlgPrefPtr != nullptr)
	{
		wxLogWarning("The preferences dialog is already running ...");
		_dlgPrefPtr->SetFocus();
		return;
	}
		
	//Création du dialog.
	_dlgPrefPtr = new DialogPreferences();

	//Bind close
	_dlgPrefPtr->Bind(wxEVT_CLOSE_WINDOW, &App::onPreferencesColse, this);

	//Affichage du dialog.
	_dlgPrefPtr->Show();
}

void App::onEnableShortcuts(wxCommandEvent&)
{
	//_enableShortcuts = event.IsChecked();
	//ManagerAction::getInstance()->enableShortcuts(_enableShortcuts);
}

void App::onPreferencesColse(wxCloseEvent&)
{
	_dlgPrefPtr->Unbind(wxEVT_CLOSE_WINDOW, &App::onPreferencesColse, this);
	
	delete _dlgPrefPtr;
	_dlgPrefPtr = nullptr;
}
