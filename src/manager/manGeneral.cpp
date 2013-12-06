//! \file **********************************************************************
//! \brief Source ManGeneral
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 04.12.2013
//!
//! ****************************************************************************

//App
#include "manager/manGeneral.hpp"

//WxWidgets
#include <wx/stdpaths.h>
#include <wx/clipbrd.h>

//Os
#if defined(__WXMSW__)
#include <windows.h>
#endif

// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

ManGeneral::ManGeneral() : _taskIcon(nullptr)
{
	//Détermination du pach ou se trouve les icônes.
	_pathIcons = "./icons";
	#if defined(__UNIX__) //ET Mac ?
	if(!wxDirExists(_pathIcons))
		_pathIcons = wxStandardPaths::Get().GetDataDir()+"/icons";
	#endif

	//Chargement de l'icône de l'application.
	_iconApp.LoadFile(_pathIcons+"/32x32/talv.png", wxBITMAP_TYPE_PNG);
	
	//creation de la liste des langues.
	_langues["af"] = _("Afrikaans");
	_langues["sq"] = _("Albanian");
	_langues["ar"] = _("Arabic");
	_langues["hy"] = _("Armenian");
	_langues["az"] = _("Azerbaijani");
	_langues["eu"] = _("Basque");
	_langues["be"] = _("Belarusian");
	_langues["bn"] = _("Bengali");
	_langues["bg"] = _("Bulgarian");
	_langues["ca"] = _("Catalan");
	_langues["zh-CN"] = _("Chinese");
	_langues["hr"] = _("Croatian");
	_langues["sr"] = _("Czech");
	_langues["da"] = _("Danish");
	_langues["nl"] = _("Dutch");
	_langues["en"] = _("English");
	_langues["eo"] = _("Esperanto");
	_langues["et"] = _("Estonian");
	_langues["tl"] = _("Filipino");
	_langues["fi"] = _("Finnish");
	_langues["fr"] = _("French");
	_langues["gl"] = _("Galician");
	_langues["ka"] = _("Georgian");
	_langues["de"] = _("German");
	_langues["el"] = _("Greek");
	_langues["gu"] = _("Gujarati");
	_langues["ht"] = _("Haitian Creole");
	_langues["iw"] = _("Hebrew");
	_langues["hi"] = _("Hindi");
	_langues["hu"] = _("Hungarian");
	_langues["is"] = _("Icelandic");
	_langues["id"] = _("Indonesian");
	_langues["ga"] = _("Irish");
	_langues["it"] = _("Italian");
	_langues["ja"] = _("Japanese");
	_langues["kn"] = _("Kannada");
	_langues["ko"] = _("Korean");
	_langues["lo"] = _("Lao");
	_langues["la"] = _("Latin");
	_langues["lv"] = _("Latvian");
	_langues["it"] = _("Lithuanian");
	_langues["mk"] = _("Macedonian");
	_langues["ms"] = _("Malay");
	_langues["mt"] = _("Maltese");
	_langues["no"] = _("Norwegian");
	_langues["fa"] = _("Persian");
	_langues["pl"] = _("Polish");
	_langues["pt"] = _("Portuguese");
	_langues["ro"] = _("Romanian");
	_langues["ru"] = _("Russian");
	_langues["sr"] = _("Serbian");
	_langues["sk"] = _("Slovak");
	_langues["sl"] = _("Slovenian");
	_langues["es"] = _("Spanish");
	_langues["sw"] = _("Swahili");
	_langues["sv"] = _("Swedish");
	_langues["ta"] = _("Tamil");
	_langues["te"] = _("Telugu");
	_langues["th"] = _("Thai");
	_langues["tr"] = _("Turkish");
	_langues["uk"] = _("Ukrainian");
	_langues["ur"] = _("Urdu");
	_langues["vi"] = _("Vietnamese");
	_langues["cy"] = _("Welsh");
	_langues["yi"] = _("Yiddish");
}

ManGeneral::~ManGeneral()
{
	if(_taskIcon != nullptr)
		delete _taskIcon;
}

IMPLEMENT_MANAGER(ManGeneral);


wxArrayString ManGeneral::getLgs()const
{
	wxArrayString tmpArray;
	
	for(auto it: _langues)
		tmpArray.Add(it.second);
	
	return tmpArray;
}

wxString ManGeneral::acrToLg(wxString const& acr)const
{
	return _langues.at(acr);
}

