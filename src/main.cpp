//! \file **************************************************************
//! \brief Source Poins d'entrée de l'application.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.15
//! \date 12.12.12
//!
//! ********************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#include "main.hpp"
#include "resource.hpp"
#include "notification.hpp"
#include "managerAction.hpp"
//#include "managerList.hpp"
#include "dialogPreferences.hpp"

#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <unistd.h>

//TEST
#include <iostream>
#include "cache.hpp"

// *********************************************************************
// Class App
// *********************************************************************

IMPLEMENT_APP(App);

void printerr(Status_e err)
{
	switch(err)
	{
		case SUCCESS:
		std::cout << "SUCCESS" << std::endl;
		break;
		case FILE_NO_NAME:
		std::cout << "FILE_NO_NAME" << std::endl;
		break;
		case FILE_NO_REMOVE:
		std::cout << "FILE_NO_REMOVE" << std::endl;
		break;
		case FILE_OPEN_FAILED:
		std::cout << "FILE_OPEN_FAILED" << std::endl;
		break;
		case FILE_CREATE_FAILED:
		std::cout << "FILE_CREATE_FAILED" << std::endl;
		break;
		case FILE_READ_ERROR:
		std::cout << "FILE_READ_ERROR" << std::endl;
		break;
		case FILE_WRITE_ERROR:
		std::cout << "FILE_WRITE_ERROR" << std::endl;
		break;
		case EMPTY:
		std::cout << "EMPTY" << std::endl;
		break;
		case NO_EMPTY:
		std::cout << "NO_EMPTY" << std::endl;
		break;
		case TEXT_EXIST:
		std::cout << "TEXT_EXIST" << std::endl;
		break;
		case TEXT_NO_EXIST:
		std::cout << "TEXT_NO_EXIST" << std::endl;
		break;
	}
}

void printtextanddatatext(wxString const& text, DataText const& dataText)
{
	std::cout << text << " : " << dataText.getMainTranslation() << std::endl;
	std::cout << "Knowledge = " ;
	switch(dataText.getKnowledge())
	{
		case KNOWLEDGE_UNKNOWN:
		std::cout << "KNOWLEDGE_UNKNOWN" << std::endl;
		break;
		case KNOWLEDGE_LITTLE_KNOWN:
		std::cout << "KNOWLEDGE_LITTLE_KNOWN" << std::endl;
		break;
		case KNOWLEDGE_KNOWN:
		std::cout << "KNOWLEDGE_KNOWN" << std::endl;
		break;
		case KNOWLEDGE_VERY_KNOWN:
		std::cout << "KNOWLEDGE_VERY_KNOWN" << std::endl;
		break;
	}
	std::cout << "NbTranslation = " << dataText.getNbTranslation() << std::endl;
	for(auto& itn: dataText.getNatures())
	{
		std::cout << "+ " << itn << std::endl;
		
		for(auto& it: dataText.getTranslations(itn))
			std::cout << "| " << it << std::endl;
	}
}

