//! \file **********************************************************************
//! \brief Header Gestion des traducteurs
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.01.2014
//!
//! ****************************************************************************

#ifndef MAN_TRANSLATOR_H
#define MAN_TRANSLATOR_H

//App
#include "manager.hpp"
#include "translator.hpp"

//Std
#include <vector>
#include <map>

//WxWidgets
#include <wx/language.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/window.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/hyperlink.h>
#include <wx/button.h>

// *****************************************************************************
// Class ManTranslator
// *****************************************************************************

//! \ingroup manager
//! \brief ManTranslator
class ManTranslator : public Manager
{
	DECLARE_MANAGER(ManTranslator);
	
	public:
	
		//! \brief Obtenir la traduction d'un texte.
		//! \param translations variable de retour contenant la traduction du texte.
		//! \param text est le textes à traduire.
		//! \param lgsrc Langue du texte.
		//! \param lgto Langue de traduction.
		//! \return La traduction principale. (elle et aussi présente dans \p translations)
		wxString getTranslations(
						std::map<wxString, wxArrayString>* translations,
						wxString const& text,
						wxLanguage lgsrc,
						wxLanguage lgto);
						
		wxArrayString getOrderTranslators()const;
		void setOrderTranslators(wxArrayString const& names);
		Translator const* getTranslator(wxString const& name)const;
						
		virtual WinManager* newEditWindow(wxWindow* parent);
		
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		std::vector<Translator*> _translators;
};

// *****************************************************************************
// Class WinManTranslator
// *****************************************************************************

//! \brief WinManTranslator
class WinManTranslator : public WinManager
{
	public:
		WinManTranslator(wxWindow* parent);
		~WinManTranslator();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onListBox(wxCommandEvent& event);
		void onButton(wxCommandEvent& event);
		
		void swapInList(unsigned int itemFirst, unsigned int itemSecond);
		void updateButtons();
		
		wxListBox* _listBoxTranslator;
		wxStaticText* _staticTextDescription;
		wxHyperlinkCtrl* _hyperlinkCtrlSee;
		wxButton* _buttonUp;
		wxButton* _buttonDown;
};

#endif //MAN_TRANSLATOR_H
