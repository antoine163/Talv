//! \file **********************************************************************
//! \brief Header Gestion de tts (text to speech)
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.12.2013
//!
//! ****************************************************************************

#ifndef MAN_TTS_H
#define MAN_TTS_H

//App
#include "manager.hpp"

// *****************************************************************************
// Class ManTts
// *****************************************************************************

//! \ingroup manager
//! \brief ManTts
class ManTts : public Manager
{
	DECLARE_MANAGER(ManTts);
	
	public:
		virtual wxWindow* newEditWindow(wxWindow* parent);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
};

#endif //MAN_TTS_H
