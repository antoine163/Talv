//! \file **********************************************************************
//! \brief Source Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.16
//! \date 12.12.12
//!
//! ****************************************************************************

//App
#include "main.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/image.h> 
#include <wx/stdpaths.h>
#include <wx/aboutdlg.h>

//Test
#include <iostream>

// *****************************************************************************
// Class App
// *****************************************************************************

wxIMPLEMENT_APP(App);

bool App::OnInit()
{  	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	
	//Changement du Préfixe seulement sous unix
	#if defined(__UNIX__)
	wxStandardPaths::Get().SetInstallPrefix("/usr");
	#endif
		
	//Bind.
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnQuit, this, ID_QUIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, ID_ABOUT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, ID_PREFERENCES);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnableShortcuts, this, ID_ENABLE_SHORTKUT);
	
	
	//! \todo migrais vair le manager générale
	_taskIcon = new TaskIcon();
	
	return true;
}

int App::OnExit()
{	
	//Unbind.
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnQuit, this, ID_QUIT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, ID_ABOUT);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, ID_PREFERENCES);
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnableShortcuts, this, ID_ENABLE_SHORTKUT);
	
	
	// suppression des locale
	delete _locale;
	
	//! \todo migrais vair le manager générale
	delete _taskIcon;
	
	return 0;
}

void App::OnQuit(wxCommandEvent&)
{		
	ExitMainLoop();
}

void App::OnAbout(wxCommandEvent&)
{	
	wxAboutDialogInfo info;

	info.SetName(PROJECT_NAME);
	info.SetVersion(PROJECT_VERSION);
	
	wxIcon tmpIcon;
	tmpIcon.LoadFile("../icons/32x32/" PROJECT_NAME ".png", wxBITMAP_TYPE_PNG);
	info.SetIcon(tmpIcon);
	
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

void App::OnPreferences(wxCommandEvent&)
{
	std::cout << "OnPreferences" << std::endl;
	////Création du dialog.
	//DialogPreferences dlg;
	
	////Affichage du dialog.
	//if(dlg.ShowModal() == wxID_OK)
	//{		
		////Vérification si on doit afficher ou pasl'icône dans la zone de
		////notification.
		//if(!Resource::getInstance()->getShowMenu())
			//Destroy();
	//}
}

void App::OnEnableShortcuts(wxCommandEvent& event)
{
	std::cout << "OnEnableShortcuts : " << event.IsChecked() << std::endl;
	//_enableShortcuts = event.IsChecked();
	//ManagerAction::getInstance()->enableShortcuts(_enableShortcuts);
}
