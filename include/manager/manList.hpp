//! \file **********************************************************************
//! \brief Header Gestion des listes
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 2.0
//! \date 02.05.2013
//!
//! ****************************************************************************

#ifndef MAN_LIST_H
#define MAN_LIST_H

//App
#include "manager.hpp"
#include "control/ctrlDataList.hpp"
#include "list.hpp"

//WxWidgets
#include <wx/string.h>
#include <wx/language.h>

// *****************************************************************************
// Class ManList
// *****************************************************************************

//! \ingroup manager
//! \brief ManList
class ManList : public Manager
{
	DECLARE_MANAGER(ManList);
	
	public:
		virtual WinManager* newEditWindow(wxWindow* parent);
		
		bool existList(wxString const& name)const;
		bool createList(wxString const& name, wxLanguage lgsrc, wxLanguage lgto);
		wxArrayString getNamesLists()const;
		wxArrayString getNamesLists(wxLanguage lgsrc, wxLanguage lgto)const;
		List getList(wxString const& name)const;
		bool remove(wxString const& name);
									
		void workToTmp(bool toTmp = true);
		void applyTmp()const;
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		bool _workInTmp;
		wxString _workDirectory;
		wxString _directoryUser;
		wxString _directoryTmp;
};

// *****************************************************************************
// Class WinManList
// *****************************************************************************

//! \brief WinManList
class WinManList : public WinManager
{
	public:
		WinManList(wxWindow* parent);
		~WinManList();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onNew(wxCommandEvent& event);
		void onEdit(wxCommandEvent& event);
		void onFind(wxCommandEvent& event);
		void onDelete(wxCommandEvent& event);
		void onLearn(wxCommandEvent& event);
		void onExport(wxCommandEvent& event);
		void onImport(wxCommandEvent& event);
		void onPreview(wxCommandEvent& event);
		void onPrint(wxCommandEvent& event);
		
		bool ensureVisible(wxString nameList);
		
		CtrlDataList* _ctrlDataList;
};

#endif //MAN_LIST_H
