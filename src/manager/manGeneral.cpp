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
#include <wx/sizer.h>
#include <wx/intl.h>

//Os
#if defined(__WXMSW__)
#include <windows.h>
#endif

// *****************************************************************************
// Class ManGeneral
// *****************************************************************************

ManGeneral::ManGeneral() : _taskIcon(nullptr)
{
}

ManGeneral::~ManGeneral()
{
	if(_taskIcon != nullptr)
		delete _taskIcon;
}

IMPLEMENT_MANAGER(ManGeneral);

wxArrayString ManGeneral::getLanguages()const
{
	wxArrayString languages;
	languages.Alloc(146);

	languages.Add(_("Abkhazian"));
	languages.Add(_("Afar"));
	languages.Add(_("Afrikaans"));
	languages.Add(_("Albanian"));
	languages.Add(_("Amharic"));
	languages.Add(_("Arabic"));
	languages.Add(_("Armenian"));
	languages.Add(_("Assamese"));
	languages.Add(_("Asturian"));
	languages.Add(_("Aymara"));
	languages.Add(_("Azeri"));
	languages.Add(_("Bashkir"));
	languages.Add(_("Basque"));
	languages.Add(_("Belarusian"));
	languages.Add(_("Bengali"));
	languages.Add(_("Bhutani"));
	languages.Add(_("Bihari"));
	languages.Add(_("Bislama"));
	languages.Add(_("Bosnian"));
	languages.Add(_("Breton"));
	languages.Add(_("Bulgarian"));
	languages.Add(_("Burmese"));
	languages.Add(_("Cambodian"));
	languages.Add(_("Catalan"));
	languages.Add(_("Chinese"));
	languages.Add(_("Corsican"));
	languages.Add(_("Croatian"));
	languages.Add(_("Czech"));
	languages.Add(_("Danish"));
	languages.Add(_("Dutch"));
	languages.Add(_("English"));
	languages.Add(_("Esperanto"));
	languages.Add(_("Estonian"));
	languages.Add(_("Faeroese"));
	languages.Add(_("Farsi"));
	languages.Add(_("Fiji"));
	languages.Add(_("Finnish"));
	languages.Add(_("French"));
	languages.Add(_("Frisian"));
	languages.Add(_("Galician"));
	languages.Add(_("Georgian"));
	languages.Add(_("German"));
	languages.Add(_("Greek"));
	languages.Add(_("Greenlandic"));
	languages.Add(_("Guarani"));
	languages.Add(_("Gujarati"));
	languages.Add(_("Hausa"));
	languages.Add(_("Hebrew"));
	languages.Add(_("Hindi"));
	languages.Add(_("Hungarian"));
	languages.Add(_("Icelandic"));
	languages.Add(_("Indonesian"));
	languages.Add(_("Interlingua"));
	languages.Add(_("Interlingue"));
	languages.Add(_("Inuktitut"));
	languages.Add(_("Inupiak"));
	languages.Add(_("Irish"));
	languages.Add(_("Italian"));
	languages.Add(_("Japanese"));
	languages.Add(_("Javanese"));
	languages.Add(_("Kannada"));
	languages.Add(_("Kashmiri"));
	languages.Add(_("Kazakh"));
	languages.Add(_("Kernewek"));
	languages.Add(_("Kinyarwanda"));
	languages.Add(_("Kirghiz"));
	languages.Add(_("Kirundi"));
	languages.Add(_("Konkani"));
	languages.Add(_("Korean"));
	languages.Add(_("Kurdish"));
	languages.Add(_("Laothian"));
	languages.Add(_("Latin"));
	languages.Add(_("Latvian"));
	languages.Add(_("Lingala"));
	languages.Add(_("Lithuanian"));
	languages.Add(_("Macedonian"));
	languages.Add(_("Malagasy"));
	languages.Add(_("Malay"));
	languages.Add(_("Malayalam"));
	languages.Add(_("Maltese"));
	languages.Add(_("Manipuri"));
	languages.Add(_("Maori"));
	languages.Add(_("Marathi"));
	languages.Add(_("Moldavian"));
	languages.Add(_("Mongolian"));
	languages.Add(_("Nauru"));
	languages.Add(_("Nepali"));
	languages.Add(_("Northern Sami"));
	languages.Add(_("Norwegian"));
	languages.Add(_("Occitan"));
	languages.Add(_("Oriya"));
	languages.Add(_("Pashto, Pushto"));
	languages.Add(_("Polish"));
	languages.Add(_("Portuguese"));
	languages.Add(_("Punjabi"));
	languages.Add(_("Quechua"));
	languages.Add(_("Rhaeto-Romance"));
	languages.Add(_("Romanian"));
	languages.Add(_("Russian"));
	languages.Add(_("Samoan"));
	languages.Add(_("Sangho"));
	languages.Add(_("Sanskrit"));
	languages.Add(_("Scots Gaelic"));
	languages.Add(_("Serbian"));
	languages.Add(_("Serbo-Croatian"));
	languages.Add(_("Sesotho"));
	languages.Add(_("Setswana"));
	languages.Add(_("Shona"));
	languages.Add(_("Sindhi"));
	languages.Add(_("Sinhalese"));
	languages.Add(_("Siswati"));
	languages.Add(_("Slovak"));
	languages.Add(_("Slovenian"));
	languages.Add(_("Somali"));
	languages.Add(_("Spanish"));
	languages.Add(_("Sundanese"));
	languages.Add(_("Swahili"));
	languages.Add(_("Swedish"));
	languages.Add(_("Tagalog"));
	languages.Add(_("Tajik"));
	languages.Add(_("Tamil"));
	languages.Add(_("Tatar"));
	languages.Add(_("Telugu"));
	languages.Add(_("Thai"));
	languages.Add(_("Tibetan"));
	languages.Add(_("Tigrinya"));
	languages.Add(_("Tonga"));
	languages.Add(_("Tsonga"));
	languages.Add(_("Turkish"));
	languages.Add(_("Turkmen"));
	languages.Add(_("Twi"));
	languages.Add(_("Uighur"));
	languages.Add(_("Ukrainian"));
	languages.Add(_("Urdu"));
	languages.Add(_("Uzbek"));
	languages.Add(_("Valencian"));
	languages.Add(_("Vietnamese"));
	languages.Add(_("Volapuk"));
	languages.Add(_("Welsh"));
	languages.Add(_("Wolof"));
	languages.Add(_("Xhosa"));
	languages.Add(_("Yiddish"));
	languages.Add(_("Yoruba"));
	languages.Add(_("Zhuang"));
	languages.Add(_("Zulu"));

	return languages;
}