bool App::OnInit()
{  	
	//Init général
	wxInitAllImageHandlers();
	SetExitOnFrameDelete(false);
	_taskIcon = nullptr;
	
	//Changement du Préfixe seulement sous unix
	#if defined(__UNIX__)
	wxStandardPaths::Get().SetInstallPrefix("/usr");
	#endif
	
	//On charge le langage par défaut de l'os.
	_locale = new wxLocale(wxLANGUAGE_DEFAULT);
	_locale->AddCatalog(PROJECT_NAME);
	
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
	
	//Chargement des ressource se trouvent dans le fichier de config.
	Resource::getInstance()->load(fileConfig);
	
	//Chargement de la configuration des notifications.
	Notification::getInstance()->load(fileConfig);
	
	//Crée de l'instance de ActionManager et Installation des raccourcis/actions
	ManagerAction::getInstance()->load(fileConfig);

	//Chargement des listes se trouvent dans le fichier de config.
	//ManagerList::getInstance()->load(fileConfig);

	//Création du menu ou pas.
	if(Resource::getInstance()->getShowMenu())
		_taskIcon = new TaskIcon();
		
	//Bind pour attraper l'évènement pour quitter qui peut venir de n'importe où dans le code.
	Bind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, wxID_EXIT);
	
	
	///TEST
	Cache myCache;
	myCache.setFileName(wxFileName("/home/antoine/testcache"));
	
	wxString lgsrc = "en";
	wxString lgto = "fr";
	printerr(myCache.setLanguages(lgsrc, lgto));
	std::cout << lgsrc << " : " << lgto << std::endl;
	
	std::map<wxString, DataText> texts;
	
	
	///Lecture du cache ------------------------------------------
	//wxArrayString texts;
	//printerr(myCache.getTexts(&texts, KNOWLEDGE_ALL, 7));
	
	//for(auto& it: texts)
		//std::cout << it << std::endl;
		
	///text existe ? ------------------------------------------
	//printerr(myCache.existText("disturb"));

	
	///Écriture du cache ------------------------------------------
	
	texts.clear();
	wxString text = "until";
	DataText myDataText;
	myDataText.clear();
	myDataText.setKnowledge(KNOWLEDGE_LITTLE_KNOWN);
	myDataText.setNbTranslation(3);
	myDataText.setMainTranslation("jusqu'à ce que");
	myDataText.addTranslation("conjonction", "jusqu'à ce que");
	myDataText.addTranslation("conjonction", "tant que");
	myDataText.addTranslation("conjonction", "avant que");
	myDataText.addTranslation("conjonction", "en attendant que");
	
	myDataText.addTranslation("préposition", "jusqu'à");
	myDataText.addTranslation("préposition", "avant");
	
	texts[text] = myDataText;
	 
	text = "disturb";
	myDataText.clear();
	myDataText.setKnowledge(KNOWLEDGE_KNOWN);
	myDataText.setNbTranslation(10);
	myDataText.setMainTranslation("déranger");
	myDataText.addTranslation("pronom", "déranger");
	myDataText.addTranslation("pronom", "troubler");
	myDataText.addTranslation("pronom", "inquiéter");
	myDataText.addTranslation("pronom", "remuer");
	myDataText.addTranslation("pronom", "importuner");
	myDataText.addTranslation("pronom", "dérégler");
	myDataText.addTranslation("pronom", "émouvoir");
	myDataText.addTranslation("pronom", "disperser");
	
	texts[text] = myDataText;
	
	printerr(myCache.replaceTexts(texts));
	
	///Lecture du cache ------------------------------------------
	texts.clear();
	printerr(myCache.getTextsAndData(&texts));
	
	for(auto& it: texts)
		printtextanddatatext(it.first, it.second);
	
	std::cout << "----------------------------------------" << std::endl;
	
	///update texte ------------------------------------------
	text = "disturb";
	myDataText.clear();
	myDataText.setKnowledge(KNOWLEDGE_KNOWN);
	myDataText.setNbTranslation(10);
	myDataText.setMainTranslation("déranger");
	myDataText.addTranslation("pronom", "déranger@");
	myDataText.addTranslation("pronom", "troubler");
	myDataText.addTranslation("pronom", "inquiéter");
	myDataText.addTranslation("pronom", "remuer");
	myDataText.addTranslation("pronom", "importuner");
	myDataText.addTranslation("pronom", "dérégler");
	myDataText.addTranslation("pronom", "émouvoir");
	myDataText.addTranslation("pronom", "disperser");
	
	printerr(myCache.updateText(text, myDataText));
	
		
	///Lecture du cache ------------------------------------------
	texts.clear();
	printerr(myCache.getTextsAndData(&texts));
	
	for(auto& it: texts)
		printtextanddatatext(it.first, it.second);
	
	std::cout << "----end-----" << std::endl;
	///TEST
	
		
	return true;
}

int App::OnExit()
{	
	//Unbind l'évènement pour quitter.
	Unbind(wxEVT_COMMAND_MENU_SELECTED, &App::OnExit, this, wxID_EXIT);
	
	//Suppression du menu.
	delete _taskIcon;
	
	//Suppression du mangeur d'action.
	ManagerAction::kill();
	
	//Suppression des ressources.
	Resource::kill();
	
	//Suppression des notifications.
	Notification::kill();
	
	//Suppression des liste.
	//ManagerList::kill();
	
	//Suppression du module de la traduction de l'application.
	delete _locale;
	
	return 0;
}

void App::OnExit(wxCommandEvent&)
{		
	ExitMainLoop();
}
