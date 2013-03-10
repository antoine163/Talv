//13/12/12

#ifndef WORD_H
#define WORD_H

#include <wx/string.h>
#include <wx/arrstr.h>
#include <map>

class Word
{
	public:
		Word();
		~Word();
		
		void setWord(const wxString& word, const wxString& lgsrc, const wxString& lgto = wxEmptyString);
		void translate();
		void showNotify();
		#if defined(__USE_TTS__)
		void say();
		#endif

	private:
		wxString translateFromGoole()const;
		void formatFromGoole(const wxString& resGoogle);
		
		//Pour les tests
		void printWordTranslatedProposal();
		
		wxString _word;
		wxString _lgsrc;
		wxString _lgto;
		
		wxString _wordTranslated;
		std::map<wxString, wxArrayString> _wordTranslatedProposal;
};

#endif //WORD_H
