//30/11/12

#include "main.hpp"

#include <unistd.h>

#include <wx/aboutdlg.h>
#include <wx/utils.h> 
#include <wx/process.h>

#if defined(__USE_TTS__)
#include <gst/gst.h>
#endif

#if defined(__UNIX__)
#include <libnotify/notify.h>
#endif

#include "dialogPreferences.hpp"


IMPLEMENT_APP(App);

bool App::OnInit()
{  	
	//Init des bibliothèques.
	#if defined(__UNIX__)
	notify_init(PROJECT_NAME);
	#endif
	#if defined(__USE_TTS__)
	gst_init(NULL, NULL);
	#endif
	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);

	//Création du gestionnaire de raccourci clavier
	_shortcut = new Shortcut(this);	
	
	//Chargement de le config
	loadAndSetupConfig();

	return true;
}

int App::OnExit()
{	
	#if defined(__UNIX__)
	notify_uninit();
	#endif
	
	//Suppression du menue
	deleteMenuItem();
	
	//supprime les raccourcis;
	uninstallShortcut();
	delete _shortcut;

	return 0;
}

void App::creatMenuItem()
{
	if(!_menuIcon)
	{
		_menuIcon = new MenuIcon();
		
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, _menuIcon->getIdMenuItemAbout());
		Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
	}
}

void App::deleteMenuItem()
{
	if(_menuIcon)
	{
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnPreferences, this, _menuIcon->getIdMenuItemPreferences());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnEnable, this, _menuIcon->getIdMenuItemEnable());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnAbout, this, _menuIcon->getIdMenuItemAbout());
		Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, _menuIcon->getIdMenuItemExit());
		
		delete _menuIcon;
		_menuIcon = nullptr;
	}
}

void App::OnPreferences(wxCommandEvent&)
{	
	static bool isRun = false;
	
	if(!isRun)
	{
		isRun = true;
		
		//Création est affcichage du fialog
		DialogPreferences *dlg = new DialogPreferences(_shortcutAction);
		dlg->ShowModal();
		dlg->Destroy();
		
		//Chargement de le config avec le nouveau fichier
		loadAndSetupConfig();
		
		isRun = false;
	}
}

void App::OnEnable(wxCommandEvent& event)
{
	_shortcut->enable(event.IsChecked());
}

void App::OnAbout(wxCommandEvent&)
{
		wxAboutDialogInfo info;

		info.SetName(PROJECT_NAME);
		info.SetVersion(PROJECT_VERSION);
		
		wxString msg;
		msg << _("This software using google translate for translate a word or sentence from your clipboard.");
		msg << _("\n\nBuild on ");
		#if defined(__UNIX__)
		msg << _("Unix ");
		#elif defined(__WXMSW__)
		msg << _("Windows ");
		#endif
		#ifdef __i386
		msg << _("in i386\n");
		#elif __amd64
		msg << _("in x86_64\n");
		#endif
		msg << _("Date : ") << __DATE__;
		
		info.SetDescription(msg);
		info.SetCopyright("(C) 2012");
		info.SetWebSite("http://antoine163.github.com/flydocs/");
		info.AddDeveloper("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
		info.AddDocWriter("Maleyrie Antoine <antoine.maleyrie@gmail.com>");
		
		wxAboutBox(info);
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}

void App::OnShortcut(ShortcutEvent& event)
{
	_shortcutAction[event.getShortcutKey()]->execute();
}

void App::loadAndSetupConfig()
{
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	bool showMenu = true;
	fileConfig.Read("show_menu", &showMenu);
	
	//Création du menu ou pas.
	if(showMenu)
		creatMenuItem();
	else
		deleteMenuItem();

	//Désinstallation préalable des raccourcis
	uninstallShortcut();
	//Chargement des raccourci clavier
	setupShortcut(fileConfig);
}

void App::setupShortcut(wxFileConfig const& fileConfig)
{
	wxString shortcutRaw;
	unsigned int i = 1;
	
	while(fileConfig.Read(wxString("shortcut")<<i, &shortcutRaw))
	{
		i++;
		
		//Extraction du raccourci dans sa forme string
		wxString actRaw;
		wxString stringShortcut = shortcutRaw.BeforeFirst(' ', &actRaw);
		
		//Extraction de l'action
		wxString actSettings;
		wxString act = actRaw.BeforeFirst(' ', &actSettings);
		
		//Extraction des paramétrés de l'action
		wxString setTwo;
		wxString setOne = actSettings.BeforeFirst(' ', &setTwo);
		
		//Conversion du raccourci;
		ShortcutKey shortcutKey(ShortcutKey::stringToShortcutKey(stringShortcut));
		
		//Association du raccourci à son actions
		if(act == "tr")
		{
			//lien le raccourci à une action
			ActTranslation *action = new ActTranslation(&_word, setOne, setTwo);
			_shortcutAction[shortcutKey] = action;
			
			//Ajout et active le raccourci
			int id = _shortcut->creat(shortcutKey);
			Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
		}
		#if defined(__USE_TTS__)
		else if(act == "ts")
		{
			//lien le raccourci à une action
			ActSay *action = new ActSay(&_word, setOne);
			_shortcutAction[shortcutKey] = action;
			
			//Ajout et active le raccourci
			int id = _shortcut->creat(shortcutKey);
			Bind(EVT_SHORTCUT, &App::OnShortcut, this, id);
		}
		#endif
	}
}

void App::uninstallShortcut()
{
	//Unbind les événement lier au raccourci et supprime les actions.
	for(auto &it: _shortcutAction)
	{
		int id = _shortcut->getId(it.first);
		Unbind(EVT_SHORTCUT, &App::OnShortcut, this, id);
			
		delete it.second;
	}
	
	//Supprime les Associations
	_shortcutAction.clear();
	
	//Supprime touts les raccourcis
	_shortcut->removeAll();
}
