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
	_workDirectory = wxStandardPaths::Get().GetUserDataDir()+"/caches";
	if(!wxDir::Exists(_workDirectory))
		wxDir::Make(_workDirectory);
}

ManCache::~ManCache()
{
}

IMPLEMENT_MANAGER(ManCache);

WinManager* ManCache::newEditWindow(wxWindow*)
{
	return nullptr;
}

bool ManCache::existCache(wxLanguage lgsrc, wxLanguage lgto)const
{
	wxString fileName = wxLocale::GetLanguageName(lgsrc)+"To"+wxLocale::GetLanguageName(lgto)+".cac";
	return wxFileExists(_workDirectory+"/"+fileName);
}

bool ManCache::createCache(wxLanguage lgsrc, wxLanguage lgto)
{
	if(existCache(lgsrc, lgto))
		return false;
		
	wxString fileName = wxLocale::GetLanguageName(lgsrc)+"To"+wxLocale::GetLanguageName(lgto)+".cac";
	Cache newCache;
	newCache.setFileName(_workDirectory+"/"+fileName);
	newCache.setLanguages(lgsrc, lgto);
	
	return true;
}

Cache ManCache::getCache(wxLanguage lgsrc, wxLanguage lgto)
{
	Cache rCache;
	wxString fileName = wxLocale::GetLanguageName(lgsrc)+"To"+wxLocale::GetLanguageName(lgto)+".cac";
	rCache.setFileName(_workDirectory+"/"+fileName);
	return rCache;
}

Cache ManCache::getCache(wxString const& name)
{
	Cache rCache;
	wxString fileName = name+".cac";
	rCache.setFileName(_workDirectory+"/"+fileName);
	return  rCache;
}

wxArrayString ManCache::getNamesCaches()const
{
	wxArrayString files;
	wxDir::GetAllFiles(_workDirectory, &files);
	
	for(auto it: files)
		it = it.BeforeLast('.');
	
	return files;
}

void ManCache::workToTmp(bool toTmp, bool apply)
{
	//To Tmp
	if(!_workInTmp && toTmp)
	{
		wxString workDirectoryOld = _workDirectory;
		_workDirectory = wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME+"/caches";
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
		_workDirectory = wxStandardPaths::Get().GetUserDataDir()+"/caches";
		
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