wxString ManGeneral::lgToAcr(wxString const& lg)const
{
	for(auto it: _langues)
	{
		if(it.second == lg)
			return it.first;
	}
	
	return wxEmptyString;
}

wxString ManGeneral::getClipboard()const
{
	wxString text;

	#if defined(__WXMSW__)
	//buffer ...
	INPUT input[32];
	int iinput = 0;

	//Relacher tout les tocuhes.
	for(int i = 0; i != 0xff; i++)
	{
		if(GetAsyncKeyState(i))
		{
			input[iinput].type = INPUT_KEYBOARD;
			input[iinput].ki.wVk = i;
			input[iinput].ki.wScan = 0;
			input[iinput].ki.dwFlags = KEYEVENTF_KEYUP;//released
			input[iinput].ki.time = 0;
			input[iinput].ki.dwExtraInfo = 0;
			iinput++;
		}
	}
	
	//Presser ctrl
	input[iinput].type = INPUT_KEYBOARD;
	input[iinput].ki.wVk = VK_CONTROL;
	input[iinput].ki.wScan = MapVirtualKey( VK_CONTROL, MAPVK_VK_TO_VSC );
	input[iinput].ki.dwFlags = 0;//pressed
	input[iinput].ki.time = 0;
	input[iinput].ki.dwExtraInfo = 0;
	iinput++;
	
	//Presser 'c'
	input[iinput].type = INPUT_KEYBOARD;
	input[iinput].ki.wVk =  0x43;//C key
	input[iinput].ki.wScan = 0;
	input[iinput].ki.dwFlags = 0;//pressed
	input[iinput].ki.time = 0;
	input[iinput].ki.dwExtraInfo = 0;
	iinput++;
	
	//Relacher 'c'
	input[iinput].type = INPUT_KEYBOARD;
	input[iinput].ki.wVk =  0x43;//C key
	input[iinput].ki.wScan = 0;
	input[iinput].ki.dwFlags = KEYEVENTF_KEYUP;//released
	input[iinput].ki.time = 0;
	input[iinput].ki.dwExtraInfo = 0;
	iinput++;
	
	//Relacher ctrl
	input[iinput].type = INPUT_KEYBOARD;
	input[iinput].ki.wVk = VK_CONTROL;
	input[iinput].ki.wScan = 0;
	input[iinput].ki.dwFlags = KEYEVENTF_KEYUP;//released
	input[iinput].ki.time = 0;
	input[iinput].ki.dwExtraInfo = 0;
	iinput++;
	
	//Simule l'appuie sur ctrl+c
	SendInput(iinput, input, sizeof(INPUT));
	Sleep(50);
	#endif
	
	//Lire le text de la presse papier
	if (wxTheClipboard->Open())
	{
		#if defined(__UNIX__)
		//Lire le text qui ce trouvent dans la presse papier primére.
		wxTheClipboard->UsePrimarySelection(true);
		#endif
		if (wxTheClipboard->IsSupported(wxDF_TEXT))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData( data );
			text = data.GetText();
		}
		wxTheClipboard->Close();
	}
	
	//On enlève les éventuelle retour à la ligne en début et fin du texte.
	text.StartsWith('\n', &text);
	text.EndsWith('\n', &text);
	//On enlève les éventuelle espace en début et fin du texte.
	text.StartsWith(' ', &text);
	text.EndsWith(' ', &text);
	//On enlève les éventuelle (2eme fois) retour à la ligne en début et fin du
	//texte.
	text.StartsWith('\n', &text);
	text.EndsWith('\n', &text);

	return text;
}

void ManGeneral::showTaskIcon(bool show)
{
	if(show)
	{
		if(_taskIcon == nullptr)
			_taskIcon = new TaskIcon();
	}
	else
	{
		if(_taskIcon != nullptr)
			delete _taskIcon;
	}
}

bool ManGeneral::isShowTaskIcon()const
{
	if(_taskIcon != nullptr)
			return true;
			
	return false;
}

//void ManGeneral::launchAtStartup(bool launch)
//{
//}

//bool ManGeneral::isLaunchAtStartup()const
//{
	//return false;
//}

wxIcon const& ManGeneral::getIconApp()const
{
	return _iconApp;
}

wxString const& ManGeneral::getPathIcons()const
{
	return _pathIcons;
}

wxWindow* ManGeneral::newEditWindow(wxWindow* parent)
{
	return nullptr;
}

void ManGeneral::manLoad(wxFileConfig&)
{
	showTaskIcon(true);
}

void ManGeneral::manSave(wxFileConfig&)const
{
}
