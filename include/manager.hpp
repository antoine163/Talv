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

//! \defgroup managers Liste des managers
//!
//! \brief Les classes dans cette section sont des gestionnaires de données ou
//!  se sont des utilitaires. 
//!
//! Ces classe sont touts basée sur la classe \ref Manager.
//! Elles sont aussi touts basée sur la classe \ref Singleton pour un accès 
//! globale.

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
// Class Manager
// *****************************************************************************

//! \ingroup managers
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
		
		virtual wxWindow* newEditWindow(wxWindow* parent);
		
		
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
