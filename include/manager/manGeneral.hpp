//! \file **********************************************************************
//! \brief Header ManGeneral
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

#ifndef MAN_GENERAL_H
#define MAN_GENERAL_H

//App
#include "manager.hpp"
#include "taskIcon.hpp"

//Std
#include <map>

//WxWidgets
#include <wx/icon.h>
#include <wx/string.h>

// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

//! \ingroup managers
//! \brief ManGeneral
class ManGeneral : public Manager
{
	DECLARE_MANAGER(ManGeneral);
	
	public:
		//Langage
		wxArrayString getLgs()const;
		wxString acrToLg(wxString const& acr)const;
		wxString lgToAcr(wxString const& lg)const;
		
		//Presse papier
		wxString getClipboard()const;
		
		//TaskIcon
		void showTaskIcon(bool show = true);
		bool isShowTaskIcon()const;
		
		////Lancement au démarrage
		//void launchAtStartup(bool launch = true);
		//bool isLaunchAtStartup()const;
		
		//Icônes
		wxIcon const& getIconApp()const;
		wxString const& getPathIcons()const;
	
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		//! \brief Liste des acronymes et des langues <acronyme, langue>.
		std::map<wxString, wxString> _langues;
		
		wxString _pathIcons;
		wxIcon _iconApp;
		TaskIcon* _taskIcon;
};

#endif //MAN_GENERAL_H
