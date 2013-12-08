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
// Enum SizeIcon_e
// *****************************************************************************
enum IconSize_e
{
	ICON_SIZE_16X16,
	ICON_SIZE_32X32
};

// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

//! \ingroup manager
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
		void enableTaskIcon(bool enable = true);
		
		////Lancement au démarrage
		//void launchAtStartup(bool launch = true);
		//bool isLaunchAtStartup()const;
		
		//Icônes
		wxIcon getIconApp(IconSize_e size)const;
		wxString getPathIcons()const;
		wxString getPathIcons(IconSize_e size)const;
		
		
	
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		//! \brief Liste des acronymes et des langues <acronyme, langue>.
		std::map<wxString, wxString> _langues;
		
		TaskIcon* _taskIcon;
};

#endif //MAN_GENERAL_H
