//03.01.2013

#ifndef CONF_H
#define CONF_H

#include <wx/string.h>

class Conf
{
	public:
		Conf();
		~Conf();
		
		void loadFile(wxString name);
	
	private:
};

#endif //CONF_H
