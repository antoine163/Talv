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

WinManager* ManCache::newEditWindow(wxWindow* parent)
{
	return nullptr;
}

Cache ManCache::getCache(wxLanguage const& lgsrc, wxLanguage const& lgto)
{
	return Cache();
}

Cache ManCache::getCache(wxString const& name)
{
	return Cache();
}

wxArrayString ManCache::getNameCaches()const
{	
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
			{
				
			}
		}
	}
	//From Tmp
	else if(_workInTmp && !toTmp)
	{
		if(apply)
		{
		}
		
		//wxDir::Remove(	,
						//wxPATH_RMDIR_FULL);
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