//22/12/12

#ifndef TTS_H
#define TTS_H

#include <wx/thread.h>
#include <wx/string.h>

class Tts : public wxThread
{
	public:
		Tts(wxString& lg, wxString& msg);
		~Tts();
		
	protected:
		wxThread::ExitCode Entry();

	private:
		wxString& _lg;
		wxString& _msg;
};

#endif //TTS_H
