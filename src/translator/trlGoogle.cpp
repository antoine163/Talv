//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 12.01.2014
//!
//! ***************************************************************************

//App
#include "translator/trlGoogle.hpp"
#include "manager/manNetwork.hpp"

//WxJson
#include <wx/jsonval.h>
#include <wx/jsonreader.h>

//WxWidgets
#include <wx/intl.h> 

// *****************************************************************************
// Class TrlGoogle
// *****************************************************************************

TrlGoogle::TrlGoogle()
{
}

TrlGoogle::~TrlGoogle()
{
}

IMPLEMENT_TRANSLATOR(TrlGoogle, _("Google"), _("Translation a text from \"Google Translate.\""), "http://translate.google.com/");

void TrlGoogle::getTranslations(	DataText* translations,
									wxString const& text,
									wxLanguage lgsrc,
									wxLanguage lgto)
{	
	//Représentent la traduction au forma json
	wxString jsonText;
	
	//Construction de l'url
	wxString url;
	url << "http://translate.google.com/translate_a/t?ie=UTF-8&oe=UTF-8&client=x";
	url << "&text=" << text;
	url << "&hl=" << wxLocale::GetLanguageCanonicalName(lgto);
	url << "&sl=" << wxLocale::GetLanguageCanonicalName(lgsrc);
	url << "&tl=" << wxLocale::GetLanguageCanonicalName(lgto);
	
	//On récupère la réponse de google.
	wxString json;
	if(ManNetwork::get().downloadFromUrlToString(url, &json) != wxURL_NOERR)
		return;

	//Variable pour la lecture du JSON
	wxJSONValue root;
	wxJSONReader reader;
	
	//Lecture du JSON
	reader.Parse(json, &root);
	
	//Récupère la phrase.
	wxJSONValue& sentences = root["sentences"];
	
	//Récupère la traduction (principale).
	for(int i = 0; i < sentences.Size(); i++)
		translations->setMainTranslation(sentences[i]["trans"].AsString());
		
	//Récupère le dictionnaire (Les autres traductions).
	wxJSONValue& dict = root["dict"];
	
	for(int i = 0; i < dict.Size(); i++)
	{
		wxString pos = dict[i]["pos"].AsString();
		wxJSONValue& terms = dict[i]["terms"];
		
		for(int i = 0; i < terms.Size(); i++)
			translations->addTranslation(pos, terms[i].AsString());
	}
}

