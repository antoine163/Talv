//! \file **************************************************************
//! \brief Source ressource.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.20
//! \date 30.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "resource.hpp"

#include <wx/jsonval.h>
#include <wx/jsonreader.h>

#include <wx/clipbrd.h>
#include <wx/sstream.h>
#include <wx/intl.h> 
#include <wx/url.h>
#include <wx/log.h>

#if defined(__WXMSW__)
#include <windows.h>
#endif

//TEST
#include <iostream>

// *********************************************************************
// Class Resource
// *********************************************************************

Resource::Resource()
{
	#if defined(__UNIX__)
	#elif defined(__WXMSW__)
	#endif
	
	//Le menu doit être afficher (par défaut)
	_showMenu = true;
	
	//Volume 100%
	_ttsVolume = 1.0;
	
	//Par défaut on ne démarre pas l'application au démarrage.
	_powerOn = false;
	
	//Liste des langues
	_languages["af"] = _("Afrikaans");
	_languages["sq"] = _("Albanian");
	_languages["ar"] = _("Arabic");
	_languages["hy"] = _("Armenian");
	_languages["az"] = _("Azerbaijani");
	_languages["eu"] = _("Basque");
	_languages["be"] = _("Belarusian");
	_languages["bn"] = _("Bengali");
	_languages["bg"] = _("Bulgarian");
	_languages["ca"] = _("Catalan");
	_languages["zh-CN"] = _("Chinese");
	_languages["hr"] = _("Croatian");
	_languages["sr"] = _("Czech");
	_languages["da"] = _("Danish");
	_languages["nl"] = _("Dutch");
	_languages["en"] = _("English");
	_languages["eo"] = _("Esperanto");
	_languages["et"] = _("Estonian");
	_languages["tl"] = _("Filipino");
	_languages["fi"] = _("Finnish");
	_languages["fr"] = _("French");
	_languages["gl"] = _("Galician");
	_languages["ka"] = _("Georgian");
	_languages["de"] = _("German");
	_languages["el"] = _("Greek");
	_languages["gu"] = _("Gujarati");
	_languages["ht"] = _("Haitian Creole");
	_languages["iw"] = _("Hebrew");
	_languages["hi"] = _("Hindi");
	_languages["hu"] = _("Hungarian");
	_languages["is"] = _("Icelandic");
	_languages["id"] = _("Indonesian");
	_languages["ga"] = _("Irish");
	_languages["it"] = _("Italian");
	_languages["ja"] = _("Japanese");
	_languages["kn"] = _("Kannada");
	_languages["ko"] = _("Korean");
	_languages["lo"] = _("Lao");
	_languages["la"] = _("Latin");
	_languages["lv"] = _("Latvian");
	_languages["it"] = _("Lithuanian");
	_languages["mk"] = _("Macedonian");
	_languages["ms"] = _("Malay");
	_languages["mt"] = _("Maltese");
	_languages["no"] = _("Norwegian");
	_languages["fa"] = _("Persian");
	_languages["pl"] = _("Polish");
	_languages["pt"] = _("Portuguese");
	_languages["ro"] = _("Romanian");
	_languages["ru"] = _("Russian");
	_languages["sr"] = _("Serbian");
	_languages["sk"] = _("Slovak");
	_languages["sl"] = _("Slovenian");
	_languages["es"] = _("Spanish");
	_languages["sw"] = _("Swahili");
	_languages["sv"] = _("Swedish");
	_languages["ta"] = _("Tamil");
	_languages["te"] = _("Telugu");
	_languages["th"] = _("Thai");
	_languages["tr"] = _("Turkish");
	_languages["uk"] = _("Ukrainian");
	_languages["ur"] = _("Urdu");
	_languages["vi"] = _("Vietnamese");
	_languages["cy"] = _("Welsh");
	_languages["yi"] = _("Yiddish");
	
	
	//Liste des actions
	_actions[_("Translation")] = "ActTranslation";
	_actions[_("Translation to list")] = "ActTranslationToList";
	_actions[_("Learn a list")] = "ActLearn";
}

Resource::~Resource()
{
	#if defined(__UNIX__)
	#elif defined(__WXMSW__)
	#endif
}

std::map<wxString, wxString> const& Resource::getLanguages()const
{
	return _languages;
}

