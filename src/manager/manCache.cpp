//! \file **********************************************************************
//! \brief Source ManCache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 19.11.2013
//!
//! ****************************************************************************

//App
#include "manager/manCache.hpp"

//WxWidgets
#include <wx/dir.h>
#include <wx/filefn.h> 
#include <wx/stdpaths.h>
#include <wx/arrstr.h>


// *****************************************************************************
// Class ManCache
// *****************************************************************************

ManCache::ManCache()
: _workInTmp(false)
{
	_workDirectory = wxStandardPaths::Get().GetUserDataDir()+"/cache";
}

ManCache::~ManCache()
{
}

IMPLEMENT_MANAGER(ManCache);

WinManager* ManCache::newEditWindow(wxWindow*)
{
	return nullptr;
}

Cache ManCache::getCache(wxLanguage const& lgsrc, wxLanguage const& lgto)
{
	return getCache(wxLocale::GetLanguageName(lgsrc)+"To"+wxLocale::GetLanguageName(lgto));
}

Cache ManCache::getCache(wxString const& name)
{
	Cache rCache;
	
	if(wxFileExists(name+".cac"))
		rCache.setFileName(name+".cac");
	
	return rCache;
}

wxArrayString ManCache::getNameCaches()const
{
	wxArrayString files;
	wxDir::GetAllFiles(_workDirectory, &files);
	
	return files;
}

void ManCache::workToTmp(bool toTmp, bool apply)
{
	//To Tmp
	if(!_workInTmp && toTmp)
	{
		wxString workDirectoryOld = _workDirectory;
		_workDirectory = wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME+"/cache";
		wxDir::Make(_workDirectory);
		
		if(apply)
		{
			wxArrayString files;
			wxDir::GetAllFiles(workDirectoryOld, &files);
			
			for(auto it: files)
				wxCopyFile(workDirectoryOld+"/"+it, _workDirectory+"/"+it);
		}
	}
	//From Tmp
	else if(_workInTmp && !toTmp)
	{
		wxString workDirectoryOld = _workDirectory;
		_workDirectory = wxStandardPaths::Get().GetUserDataDir()+"/cache";
		
		if(apply)
		{
			wxDir::Remove(_workDirectory, wxPATH_RMDIR_FULL);
			wxDir::Make(_workDirectory);
			
			wxArrayString files;
			wxDir::GetAllFiles(workDirectoryOld, &files);
			
			for(auto it: files)
				wxCopyFile(workDirectoryOld+"/"+it, _workDirectory+"/"+it);
		}
		
		wxDir::Remove(workDirectoryOld, wxPATH_RMDIR_FULL);
	}
	else
		return;
	
	_workInTmp = toTmp;
}

void ManCache::manLoad(wxFileConfig&)
{
}

void ManCache::manSave(wxFileConfig&)const
{
}