//! \file **********************************************************************
//! \brief Source Gestion des traducteurs
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 11.01.2014
//!
//! ****************************************************************************

//App
#include "manager/manTranslator.hpp"
#include "defs.hpp"

//WwWidgets
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/artprov.h>


// *****************************************************************************
// Class ManTranslator
// *****************************************************************************

ManTranslator::ManTranslator()
{
	_translators = Translator::createAllTranslators();
}

ManTranslator::~ManTranslator()
{
	for(auto it: _translators)
		delete it;
}

IMPLEMENT_MANAGER(ManTranslator);

wxString ManTranslator::getTranslations(
						std::map<wxString, wxArrayString>* translations,
						wxString const& text,
						wxLanguage lgsrc,
						wxLanguage lgto)
{	
	return wxEmptyString;
}

wxArrayString ManTranslator::getNamesTranslators()
{
	wxArrayString r;
	for(auto it: _translators)
		r.Add(it->getName());
	return r;
}

WinManager* ManTranslator::newEditWindow(wxWindow* parent)
{
	return new WinManTranslator(parent);
}

void ManTranslator::manLoad(wxFileConfig&)
{
}

void ManTranslator::manSave(wxFileConfig&)const
{
}

// *****************************************************************************
// Class WinManTranslator
// *****************************************************************************

WinManTranslator::WinManTranslator(wxWindow* parent)
: WinManager(parent, _("Translator"))
{
	//Creation de la wxListBox
	wxArrayString namesTranslators = ManTranslator::get().getNamesTranslators();
	_listBoxTranslator = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, namesTranslators.GetCount(), &namesTranslators.Item(0));
	
	//Créations des boutons.
	wxBitmapButton* bitmapButtonUp = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_UP, wxART_BUTTON));
	wxBitmapButton* bitmapButtonDown = new wxBitmapButton(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_BUTTON));
	
	//Mise en for des bouton dans un sizer.
	wxBoxSizer* boxSizerButtons = new wxBoxSizer(wxVERTICAL);
	boxSizerButtons->Add(bitmapButtonUp, 	0, wxBOTTOM, SIZE_BORDER);	
	boxSizerButtons->Add(bitmapButtonDown, 	0);	
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);
	sizerMain->Add(_listBoxTranslator, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(boxSizerButtons, 		0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);
	//sizerMain->Add(_staticBoxNotificationSetting, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(sizerMain);
}

WinManTranslator::~WinManTranslator()
{
}

void WinManTranslator::refreshGuiFromManager()
{
}

void WinManTranslator::refreshManagerFromGui()const
{
}