wxLanguage ManGeneral::getSystemLanguage()const
{
	wxLanguage lg = (wxLanguage)wxLocale::GetSystemLanguage();
	if(	lg == wxLANGUAGE_ARABIC ||
		lg == wxLANGUAGE_ARABIC_ALGERIA ||
		lg == wxLANGUAGE_ARABIC_BAHRAIN ||
		lg == wxLANGUAGE_ARABIC_EGYPT ||
		lg == wxLANGUAGE_ARABIC_IRAQ ||
		lg == wxLANGUAGE_ARABIC_JORDAN ||
		lg == wxLANGUAGE_ARABIC_KUWAIT ||
		lg == wxLANGUAGE_ARABIC_LEBANON ||
		lg == wxLANGUAGE_ARABIC_LIBYA ||
		lg == wxLANGUAGE_ARABIC_MOROCCO ||
		lg == wxLANGUAGE_ARABIC_OMAN ||
		lg == wxLANGUAGE_ARABIC_QATAR ||
		lg == wxLANGUAGE_ARABIC_SAUDI_ARABIA ||
		lg == wxLANGUAGE_ARABIC_SUDAN ||
		lg == wxLANGUAGE_ARABIC_SYRIA ||
		lg == wxLANGUAGE_ARABIC_TUNISIA ||
		lg == wxLANGUAGE_ARABIC_UAE ||
		lg == wxLANGUAGE_ARABIC_YEMEN)
		return wxLANGUAGE_ARABIC;
	if(	lg == wxLANGUAGE_AZERI ||
		lg == wxLANGUAGE_AZERI_CYRILLIC ||
		lg == wxLANGUAGE_AZERI_LATIN)
		return wxLANGUAGE_AZERI;
	if(	lg == wxLANGUAGE_CHINESE ||
		lg == wxLANGUAGE_CHINESE_SIMPLIFIED ||
		lg == wxLANGUAGE_CHINESE_TRADITIONAL ||
		lg == wxLANGUAGE_CHINESE_HONGKONG ||
		lg == wxLANGUAGE_CHINESE_MACAU ||
		lg == wxLANGUAGE_CHINESE_SINGAPORE ||
		lg == wxLANGUAGE_CHINESE_TAIWAN)
		return wxLANGUAGE_CHINESE;
	if(	lg == wxLANGUAGE_DUTCH ||
		lg == wxLANGUAGE_DUTCH_BELGIAN)
		return wxLANGUAGE_DUTCH;
	if(	lg == wxLANGUAGE_ENGLISH ||
		lg == wxLANGUAGE_ENGLISH_UK ||
		lg == wxLANGUAGE_ENGLISH_US ||
		lg == wxLANGUAGE_ENGLISH_AUSTRALIA ||
		lg == wxLANGUAGE_ENGLISH_BELIZE ||
		lg == wxLANGUAGE_ENGLISH_BOTSWANA ||
		lg == wxLANGUAGE_ENGLISH_CANADA ||
		lg == wxLANGUAGE_ENGLISH_CARIBBEAN ||
		lg == wxLANGUAGE_ENGLISH_DENMARK ||
		lg == wxLANGUAGE_ENGLISH_EIRE ||
		lg == wxLANGUAGE_ENGLISH_JAMAICA ||
		lg == wxLANGUAGE_ENGLISH_NEW_ZEALAND ||
		lg == wxLANGUAGE_ENGLISH_PHILIPPINES ||
		lg == wxLANGUAGE_ENGLISH_SOUTH_AFRICA ||
		lg == wxLANGUAGE_ENGLISH_TRINIDAD ||
		lg == wxLANGUAGE_ENGLISH_ZIMBABWE)
		return wxLANGUAGE_ENGLISH;
	if(	lg == wxLANGUAGE_FRENCH ||
		lg == wxLANGUAGE_FRENCH_BELGIAN ||
		lg == wxLANGUAGE_FRENCH_CANADIAN ||
		lg == wxLANGUAGE_FRENCH_LUXEMBOURG ||
		lg == wxLANGUAGE_FRENCH_MONACO ||
		lg == wxLANGUAGE_FRENCH_SWISS)
		return wxLANGUAGE_FRENCH;
	if(	lg == wxLANGUAGE_GERMAN ||
		lg == wxLANGUAGE_GERMAN_AUSTRIAN ||
		lg == wxLANGUAGE_GERMAN_BELGIUM ||
		lg == wxLANGUAGE_GERMAN_LIECHTENSTEIN ||
		lg == wxLANGUAGE_GERMAN_LUXEMBOURG ||
		lg == wxLANGUAGE_GERMAN_SWISS)
		return wxLANGUAGE_GERMAN;
	if(	lg == wxLANGUAGE_ITALIAN ||
		lg == wxLANGUAGE_ITALIAN_SWISS)
		return wxLANGUAGE_ITALIAN;
	if(	lg == wxLANGUAGE_KASHMIRI ||
		lg == wxLANGUAGE_KASHMIRI_INDIA)
		return wxLANGUAGE_KASHMIRI;
	if(	lg == wxLANGUAGE_MALAY ||
		lg == wxLANGUAGE_MALAY_BRUNEI_DARUSSALAM ||
		lg == wxLANGUAGE_MALAY_MALAYSIA)
		return wxLANGUAGE_MALAY;
	if(	lg == wxLANGUAGE_NEPALI ||
		lg == wxLANGUAGE_NEPALI_INDIA)
		return wxLANGUAGE_NEPALI;
	if(	lg == wxLANGUAGE_NORWEGIAN_BOKMAL ||
		lg == wxLANGUAGE_NORWEGIAN_NYNORSK)
		return wxLANGUAGE_NORWEGIAN_BOKMAL;
	if(	lg == wxLANGUAGE_PORTUGUESE ||
		lg == wxLANGUAGE_PORTUGUESE_BRAZILIAN)
		return wxLANGUAGE_PORTUGUESE;
	if(	lg == wxLANGUAGE_RUSSIAN ||
		lg == wxLANGUAGE_RUSSIAN_UKRAINE)
		return wxLANGUAGE_RUSSIAN;
	if(	lg == wxLANGUAGE_SERBIAN ||
		lg == wxLANGUAGE_SERBIAN_CYRILLIC ||
		lg == wxLANGUAGE_SERBIAN_LATIN ||
		lg == wxLANGUAGE_SERBIAN_CYRILLIC ||
		lg == wxLANGUAGE_SERBIAN_LATIN)
		return wxLANGUAGE_SERBIAN;
	if(	lg == wxLANGUAGE_SPANISH ||
		lg == wxLANGUAGE_SPANISH_ARGENTINA ||
		lg == wxLANGUAGE_SPANISH_BOLIVIA ||
		lg == wxLANGUAGE_SPANISH_CHILE ||
		lg == wxLANGUAGE_SPANISH_COLOMBIA ||
		lg == wxLANGUAGE_SPANISH_COSTA_RICA ||
		lg == wxLANGUAGE_SPANISH_DOMINICAN_REPUBLIC ||
		lg == wxLANGUAGE_SPANISH_ECUADOR ||
		lg == wxLANGUAGE_SPANISH_EL_SALVADOR ||
		lg == wxLANGUAGE_SPANISH_GUATEMALA ||
		lg == wxLANGUAGE_SPANISH_HONDURAS ||
		lg == wxLANGUAGE_SPANISH_MEXICAN ||
		lg == wxLANGUAGE_SPANISH_MODERN ||
		lg == wxLANGUAGE_SPANISH_NICARAGUA ||
		lg == wxLANGUAGE_SPANISH_PANAMA ||
		lg == wxLANGUAGE_SPANISH_PARAGUAY ||
		lg == wxLANGUAGE_SPANISH_PERU ||
		lg == wxLANGUAGE_SPANISH_PUERTO_RICO ||
		lg == wxLANGUAGE_SPANISH_URUGUAY ||
		lg == wxLANGUAGE_SPANISH_US ||
		lg == wxLANGUAGE_SPANISH_VENEZUELA)
		return wxLANGUAGE_SPANISH;
	if(	lg == wxLANGUAGE_SWEDISH ||
		lg == wxLANGUAGE_SWEDISH_FINLAND)
		return wxLANGUAGE_SWEDISH;
	if(	lg == wxLANGUAGE_URDU ||
		lg == wxLANGUAGE_URDU_INDIA ||
		lg == wxLANGUAGE_URDU_PAKISTAN)
		return wxLANGUAGE_URDU;
	if(	lg == wxLANGUAGE_UZBEK ||
		lg == wxLANGUAGE_UZBEK_CYRILLIC ||
		lg == wxLANGUAGE_UZBEK_LATIN)
		return wxLANGUAGE_UZBEK;
	return lg;
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
		{
			//_taskIcon->Destroy();
			delete _taskIcon;
			_taskIcon = nullptr;
		}
	}
}

