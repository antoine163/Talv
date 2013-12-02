//! \file **************************************************************
//! \brief Header ManagerBase
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 30.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef MANAGER_BASE_H
#define MANAGER_BASE_H

//Stl
#include <vector>

//WxWidgets
#include <wx/fileconf.h>
#include <wx/window.h>

// *********************************************************************
// Class ManagerBase
// *********************************************************************

//! \brief
class ManBase
{	
	
	public:
		////! \brief Charger la configuration du manager.
		//virtual void load(wxFileConfig& fileConfig);
		
		////! \brief Sauvegarde la configuration du manager.
		//virtual void save(wxFileConfig& fileConfig)const;
		
		
		//virtual wxWindow* newEditWindow(wxWindow* parent)=0;
		
	protected:
		ManagerBase(){}
		virtual ~ManagerBase(){}
};

// *********************************************************************
// Class ManagerMain
// *********************************************************************

////! \brief
//class ManagerMain : public ManagerBase<ManagerMain>
//{	
	////friend class ManagerBase<ManagerMain>;
	////friend class Singleton<ManagerMain>;
	
	//public:
		
		//////! \brief Charger la configuration du manager.
		////virtual void load(wxFileConfig& fileConfig);
		
		//////! \brief Sauvegarde la configuration du manager.
		////virtual void save(wxFileConfig& fileConfig)const;
		
		
		////virtual wxWindow* newEditWindow(wxWindow* parent);
		
		////static std::vector<ManagerBase*>& getManagers();
		
		////static void creatAllManagers();
		////static void killAllManagers();
	
	//private:
		//ManagerMain(){}
		//virtual ~ManagerMain(){}
//};

#endif //MANAGER_BASE_H
