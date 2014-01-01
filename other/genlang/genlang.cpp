//! \file **********************************************************************
//! \brief Source pour génère la methode ManGeneral::GetLanguages() à partir
//! du fichier misc/languages/langtabl.txt des source de WxWidgets.
//! 
//! \note Écrit à la rache.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 01.01.2014
//!
//! ****************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "You must specify a file input!" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::ifstream file(argv[1]);
	
	char c;
	bool valReading = false;
	bool valToInclude = true;
	std::string languageCurrent;
	std::vector<std::string> languages;
	while(file.good())
	{
		file.get(c);
		if(c == '"')
		{
			if(valReading)
			{
				if(!languageCurrent.empty() && valToInclude)
					languages.push_back(languageCurrent);
				
				languageCurrent.clear();
				valReading = false;
				valToInclude = true;
			}
			else
				valReading = true;
		}
		else if(c == '(')
		{
			valToInclude = false;
		}
		else if(valReading)
		{
			languageCurrent.push_back(c);
		}		
	}
	
	file.close();
	
	std::cout << "wxArrayString ManGeneral::GetLanguages()const" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "\twxArrayString languages;" << std::endl;
	std::cout << "\tlanguages.Alloc(" << languages.size() << ");" << std::endl;
	std::cout << std::endl;
	for(unsigned int i = 0; i < languages.size(); i++)
	{
		std::cout << "\tlanguages.Add(_(\"" << languages[i] << "\"));" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "\treturn languages;" << std::endl;
	std::cout << "}" << std::endl;
		
	return EXIT_SUCCESS;
}