bool ManGeneral::isShowTaskIcon()const
{
	if(_taskIcon != nullptr)
			return true;
			
	return false;
}

void ManGeneral::enableTaskIcon(bool enable)
{
	if(_taskIcon != nullptr)
			_taskIcon->enable(enable);
}

//void ManGeneral::launchAtStartup(bool launch)
//{
//}

//bool ManGeneral::isLaunchAtStartup()const
//{
	//return false;
//}

wxIcon ManGeneral::getIconApp(IconSize_e size)const
{
	//Chargement de l'icône de l'application.
	wxString nameIcon = PROJECT_NAME;
	nameIcon.MakeLower();
	return wxIcon(	getPathIcons(size)+'/'+nameIcon+".png",
					wxBITMAP_TYPE_PNG);
}

wxString ManGeneral::getPathIcons()const
{
	//Détermination du pach ou se trouve les icônes.
	#if defined(__UNIX__) //ET Mac ?
	wxString _pathIcons;
	if(_pathIcons.IsEmpty())
	{
		_pathIcons = "./icons";
		if(!wxDirExists(_pathIcons))
			_pathIcons = wxStandardPaths::Get().GetDataDir()+"/icons";
	}
	#else
	wxString _pathIcons = "./icons";
	#endif
	
	return _pathIcons;
}

wxString ManGeneral::getPathIcons(IconSize_e size)const
{
	wxString path = getPathIcons();
	
	switch(size)
	{
		case ICON_SIZE_16X16:
			path << "/16x16";
		break;
		
		case ICON_SIZE_32X32:
			path << "/32x32";
		break;
	}
	
	return path;
}

WinManager* ManGeneral::newEditWindow(wxWindow* parent)
{
	//wxWindow* tmp = new WinManager(	parent,
									//wxID_ANY,
									//wxDefaultPosition,
									//wxDefaultSize,
									//0,
									//_("General"));
	//return tmp;
	return nullptr;
}

void ManGeneral::manLoad(wxFileConfig&)
{
	showTaskIcon(true);
}

void ManGeneral::manSave(wxFileConfig&)const
{
}
