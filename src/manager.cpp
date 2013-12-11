//! \file **********************************************************************
//! \brief Source Manager
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

//App
#include "manager.hpp"

//Stl
#include <cstddef>

//WxWidgets
#include <wx/stdpaths.h>

//
#define CREATE_MANAGER(manager) 						\
		manager** _ins ## manager = manager::getPtr();	\
		*_ins ## manager = new manager();				\
		getManagers().push_back(*_ins ## manager);
								
#define KILL_MANAGER(manager) 							\
		manager** _ins ## manager = manager::getPtr();	\
		delete *_ins ## manager;						\
		*_ins ## manager = nullptr;
#include "managerDefs.hpp"

// *****************************************************************************
// Class WinManager
// *****************************************************************************

WinManager::WinManager(wxWindow *parent, const wxString &name)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, name)
{
}

WinManager::~WinManager()
{
}

// *****************************************************************************
// Class Manager
// *****************************************************************************

Manager::Manager()
{
}

Manager::~Manager()
{
}

WinManager* Manager::newEditWindow(wxWindow*)
{
	return nullptr;
}

void Manager::createManagers()
{
	MAKE_CREATE_MANAGERS();
}

void Manager::killManagers()
{
	MAKE_KILL_MANAGERS();
	getManagers().clear();
}

void Manager::loadManagers()
{
	//Préparation du wxFileConfig
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
		
	//Appelle de la méthode load de touts les managers avec le fichier de
	//configuration	.					
	auto _iManagers = getManagers();
	for(auto it : _iManagers)
		it->load(fileConfig);
}

void Manager::saveManagers()
{
	//Préparation du wxFileConfig
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxStandardPaths::Get().GetUserDataDir()+'/'+PROJECT_NAME);
	fileConfig.DeleteAll();
		
	//Appelle de la méthode save de touts les managers avec le fichier de
	//configuration	.					
	auto _iManagers = getManagers();
	for(auto it : _iManagers)
		it->save(fileConfig);
}
		
std::vector<Manager*>& Manager::getManagers()
{
	static std::vector<Manager*> _iManagers;
	return _iManagers;
}