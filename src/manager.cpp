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

//
#define CREATE_MANAGER(manager) manager** _ins = manager::getPtr();		\
								*_ins = new manager();					\
								getManagers().push_back(*_ins);
								
#define KILL_MANAGER(manager) 	manager** _ins = manager::getPtr();		\
								delete *_ins;							\
								*_ins = nullptr;
#include "managerDefs.hpp"

// *****************************************************************************
// Class Manager
// *****************************************************************************

Manager::Manager()
{
}

Manager::~Manager()
{
}

wxWindow* Manager::newEditWindow(wxWindow*)
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
		
std::vector<Manager*>& Manager::getManagers()
{
	static std::vector<Manager*> _iManagers;
	return _iManagers;
}