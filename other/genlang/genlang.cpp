//! \file **********************************************************************
//! \brief Source pour générer les méthodes
//! wxArrayString ManGeneral::getLanguages()
//! wxLanguage ManGeneral::getSystemLanguage()
//! 
//! \note Écrit à la rache.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 01.01.2014
//!
//! ****************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "You must specify the folder location of file langtabl.txt!" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::string filename = argv[1];
	filename += "/langtabl.txt";
	std::ifstream file(filename);
	if(!file.is_open())
	{
		std::cout << "Error opening file: " << filename << std::endl;
		return EXIT_FAILURE;
	}
	
	char c;
	bool valReading = false;
	std::string enumLanguageCurrent;
	std::string languageCurrent;
	std::map<std::string, std::vector<std::string>> languages;
	while(file.good())
	{
		file >> enumLanguageCurrent;
		
		languageCurrent.clear();
		valReading = false;
		while(file.good())
		{
			file.get(c);
			
			if(c == '"')
			{
				if(valReading)
				{
					languages[languageCurrent].push_back(enumLanguageCurrent);		
					break;
				}
				else
					valReading = true;
			}
			else if(c == '(')
			{
				if(languageCurrent.size() > 0)
					languageCurrent.pop_back();
				
				languages[languageCurrent].push_back(enumLanguageCurrent);		
				break;
			}
			else if(valReading)
				languageCurrent.push_back(c);
		}
		
		while(file.good())
		{
			file.get(c);
			if(c == '\n')
				break;
		}
	}
	
	file.close();
	
	std::cout << "wxArrayString ManGeneral::getLanguages()const" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "\twxArrayString languages;" << std::endl;
	std::cout << "\tlanguages.Alloc(" << languages.size() << ");" << std::endl;
	std::cout << std::endl;
	for(auto it: languages)
		std::cout << "\tlanguages.Add(_(\"" << it.first << "\"));" << std::endl;
	std::cout << std::endl;
	std::cout << "\treturn languages;" << std::endl;
	std::cout << "}" << std::endl;
	
	
	std::cout << "wxLanguage ManGeneral::getSystemLanguage()const" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "\twxLanguage lg = (wxLanguage)wxLocale::GetSystemLanguage();" << std::endl;
	for(auto it: languages)
	{
		if(it.second.size() == 1)
			continue;
			
		std::cout << "\tif(\tlg == " << it.second[0];
		for(size_t i = 1; i < it.second.size(); i++)
		{
			std::cout << " ||" << std::endl;
			std::cout << "\t\tlg == " << it.second[i];
		}
		std::cout << ")" << std::endl << "\t\treturn " << it.second[0] << ";" << std::endl;
	}
	std::cout << "\treturn lg;" << std::endl;
	std::cout << "}" << std::endl;
		
	return EXIT_SUCCESS;
}