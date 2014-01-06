//! \file **********************************************************************
//! \brief Source pour génère l'enum Key_e,
//! la méthode wxString ShortcutKey::keyToString(Key_e key),
//! la méthode Key_e ShortcutKey::stringToKey(wxString key),
//! la méthode wxArrayString ShortcutKey::getKeysStrings()
//! 
//! \note Écrit à la rache.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 05.01.2014
//!
//! ****************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void parseFileFromX11(std::ifstream& file, std::map<std::string, std::vector<std::string>>& vals);
void parseFileFromWin(std::ifstream& file, std::vector<std::string>& vals);

void genKey_e(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin);
void genKeyToString(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin);
void genStringToKey(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin);
void genGetKeysStrings(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin);

std::string upper(std::string const& str);
std::string lower(std::string const& str);

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cout << "You must specify the folder location of file keysymdef.h, XF86keysym.h and winuser.h!"  << std::endl;
		std::cout << "Look the file README for more detail" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::string filenamekeysymdef = argv[1];
	filenamekeysymdef += "/keysymdef.h";
	std::string filenameXF86keysym = argv[1];
	filenameXF86keysym += "/XF86keysym.h";
	std::string filenamewinuser = argv[2];
	filenamewinuser += "/winuser.h";
	
	//Ouverture des fichiers
	
	std::ifstream filekeysymdef(filenamekeysymdef);
	if(!filekeysymdef.is_open())
	{
		std::cout << "Error opening file: " << filenamekeysymdef << std::endl;
		return EXIT_FAILURE;
	}
	
	std::ifstream fileXF86keysym(filenameXF86keysym);
	if(!fileXF86keysym.is_open())
	{
		std::cout << "Error opening file: " << filenameXF86keysym << std::endl;
		
		filekeysymdef.close();
		return EXIT_FAILURE;
	}
	
	std::ifstream filewinuser(filenamewinuser);
	if(!filewinuser.is_open())
	{
		std::cout << "Error opening file: " << filenamewinuser << std::endl;
		
		filekeysymdef.close();
		fileXF86keysym.close();
		return EXIT_FAILURE;
	}
	
	std::map<std::string, std::vector<std::string>> valsX11;
	std::vector<std::string> valsWin;
	
	//Parse les fichiers.
	parseFileFromX11(filekeysymdef, valsX11);
	//parseFileFromX11(fileXF86keysym, valsX11);
	parseFileFromWin(filewinuser, valsWin);
	
	
	//Fermeture des fichiers.
	filekeysymdef.close();
	fileXF86keysym.close();
	filewinuser.close();
	
	//Génération des méthodes.
	genKey_e(valsX11, valsWin);
	std::cout << std::endl;
	genKeyToString(valsX11, valsWin);
	std::cout << std::endl;
	genStringToKey(valsX11, valsWin);
	std::cout << std::endl;
	genGetKeysStrings(valsX11, valsWin);
		
	return EXIT_SUCCESS;
}

void parseFileFromX11(std::ifstream& file, std::map<std::string, std::vector<std::string>>& vals)
{
	std::string word;
	std::string def = "none";
	bool defineIsRead = false;
	while(file.good())
	{		
		file >> word;
		
		if(defineIsRead)
		{
			if(		!(word.size() == 4 &&
					((word[3] >= 0x41 && word[3] <= 0x5a) ||
					(word[3] >= 0x61 && word[3] <= 0x7a) ||
					(word[3] >= 0x30 && word[3] <= 0x39))) &&
					word != "XK_VoidSymbol")
			{					
				bool add = true;
				for(auto it: vals)
				{
					for(auto it2: it.second)
					{
						if(upper(it2) == upper(word))
							add = false;
					}
				}
				
				if(add)
					vals[def].push_back(word);
			}
			
			defineIsRead = false;
		}
		else if(word == "#define")
			defineIsRead = true;
		else if(word == "#ifdef")
			file >> def;
		else if(word == "deprecated" && !vals.empty() && !vals[def].empty())
			vals[def].pop_back();
		else
			defineIsRead = false;
	}
}

