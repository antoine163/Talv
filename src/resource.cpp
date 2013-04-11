//! \file **************************************************************
//! \brief Source ressource.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.5
//! \date 30.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "resource.hpp"

#include <wx/jsonreader.h>
#include <wx/clipbrd.h>
#include <wx/intl.h> 
#include <wx/url.h>

//TEST
#include <iostream>

// *********************************************************************
// Class Resource
// *********************************************************************

Resource::Resource()
{
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
	#ifdef USE_ACT_TRANSLATION
	_actions[_("Translation")] = "ActTranslation";
	#endif
	#ifdef USE_ACT_SAVE_TRANSLATION
	_actions[_("Save a translation")] = "ActSaveTranslation";
	#endif
	#ifdef USE_ACT_SAY
	_actions[_("Say a text")] = "ActSay";
	#endif
}

Resource::~Resource()
{
}

std::map<wxString, wxString> const& Resource::getLanguages()const
{
	return _languages;
}

wxString const& Resource::acronymToLanguage(wxString const& acronym)const
{
	return _languages.at(acronym);
}

wxString const& Resource::languageToAcronym(wxString const& language)const
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

wxString const& Resource::typeToAction(wxString const& actTypeName)const
{
	for(auto &it: _actions)
	{
		if(it.second == actTypeName)
			return it.first;
	}
	
	return wxEmptyString;
}

wxString const& Resource::actionsToType(wxString const& actionName)const
{
	return _actions.at(actionName);
}

//! \todo a implémenter pour win
wxString Resource::getClipboard()
{
	wxString text;
	
	//Lire le text ce trouvent dans la presse papier
	if (wxTheClipboard->Open())
	{
		#if defined(__UNIX__)
		wxTheClipboard->UsePrimarySelection(true);
		#endif
		if(wxTheClipboard->IsSupported(wxDF_TEXT))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData(data);
			text = data.GetText();
		}
		wxTheClipboard->Close();
	}
	
	return text;
}

void Resource::getTranslation(	wxString const& text,
								wxString const& lgsrc,
								wxString const& lgto)
{
	////Si il y a un texte à traduire.
	//if(!text.IsEmpty())
	//{
		////Preparation de l'url
		//wxURL url("http://translate.google.com/translate_a/t?ie=UTF-8&client=x&text="+text+"&hl="+lgsrc+"&sl="+lgsrc+"&tl="+lgto);
		
		////Pas d'erreur ?
		//if (url.GetError() == wxURL_NOERR)
		//{
			////Récupération des données.
			//wxInputStream *inStream;
			//inStream = url.GetInputStream();
			
			////Si il y à quel que chose à lire
			//if(inStream->CanRead())
			//{
				////On récupère tout les données.
				//int cRead = inStream->GetC();
				//while(cRead != wxEOF)
				//{
					//jsonText << (wxUniChar)cRead;
					//cRead = inStream->GetC();
				//}
			//}
			
			//wxDELETE(inStream);
		//}
	//}
		
	//std::cout << text << std::endl;
	//std::cout << jsonText << std::endl;
}
