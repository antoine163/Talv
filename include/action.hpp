//04.01.2013

#ifndef ACTION_H
#define ACTION_H

#include <wx/string.h>
#include "word.hpp"

class Action
{
	public:				
		Action(wxString const& name = wxEmptyString);
		virtual ~Action();
		
		void setName(wxString const& name);
		wxString const& getName()const;
		
		virtual void execute()=0;
		
		static wxString getClipboard();
	
	private:
		wxString _name;
};

class ActTranslation : public Action
{
	public:				
		ActTranslation(	Word* word = nullptr,
						wxString const& lgsrc = wxEmptyString,
						wxString const& lgto = wxEmptyString);
		~ActTranslation();
		
		void settings(Word* word, wxString const& lgsrc, wxString const& lgto);
		void execute();
		
		wxString const& getLanguageScr()const;
		wxString const& getLanguageTo()const;
	
	private:
		Word* _word;
		wxString _lgsrc;
		wxString _lgto;
};

#if defined(__USE_TTS__)
class ActSay : public Action
{
	public:				
		ActSay(Word* word = nullptr, wxString const& lg = wxEmptyString);
		~ActSay();
		
		void settings(Word* word, wxString const& lg);
		void execute();
		
		wxString const& getLanguage()const;
	
	private:
		Word* _word;
		wxString _lg;
};
#endif

#endif //ACTION_H
