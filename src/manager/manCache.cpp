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
#include <wx/filename.h>


// *****************************************************************************
// Class ManCache
// *****************************************************************************

ManCache::ManCache()
: _workInTmp(false)
{
	_directoryUser = wxStandardPaths::Get().GetUserDataDir()+"/caches";
	_directoryTmp = wxStandardPaths::Get().GetTempDir()+"/"+PROJECT_NAME+"/caches";
	
	_workDirectory = _directoryUser;
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
	wxArrayString nameFiles;
	wxDir::GetAllFiles(_workDirectory, &files);
	
	wxFileName file;
	for(auto it: files)
	{
		file.Assign(it);
		nameFiles.Add(file.GetName());
	}
	
	return nameFiles;
}

void ManCache::workToTmp(bool toTmp)
{
	//To Tmp
	if(!_workInTmp && toTmp)
	{
		wxDir::Make(_directoryTmp, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);

		wxArrayString files = getNamesCaches();
		for(auto it: files)
			wxCopyFile(_directoryUser+"/"+it+".cac", _directoryTmp+"/"+it+".cac");
		
		_workDirectory = _directoryTmp;
	}
	//From Tmp
	else if(_workInTmp && !toTmp)
	{
		wxDir::Remove(_directoryTmp, wxPATH_RMDIR_FULL|wxPATH_RMDIR_RECURSIVE);
		_workDirectory = _directoryUser;
	}
	else
		return;
	
	_workInTmp = toTmp;
}

void ManCache::applyTmp()const
{
	if(_workInTmp)
	{
		wxDir::Remove(_directoryUser, wxPATH_RMDIR_FULL|wxPATH_RMDIR_RECURSIVE);
		wxDir::Make(_directoryUser);
		
		wxArrayString files = getNamesCaches();
		for(auto it: files)
			wxCopyFile(_directoryTmp+"/"+it+".cac", _directoryUser+"/"+it+".cac");
	}
}

void ManCache::manLoad(wxFileConfig&)
{
}

void ManCache::manSave(wxFileConfig&)const
{
	applyTmp();
}