void parseFileFromWin(std::ifstream& file, std::vector<std::string>& vals)
{
	std::string word;
	bool NOVIRTUALKEYCODES_isRead = false;
	bool defineIsRead = false;
	while(file.good())
	{
		file >> word;
		
		if(NOVIRTUALKEYCODES_isRead && defineIsRead)
		{
			if(	word != "VK_LBUTTON" &&
				word != "VK_RBUTTON" &&
				word != "VK_MBUTTON" &&
				word != "VK_XBUTTON1"&& 
				word != "VK_XBUTTON2")
			{
				vals.push_back(word);
			}
			
			defineIsRead = false;
		}
		else if(word == "#define")
			defineIsRead = true;
		else if(word == "NOVIRTUALKEYCODES")
			NOVIRTUALKEYCODES_isRead = true;
		else if(NOVIRTUALKEYCODES_isRead && word == "#endif")
			break;
		else
			defineIsRead = false;
	}
}

void genKey_e(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin)
{
	std::cout << "enum Key_e" << std::endl;
	std::cout << "{" << std::endl;
	
	std::cout << "\t#ifdef __UNIX__" << std::endl;
	for(auto it: valsX11)
	{
		std::cout << "\t#ifdef " << it.first << std::endl;
		for(auto it2: it.second)
		{
			size_t pos = it2.find('_');
			std::cout << "\tKEY" << upper(it2.c_str()+pos) << "=\t\t" << it2 << "," << std::endl;
		}
		std::cout << "\t#endif" << std::endl;
	}	
	std::cout << "\t#elif __WXMSW__" << std::endl;
	for(auto it: valsWin)
	{
		size_t pos = it.find('_');
		std::cout << "\tKEY" << upper(it.c_str()+pos) << "=\t\t" << it << "," << std::endl;
	}
	std::cout << "\t#endif" << std::endl;
	
	for(char c = 'A'; c <= 'Z'; c++)
	{
		std::cout << "\tKEY_" << c << "=\t\t'" << c << "'" << "," << std::endl;
	}
	std::cout << "\tKEY_NONE=\t\t" << 0 << std::endl;
	
	std::cout << "};" << std::endl;
}

void genKeyToString(std::map<std::string, std::vector<std::string>>&, std::vector<std::string>& valsWin)
{
	std::cout << "wxString ShortcutKey::keyToString(Key_e key)" << std::endl;
	std::cout << "{" << std::endl;
	
	std::cout << "\t#ifdef __UNIX__" << std::endl;
	std::cout << "\tDisplay* display = (Display*)wxGetDisplay();" << std::endl;
	std::cout << "\tKeyCode keyCode = XKeysymToKeycode(display, (KeySym)key);" << std::endl;
	std::cout << "\tKeySym keySym = XkbKeycodeToKeysym(display, keyCode, 0, 0);" << std::endl;
	std::cout << "\treturn XKeysymToString(keySym);" << std::endl;
	
	std::cout << "\t#elif __WXMSW__" << std::endl;
	for(auto it: valsWin)
	{
		size_t pos = it.find('_')+1;
		std::string keyString;
		keyString = lower(it.c_str()+pos);
		keyString[0] -= 32;
		
		std::cout << "\tif(KEY_" << it.c_str()+pos << ")" << std::endl;
		std::cout << "\t\treturn \"" << keyString << "\";" << std::endl;
	}
	for(char c = 'A'; c <= 'Z'; c++)
	{
		std::cout << "\tif(KEY_" << c << ")" << std::endl;
		std::cout << "\t\treturn \"" << c << "\";" << std::endl;
	}
	std::cout << "\t}" << std::endl;
	
	std::cout << "\t#endif" << std::endl;

	std::cout << std::endl;
	std::cout << "\treturn wxEmptyString;" << std::endl;
	std::cout << "}" << std::endl;
}

