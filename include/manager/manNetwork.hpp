//! \file **********************************************************************
//! \brief Header Gestion réseau
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.12.2013
//!
//! ****************************************************************************

#ifndef MAN_NETWORK_H
#define MAN_NETWORK_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup manager
//! \brief ManNetwork
class ManNetwork : public Manager
{
	DECLARE_MANAGER(ManNetwork);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_NETWORK_H