wxString Resource::abbreviationToLanguage(wxString const& abbreviation)const
{
	return _languages.at(abbreviation);
}

wxString Resource::languageToAbbreviation(wxString const& language)const
{
	for(auto &it: _languages)
	{
		if(it.second == language)
			return it.first;
	}
	
	return wxEmptyString;
}

std::map<wxString, wxString> const& Resource::getActions()const
{
	return _actions;
}

wxString Resource::typeToAction(wxString const& actTypeName)const
{
	for(auto &it: _actions)
	{
		if(it.second == actTypeName)
			return it.first;
	}
	
	return wxEmptyString;
}

wxString Resource::actionsToType(wxString const& actionName)const
{
	return _actions.at(actionName);
}

wxString Resource::getClipboard() 
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
	//On enlève les éventuelle (2eme fois) retour à la ligne en début et fin du texte.
	text.StartsWith('\n', &text);
	text.EndsWith('\n', &text);

	return text;
}

wxString Resource::getTranslations(
						std::map<wxString, wxArrayString>* translations,
						wxString const& text,
						wxString const& lgsrc,
						wxString const& lgto)
{	
	//Représentent la traduction au forma json
	wxString jsonText;
		
	//Si il y a un texte à traduire.
	if(!text.IsEmpty())
	{	
		//Télécharger la raiponce de google
		wxMemoryBuffer buffer;
		if(!Resource::getInstance()->downloadFromUrl(&buffer,"http://translate.google.com/translate_a/t?ie=UTF-8&oe=UTF-8&client=x&text="+text+"&hl="+lgto+"&sl="+lgsrc+"&tl="+lgto))
			return wxEmptyString;
		//ajouter au jsonText
		jsonText.Append(wxString::FromUTF8((const char *)buffer.GetData(), buffer.GetDataLen()));
	}
	else
		return wxEmptyString;
			
	//Variable qui va contenir la traduction.
	wxString trans;

	//Variable pour la lecture du JSON
	wxJSONValue root;
	wxJSONReader reader;
	
	//Lecture du JSON
	reader.Parse(jsonText, &root);
	
	//Récupère la phrase.
	wxJSONValue& sentences = root["sentences"];
	
	//Récupère la traduction (principale).
	for(int i = 0; i < sentences.Size(); i++)
		trans << sentences[i]["trans"].AsString();
		
	//Récupère le dictionnaire (Les autres traductions).
	wxJSONValue& dict = root["dict"];
	
	for(int i = 0; i < dict.Size(); i++)
	{
		wxString pos = dict[i]["pos"].AsString();
		wxJSONValue& terms = dict[i]["terms"];
		
		for(int i = 0; i < terms.Size(); i++)
		{
			(*translations)[pos].Add(terms[i].AsString());
		}
	}

	return trans;
}

bool Resource::downloadFromUrl(wxMemoryBuffer* buffer, wxString const& sUrl)
{
	wxURL url(sUrl);
	
	//Erreur ?
	if (url.GetError() == wxURL_NOERR)
	{	
		//Récupération des données.
		wxInputStream *urlStream = url.GetInputStream();
		
		if(!urlStream)
			return false;

		//Erreur ?
		if(urlStream->IsOk())
		{			
			//data temporaire.
			uint8_t tmpData[1024];
			
			//Lie des données temps qu'il y en a.
			while(urlStream->CanRead() && !urlStream->Eof())
			{
				urlStream->Read(tmpData, 1024);
				buffer->AppendData(tmpData, urlStream->LastRead());
			}
		}
		delete urlStream;
	}
	
	return true;
}

void Resource::setShowMenu(bool showMenu)
{
	_showMenu = showMenu;
}

bool Resource::getShowMenu()
{
	return _showMenu;
}

//! \todo a compléter pour réellement le prendre en compte coter os.
void Resource::setPowerOn(bool powerOn)
{
	_powerOn = powerOn;
}

bool Resource::getPowerOn()
{
	return _powerOn;
}

void Resource::load(wxFileConfig& fileConfig)
{
	fileConfig.Read("show_menu", &_showMenu);
	fileConfig.Read("power_on", &_powerOn);
}

void Resource::save(wxFileConfig& fileConfig)const
{
	fileConfig.Write("show_menu", _showMenu);
	fileConfig.Write("power_on", _powerOn);
}
