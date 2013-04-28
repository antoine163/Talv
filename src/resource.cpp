//! \file **************************************************************
//! \brief Source ressource.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.13
//! \date 30.03.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "resource.hpp"

#include <wx/clipbrd.h>
#include <wx/sstream.h>
#include <wx/intl.h> 
#include <wx/url.h>
#include <wx/log.h> 

//TEST
#include <iostream>

// *********************************************************************
// Class Resource
// *********************************************************************

Resource::Resource()
{
	#if defined(__UNIX__)
		//Initialisation de GStreamer.
		gst_init(nullptr, nullptr);
		_pipeline = nullptr;
	#elif defined(__WXMSW__)
	#endif
	
	//Le menu doit être afficher (par défaut)
	_showMenu = true;
	
	//Volume 100%
	_ttsVolume = 1.0;
	
	
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
	#if defined(__UNIX__)
		//Libération des ressources de GStreamer.
		if (_pipeline != NULL)
		{
			gst_object_unref(_pipeline);
		}
		gst_deinit();
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

//! \todo Vois pour une implémentation avec un analyser jSON
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
		Resource::getInstance()->downloadFromUrl(&buffer, "http://translate.google.com/translate_a/t?ie=UTF-8&oe=UTF-8&client=x&text="+text+"&hl="+lgto+"&sl="+lgsrc+"&tl="+lgto);
		//l'ajouter au jsonText
		jsonText.Append((const char *)buffer.GetData(), buffer.GetDataLen());
	}
	else
		return wxEmptyString;
		
	//Analyser du forma jSON provenant de google (Code fonctionnelle ...)
	wxString mainTranslate;
	bool inSentences = false;
	bool inSentencesTrans = false;
	
	bool inDict = false;
	bool inDictPos = false;
	bool inDictTerms = false;
	
	wxString parseText;
	wxString proposal;
	unsigned int accolade = 0;
	unsigned int quote = 0;

	for(size_t i = 0; i<jsonText.Len(); i++)
	{
		if(jsonText[i] == '{')
			accolade++;
		else if(jsonText[i] == '}')
			accolade--;
		else if(jsonText[i] == ':')
		{
			if(!parseText.IsEmpty())
			{
				if((accolade-1) == 0)
				{
					inSentences = false;
					inDict = false;
					if(parseText == "sentences")
						inSentences = true;
					else if(parseText == "dict")
						inDict = true;
				}
				else if((accolade-1) == 1)
				{
					if(inSentences)
					{
						inSentencesTrans = false;
						if(parseText == "trans")
							inSentencesTrans = true;
					}
					else if(inDict)
					{
						inDictPos = false;
						inDictTerms = false;
						if(parseText == "pos")
							inDictPos = true;
						else if(parseText == "terms")
							inDictTerms = true;
					}
				}
			}
		}
		else if(jsonText[i] == ',')
		{
			if(!parseText.IsEmpty())
			{
				if(inSentencesTrans)
				{
					//ici parseText est la traduction du text
					mainTranslate = parseText;
				}
				else if(inDictPos)
				{
					//ici parseText est la proposition
					proposal = parseText;
					(*translations)[proposal] = wxArrayString();					
				}
				else if(inDictTerms)
				{
					//ici parseText est un terme de la proposition
					(*translations)[proposal].Add(parseText);
				}
			}
		}
		else if(jsonText[i] == '"')
		{
			if(quote == 0)
			{
				parseText.Empty();
				quote = 1;
			}
			else
				quote = 0;
		}
		else if(quote == 1)
		{
			parseText << jsonText[i];
		}
	}
	
	return mainTranslate;
}

void Resource::downloadFromUrl(wxMemoryBuffer* buffer, wxString const& sUrl)
{
	wxURL url(sUrl);
	
	//Erreur ?
	if (url.GetError() == wxURL_NOERR)
	{	
		//Récupération des données.
		wxInputStream *urlStream = url.GetInputStream();
		
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
}

void Resource::Tts(wxString const& text, wxString const& lg)
{		
	//Construction de la pipeline
	wxString stringPipeline;
	stringPipeline << "playbin uri=\"http://translate.google.com/translate_tts?ie=UTF-8&tl="+lg+"&q="+text+"\" volume=" << _ttsVolume;
	_pipeline = gst_parse_launch(stringPipeline.fn_str(), nullptr);
	
	//pipeline n'est pas ok ?
	if(_pipeline == nullptr)
	{
		wxLogError(_("Could not build pipeling for GStreamer."));
		return;
	}
	
	//Début la lecture.
	gst_element_set_state(_pipeline, GST_STATE_PLAYING);
}

void Resource::setShowMenu(bool showMenu)
{
	_showMenu = showMenu;
}

bool Resource::getShowMenu()
{
	return _showMenu;
}

// \todo a compléter pour réellement le prendre en compte coter os.
void Resource::setPowerOn(bool powerOn)
{
	_powerOn = powerOn;
}

bool Resource::getPowerOn()
{
	return _powerOn;
}

void Resource::setTtsVolume(double volume)
{
	_ttsVolume = volume;
}

double Resource::getTtsVolume()
{
	return _ttsVolume;
}

void Resource::load(wxFileConfig& fileConfig)
{
	fileConfig.Read("show_menu", &_showMenu);
	fileConfig.Read("power_on", &_powerOn);
	fileConfig.Read("tts_volume", &_ttsVolume);
}

void Resource::save(wxFileConfig& fileConfig)const
{
	fileConfig.Write("show_menu", _showMenu);
	fileConfig.Write("power_on", _powerOn);
	fileConfig.Write("tts_volume", _ttsVolume);
}
