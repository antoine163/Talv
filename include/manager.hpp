//! \file **********************************************************************
//! \brief Header Manager
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

#ifndef MANAGER_H
#define MANAGER_H

//! \defgroup manager Managers
//! \brief Liste des managers
//!
//! Les classes dans cette section sont des gestionnaires de données ou des
//! utilitaires.
//! Les classes préfixer par \b Man sont touts basée sur la classe \ref Manager.

//! \defgroup winmanager Window manager
//! \brief Liste des windows managers

//Stl
#include <vector>

//WxWidgets
#include <wx/fileconf.h>
#include <wx/window.h>

#define DECLARE_MANAGER(manager)								\
		friend class Manager;									\
		public:													\
			virtual void load(wxFileConfig& fileConfig);		\
			virtual void save(wxFileConfig& fileConfig)const;	\
			static manager& get();								\
		private:												\
			manager();											\
			virtual ~manager();									\
			static manager** getPtr();
	

#define IMPLEMENT_MANAGER(manager)								\
		void manager::load(wxFileConfig& fileConfig)			\
		{														\
			fileConfig.SetPath(#manager "/");					\
			manLoad(fileConfig);								\
		}														\
																\
		void manager::save(wxFileConfig& fileConfig)const		\
		{														\
			fileConfig.SetPath(#manager "/");					\
			manSave(fileConfig);								\
		}														\
																\
		manager& manager::get()									\
		{														\
			return **getPtr();									\
		}														\
																\
		manager** manager::getPtr()								\
		{														\
			static manager* _ins = nullptr;						\
			return &_ins;										\
		}

// *****************************************************************************
// Class WinManager
// *****************************************************************************

//! \ingroup winmanager
//! \brief Classe de base pour crées des GUIs pour managers.
class WinManager : public wxWindow 
{	
	public:
		WinManager(wxWindow *parent, const wxString &name);
		virtual ~WinManager();
		
		virtual void refreshGuiFromManager(){};
		virtual void refreshManagerFromGui()const{};
	
	protected:
}; 

// *****************************************************************************
// Class Manager
// *****************************************************************************

//! \ingroup manager
//! \brief Classe de base pour crées des managers.
class Manager
{	
	public:
		//! \brief Charger la configuration du manager.
		//! Pas forcement dans le fichier de config.
		//! Implémenter dans IMPLEMENT_MANAGER.
		virtual void load(wxFileConfig& fileConfig)=0;
		
		//! \brief Sauvegarde la configuration du manager.
		//! Pas forcement dans le fichier de config.
		//! Implémenter dans IMPLEMENT_MANAGER.
		virtual void save(wxFileConfig& fileConfig)const=0;
		
		virtual WinManager* newEditWindow(wxWindow* parent);
		
		
		static void createManagers();
		static void killManagers();
		static void loadManagers();
		static void saveManagers();
		static std::vector<Manager*>& getManagers();
		
	protected:
		Manager();
		virtual ~Manager();
		
		virtual void manLoad(wxFileConfig& fileConfig)=0;
		virtual void manSave(wxFileConfig& fileConfig)const=0;
}; 

#endif //MANAGER_H
