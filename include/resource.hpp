//30.03.2013
//v0.1


#ifndef RESOURCE_H
#define RESOURCE_H

#include "singleton.hpp"

#include <wx/string.h>
#include <vector>
#include <map>

class Resource : public Singleton<Resource>
{	
	friend class Singleton<Resource>;
	
	public:
		std::map<wxString, wxString> const& getLangs();
		std::vector<wxString> const& getActions();
	
	private:
		Resource();
		~Resource();
		
		std::map<wxString, wxString> _langs;
		std::vector<wxString> _actions;
};

#endif //RESOURCE_H
