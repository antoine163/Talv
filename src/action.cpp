//04.01.2013

#include "action.hpp"

#include <wx/clipbrd.h>

Action::Action(wxString const& name) : _name(name)
{
}

Action::~Action()
{
}

wxString Action::getClipboard()
{
	wxString word;
	
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
			word = data.GetText();
		}
		wxTheClipboard->Close();
	}
	
	return word;
}

void Action::setName(wxString const& name)
{
	_name = name;
}

wxString const& Action::getName()const
{
	return _name;
}

ActTranslation::ActTranslation(	Word* word,
								wxString const& lgsrc,
								wxString const& lgto)
: Action("tr"), _word(word), _lgsrc(lgsrc), _lgto(lgto)
{
}

ActTranslation::~ActTranslation()
{
}

void ActTranslation::settings(Word* word, wxString const& lgsrc, wxString const& lgto)
{
	_word = word;
	_lgsrc = lgsrc;
	_lgto = lgto;
}
		
void ActTranslation::execute()
{
	wxString word = getClipboard();
	
	//Suppression des '\n'
	word.Replace("\n", " ");
	
	_word->setWord(word, _lgsrc, _lgto);
	_word->translate();
	_word->showNotify();
}

wxString const& ActTranslation::getLanguageScr()const
{
	return _lgsrc;
}

wxString const& ActTranslation::getLanguageTo()const
{
	return _lgto;
}

#if defined(__USE_TTS__)
ActSay::ActSay(	Word* word,	wxString const& lg)
: Action("ts"), _word(word), _lg(lg)
{
}

ActSay::~ActSay()
{
}

void ActSay::settings(Word* word, wxString const& lg)
{
	_word = word;
	_lg = lg;
}
		
void ActSay::execute()
{
	wxString word = getClipboard();
	
	//Suppression des '\n'
	word.Replace("\n", " ");
	
	_word->setWord(word, _lg);
	_word->say();
}

wxString const& ActSay::getLanguage()const
{
	return _lg;
}
#endif
