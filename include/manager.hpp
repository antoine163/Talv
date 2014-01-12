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
//! \todo détailler ...
//! \todo Crées la page pageCreateTranslator

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
			static manager** getPtr()
	

#define IMPLEMENT_MANAGER(manager)								\
		void manager::load(wxFileConfig& fileConfig)			\
		{														\
			fileConfig.SetPath(#manager "/");					\
			manLoad(fileConfig);								\
			fileConfig.SetPath("..");							\
		}														\
																\
		void manager::save(wxFileConfig& fileConfig)const		\
		{														\
			fileConfig.SetPath(#manager "/");					\
			manSave(fileConfig);								\
			fileConfig.SetPath("..");							\
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
//! \brief Classe de base pour crées des GUIs pour les préférences des managers.
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
		//! \brief Chargement de la configuration du manager.
		//!
		//! Cette méthode est implémenter dans la define \b IMPLEMENT_MANAGER.
		//!  Dans les classe enfant, Vous devais tout de même définir et
		//! implémenter la méthode de prototype:
		//! \code
		//! virtual void manLoad(wxFileConfig& fileConfig); 
		//! \endcode 
		virtual void load(wxFileConfig& fileConfig)=0;
		
		//! \brief Sauvegarde de la configuration du manager.
		//!
		//! Cette méthode est implémenter dans la define \b IMPLEMENT_MANAGER.
		//! Dans les classe enfant, vous devais tout de même définir et
		//! implémenter la méthode de prototype:
		//! \code
		//! virtual void manSave(wxFileConfig& fileConfig); 
		//! \endcode 
		virtual void save(wxFileConfig& fileConfig)const=0;
		
		virtual WinManager* newEditWindow(wxWindow* parent);
		
		//! \brief Créations de tous les managers de l'app.
		static void createManagers();
		//! \brief Suppression de tous les managers de l'app.
		static void killManagers();
		//! \brief Chargement de la configuration de tous les managers de l'app.
		static void loadManagers();
		//! \brief Sauvegarde de la configuration de tous les managers de l'app.
		static void saveManagers();
		//! \brief Obtenir l"instance de tous les managers de l'app.
		static std::vector<Manager*>& getManagers();
		
	protected:
		//! \brief Constructeur.
		Manager();
		//! \brief Destructeur.
		virtual ~Manager();
		
		virtual void manLoad(wxFileConfig& fileConfig)=0;
		virtual void manSave(wxFileConfig& fileConfig)const=0;
}; 

#endif //MANAGER_H