void genStringToKey(std::map<std::string, std::vector<std::string>>&, std::vector<std::string>& valsWin)
{
	std::cout << "Key_e ShortcutKey::stringToKey(wxString key)" << std::endl;
	std::cout << "{" << std::endl;
	
	std::cout << "\tkey.MakeUpper();" << std::endl;
	std::cout << "\t#ifdef __UNIX__" << std::endl;
	std::cout << "\tKeySym keySym = XStringToKeysym(key.c_str());" << std::endl;
	std::cout << "\tif(keySym == NoSymbol)" << std::endl;
	std::cout << "\t\treturn KEY_NONE;" << std::endl;
	std::cout << "\telse" << std::endl;
	std::cout << "\t{" << std::endl;
	std::cout << "\t\tDisplay* display = (Display*)wxGetDisplay();" << std::endl;
	std::cout << "\t\tKeyCode keyCode = XKeysymToKeycode(display, keySym);" << std::endl;
	std::cout << "\t\tkeySym = XkbKeycodeToKeysym(display, keyCode, 0, 0);" << std::endl;
	std::cout << "\t\treturn (Key_e)keySym;" << std::endl;
	std::cout << "\t}" << std::endl;
	
	std::cout << "\t#elif __WXMSW__" << std::endl;
	for(auto it: valsWin)
	{
		size_t pos = it.find('_')+1;
		std::cout << "\tif(key == \"" << it.c_str()+pos << "\")" << std::endl;
		std::cout << "\t\treturn KEY_" << it.c_str()+pos << ";" << std::endl;
	}
	for(char c = 'A'; c <= 'Z'; c++)
	{
		std::cout << "\tif(key == KEY_" << c << ")" << std::endl;
		std::cout << "\t\treturn \"" << c << "\";" << std::endl;
	}
	std::cout << "\t#endif" << std::endl;

	std::cout << std::endl;
	std::cout << "\treturn KEY_NONE;" << std::endl;
	std::cout << "}" << std::endl;
}

void genGetKeysStrings(std::map<std::string, std::vector<std::string>>& valsX11, std::vector<std::string>& valsWin)
{
	std::cout << "wxArrayString ShortcutKey::getKeysStrings()" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "\twxArrayString r;" << std::endl;
	std::cout << std::endl;
	
	std::cout << "\t#ifdef __UNIX__" << std::endl;
	for(auto it: valsX11)
	{
		std::cout << "\t#ifdef " << it.first << std::endl;
		for(auto it2: it.second)
		{
			size_t pos = it2.find('_');
			std::cout << "\tr.Add(keyToString(KEY" << upper(it2.c_str()+pos) << "));" << std::endl;
		}
		std::cout << "\t#endif" << std::endl;
	}
	
	std::cout << "\t#elif __WXMSW__" << std::endl;
	std::cout << "\tr.Alloc(" << valsWin.size() << ");" << std::endl;
	for(auto it: valsWin)
	{
		size_t pos = it.find('_');
		std::cout << "\tr.Add(keyToString(KEY" << upper(it.c_str()+pos) << "));" << std::endl;
	}

	std::cout << "\t#endif" << std::endl;
	
	for(char c = 'A'; c <= 'Z'; c++)
	{
		std::cout << "\tr.Add(keyToString(KEY_" << c << "));" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "\treturn r;" << std::endl;
	std::cout << "}" << std::endl;
}

std::string upper(std::string const& str)
{
	std::string r;
	
	for(auto it: str)
	{
		if(it >= 'a' && it <= 'z')
			r += it-32;
		else
			r += it;
	}
	
	return r;
}

std::string lower(std::string const& str)
{
	std::string r;
	
	for(auto it: str)
	{
		if(it >= 'A' && it <= 'Z')
			r += it+32;
		else
			r += it;
	}
	
	return r;
}
