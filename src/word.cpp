//10/12/12

#include "word.hpp"
#if defined(__USE_TTS__)
#include "tts.hpp"
#endif

#include <wx/url.h>
#include <iostream>
#include <wx/protocol/http.h>
#include <wx/sstream.h>

#if defined(__UNIX__)
#include <libnotify/notify.h>
#else
#include <wx/notifmsg.h>
#endif

Word::Word()
{
}

Word::~Word()
{
}

void Word::setWord(const wxString& word, const wxString& lgsrc, const wxString& lgto)
{
	_wordTranslatedProposal.clear();
	_wordTranslated.Clear();
	_word = word;
	_lgsrc = lgsrc;
	_lgto = lgto;

}

void Word::translate()
{
	//Traduction a partir de google
	wxString res = translateFromGoole();
	//Mise en forme du résulta
	if(!res.IsEmpty())
		formatFromGoole(res);
}

void Word::showNotify()
{
	wxString res;
	
	if(_wordTranslated.IsEmpty())
	{
		res << _T("\nSorry no word a translation !");
	}
	else
	{
		res << "\nTranslation : " << _wordTranslated;
		
		if(!_wordTranslatedProposal.empty())
		{
			res << "\n";
			
			std::map<wxString, wxArrayString>::iterator it=_wordTranslatedProposal.end();
			it--;
			std::map<wxString, wxArrayString>::iterator itbegin=_wordTranslatedProposal.begin();
			itbegin--;
			for (;it != itbegin;it--)
			{
				res << "\n- " << it->first;
				
				for (size_t i = 0; i < it->second.GetCount(); i++)
				{
					res << "\n\t" << it->second[i];
				}
			}
		}
	}
	
	#if defined(__WXMSW__) || defined(__WXMAC__)
	wxNotificationMessage notifi(_T("Translate clipboard in french :"), res);
	notifi.Show();
	#elif defined(__UNIX__)
	NotifyNotification * notifi = notify_notification_new("Translate clipboard in french :", res.fn_str(), "dialog-information");
	notify_notification_show(notifi, NULL);
	#endif
}

#if defined(__USE_TTS__)
void Word::say()
{
	if(_word.IsEmpty())
	{
		wxString res;
		res << _T("\nSorry no word a say !");
		
		#if defined(__WXMSW__) || defined(__WXMAC__)
		wxNotificationMessage notifi(_T("Say clipboard :"), res);
		notifi.Show();
		#elif defined(__UNIX__)
		NotifyNotification * notifi = notify_notification_new("Say clipboard :", res.fn_str(), "dialog-information");
		notify_notification_show(notifi, NULL);
		#endif
	}
	else
		new Tts(_lgsrc, _word);
}
#endif

wxString Word::translateFromGoole()const
{
	wxString res;
	
	if(!_word.IsEmpty())
	{
		wxURL url("http://translate.google.com/translate_a/t?client=x&text="+_word+"&hl="+_lgsrc+"&sl="+_lgsrc+"&tl="+_lgto);
		
		if (url.GetError() == wxURL_NOERR)
		{
			//Récupération des données.
			wxInputStream *inStream;
			inStream = url.GetInputStream();
			
			//Si il y à quel que chose à lire
			if(inStream->CanRead())
			{
				int cRead = inStream->GetC();
				while(cRead != wxEOF)
				{
					res << (wxUniChar)cRead;
					cRead = inStream->GetC();
				}
			}
			
			wxDELETE(inStream);
		}
		else
		{
			//err
		}
	}
		
	return res;
}

void Word::formatFromGoole(const wxString& resGoogle)
{	
	bool inSentences = false;
	bool inSentencesTrans = false;
	
	bool inDict = false;
	bool inDictPos = false;
	bool inDictTerms = false;
	
	wxString word;
	wxString proposal;
	unsigned int accolade = 0;
	unsigned int quote = 0;

	for(size_t i = 0; i<resGoogle.Len(); i++)
	{
		if(resGoogle[i] == '{')
			accolade++;
		else if(resGoogle[i] == '}')
			accolade--;
		else if(resGoogle[i] == ':')
		{
			if(!word.IsEmpty())
			{
				if((accolade-1) == 0)
				{
					inSentences = false;
					inDict = false;
					if(word == "sentences")
						inSentences = true;
					else if(word == "dict")
						inDict = true;
				}
				else if((accolade-1) == 1)
				{
					if(inSentences)
					{
						inSentencesTrans = false;
						if(word == "trans")
							inSentencesTrans = true;
					}
					else if(inDict)
					{
						inDictPos = false;
						inDictTerms = false;
						if(word == "pos")
							inDictPos = true;
						else if(word == "terms")
							inDictTerms = true;
					}
				}
			}
		}
		else if(resGoogle[i] == ',')
		{
			if(!word.IsEmpty())
			{
				if(inSentencesTrans)
				{
					//word est la traduction du mot
					_wordTranslated = word;
				}
				else if(inDictPos)
				{
					//word est la proposition
					proposal = word;
					_wordTranslatedProposal[proposal] = wxArrayString();					
				}
				else if(inDictTerms)
				{
					//word est un terme de la proposition
					_wordTranslatedProposal[proposal].Add(word);
				}
			}
		}
		else if(resGoogle[i] == '"')
		{
			if(quote == 0)
			{
				word.Empty();
				quote = 1;
			}
			else
				quote = 0;
		}
		else if(quote == 1)
		{
			word << resGoogle[i];
		}
	}
}

void Word::printWordTranslatedProposal()
{
	std::cout << "Mot original : " << _word << std::endl;
	std::cout << "Traduction : " << _wordTranslated << std::endl;
	
	std::map<wxString, wxArrayString>::iterator it=_wordTranslatedProposal.end();
	it--;
	std::map<wxString, wxArrayString>::iterator itbegin=_wordTranslatedProposal.begin();
	itbegin--;
	for (;it != itbegin;it--)
	{
		std::cout << "- " << it->first << std::endl;
		
		for (size_t i = 0; i < it->second.GetCount(); i++)
		{
			std::cout << "\t" << it->second[i] << std::endl;
		}
	}
}
