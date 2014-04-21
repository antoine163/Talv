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
#include "manager/manCache.hpp"
#include "cache.hpp"
#include "defs.hpp"
#include "staticBox.hpp"

//WwWidgets
#include <wx/sizer.h>
#include <wx/language.h>
#include <wx/log.h> 

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

void ManTranslator::getTranslations(	DataText* translations,
										wxString const& text,
										wxLanguage lgsrc,
										wxLanguage lgto)
{	
	if(text.IsEmpty())
	{
		wxLogMessage("No text at tranlate.");
		return;
	}
	
	translations->clear();
	for(auto it: _translators)
	{
		it->getTranslations(translations, text, lgsrc, lgto);
		if(translations->getMainTranslation().IsEmpty())
			wxLogMessage("The %s text could not be translate to %s from the translator: %s",
						wxLocale::GetLanguageName(lgsrc), wxLocale::GetLanguageName(lgto), it->getName());
		else
		{
			if(text.Len() <= NB_CHARACTER_MIN_FOR_SENTENCE)
			{
				//Si le cache n'existe pas on le crée.
				if(!ManCache::get().existCache(lgsrc, lgto))
					ManCache::get().createCache(lgsrc, lgto);
					
				//Ajout de la traduction du texte dans le cache.
				Cache tmpCache = ManCache::get().getCache(lgsrc, lgto);
				tmpCache.addText(text, *translations);
			}
			
			return;
		}
	}
}

wxArrayString ManTranslator::getOrderTranslators()const
{
	wxArrayString r;
	for(auto it: _translators)
		r.Add(it->getName());
	return r;
}

void ManTranslator::setOrderTranslators(wxArrayString const& names)
{
	//Pour chaque non de traducteur
	for(size_t iName = 0; iName < names.GetCount(); iName++)
	{
		//On cherche le traducteur dans le vector.
		for(size_t iSearch = iName; iSearch < _translators.size(); iSearch++)
		{
			//Si on l'a trouver on swape les deux pointeur.
			if(names[iName] == _translators[iSearch]->getName())
			{
				//On swap si ce n'est pas les même id.
				if(iName != iSearch)
				{
					Translator* tmpSwap = _translators[iSearch];
					_translators[iSearch] = _translators[iName];
					_translators[iName] = tmpSwap;
				}
				
				break;
			}
		}
	}
}

Translator const* ManTranslator::getTranslator(wxString const& name)const
{
	for(auto it: _translators)
	{
		if(it->getName() == name)
			return it;
	}
		
	return nullptr;
}

WinManager* ManTranslator::newEditWindow(wxWindow* parent)
{
	return new WinManTranslator(parent);
}

void ManTranslator::manLoad(wxFileConfig& fileConfig)
{
	wxArrayString tranlatorsOrder(_translators.size(), &wxEmptyString);
	
	for(size_t i = 0; i < _translators.size(); i++)
	{
		size_t index = (size_t)fileConfig.ReadLong(_translators[i]->getName(), (long)i);
		tranlatorsOrder[index] = _translators[i]->getName();
	}
		
	setOrderTranslators(tranlatorsOrder);
}

void ManTranslator::manSave(wxFileConfig& fileConfig)const
{
	for(size_t i = 0; i < _translators.size(); i++)
		fileConfig.Write(_translators[i]->getName(), (long)i);
}

// *****************************************************************************
// Class WinManTranslator
// *****************************************************************************

WinManTranslator::WinManTranslator(wxWindow* parent)
: WinManager(parent, _("Translators"))
{	
	//Créations staticBoxInformation et de staticTextInformation
	StaticBox* staticBoxInformation = new StaticBox(this, wxID_ANY, _("Information:"));
	wxStaticText* staticTextInformation = new wxStaticText(
		staticBoxInformation, wxID_ANY,
		_("Sort your translator by order from your preference.\n"
		"The first in the list, is first used.\n"
		"If the translator can not translate the text, the second translator is used..."));
	//Mise en forme avec un sizer.
	wxSizer* sizerInformation = new wxBoxSizer(wxVERTICAL);
	sizerInformation->Add(staticTextInformation, 0, wxTOP, SIZE_BORDER);	
	staticBoxInformation->SetSizer(sizerInformation);
	
	//Créations de _listCtrlTranslator.
	StaticBox* staticBoxTranslator = new StaticBox(this, wxID_ANY, _("Translator:"));
	wxArrayString namesTranslators = ManTranslator::get().getOrderTranslators();
	_listBoxTranslator = new wxListBox(staticBoxTranslator, wxID_ANY, wxDefaultPosition, wxDefaultSize, namesTranslators.GetCount(), &namesTranslators.Item(0));
	//Mise en forme avec un sizer.
	wxSizer* sizerTranslator = new wxBoxSizer(wxVERTICAL);
	sizerTranslator->Add(_listBoxTranslator, 1, wxTOP, SIZE_BORDER);	
	staticBoxTranslator->SetSizer(sizerTranslator);
	
	//Créations de la description du traducteur sélectionner.
	StaticBox* staticBoxDescription = new StaticBox(this, wxID_ANY, _("Description:"));
	_staticTextDescription = new wxStaticText(staticBoxDescription, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	_hyperlinkCtrlSee = new wxHyperlinkCtrl(staticBoxDescription, wxID_ANY, _("See also: "), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_LEFT|wxHL_CONTEXTMENU|wxBORDER_NONE);
	//Mise en forme avec un sizer.
	wxSizer* sizerDescription = new wxBoxSizer(wxVERTICAL);
	sizerDescription->Add(_staticTextDescription);
	sizerDescription->Add(_hyperlinkCtrlSee);
	staticBoxDescription->SetSizer(sizerDescription);
	
	//Créations des boutons.
	StaticBox* staticBoxControl = new StaticBox(this, wxID_ANY, _("Control:"));
	_buttonUp = new wxButton(staticBoxControl, wxID_UP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
	_buttonDown = new wxButton(staticBoxControl, wxID_DOWN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
	//Mise en forme des bouton dans un sizer.
	wxSizer* sizerButtons = new wxBoxSizer(wxVERTICAL);
	sizerButtons->Add(_buttonUp, 	0, wxBOTTOM|wxTOP, SIZE_BORDER);	
	sizerButtons->Add(_buttonDown, 	0);
	staticBoxControl->SetSizer(sizerButtons);
	
	
	//Mise en forme avec des sizers.
	wxSizer* sizerDescriptionAndControl = new wxBoxSizer(wxVERTICAL);
	sizerDescriptionAndControl->Add(staticBoxDescription, 	0, wxEXPAND|wxLEFT, SIZE_BORDER);
	sizerDescriptionAndControl->AddStretchSpacer(1);
	sizerDescriptionAndControl->Add(staticBoxControl, 		0, wxEXPAND|wxLEFT, SIZE_BORDER);
	wxSizer* sizerTrenslator = new wxBoxSizer(wxHORIZONTAL);
	sizerTrenslator->Add(staticBoxTranslator, 				0, wxEXPAND, SIZE_BORDER);
	sizerTrenslator->Add(sizerDescriptionAndControl, 		1, wxEXPAND, SIZE_BORDER);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxInformation, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(sizerTrenslator, 		1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);	
	SetSizer(sizerMain);
	
	//Bind
	_listBoxTranslator->Bind(wxEVT_LISTBOX, &WinManTranslator::onListBox, this);
	Bind(wxEVT_BUTTON, &WinManTranslator::onButton, this);
}

WinManTranslator::~WinManTranslator()
{
	//Unbind
	_listBoxTranslator->Unbind(wxEVT_LISTBOX, &WinManTranslator::onListBox, this);
	Unbind(wxEVT_BUTTON, &WinManTranslator::onButton, this);
}

void WinManTranslator::refreshGuiFromManager()
{
	//On initialise la liste
	wxArrayString namesTranslators = ManTranslator::get().getOrderTranslators();
	for(size_t i = 0; i < namesTranslators.GetCount(); i++)
	{
		_listBoxTranslator->SetString(i, namesTranslators[i]);
	}
	
	//On dé-sélectionne tout sélection.
	_listBoxTranslator->Deselect(_listBoxTranslator->GetSelection());
	
	_staticTextDescription->Show(false);
	_hyperlinkCtrlSee->Show(false);
	_buttonUp->Enable(false);
	_buttonDown->Enable(false);
}

void WinManTranslator::refreshManagerFromGui()const
{
	wxArrayString translators;
	for(unsigned int i = 0; i < _listBoxTranslator->GetCount(); i++)
		translators.Add(_listBoxTranslator->GetString(i));
	
	ManTranslator::get().setOrderTranslators(translators);
}

void WinManTranslator::onListBox(wxCommandEvent&)
{
	updateButtons();
	
	//Mise à jour de la description du traducteur sélectionner.
	
	//Récupérer le non du traducteur
	wxString name = _listBoxTranslator->GetString(_listBoxTranslator->GetSelection());
	//On récupère le traducteur.
	Translator const* translator = ManTranslator::get().getTranslator(name);
	
	_staticTextDescription->Show(true);
	_staticTextDescription->SetLabel(translator->getDescription());
	
	if(translator->getURL().IsEmpty())
		_hyperlinkCtrlSee->Show(false);
	else
	{
		_hyperlinkCtrlSee->Show(true);
		_hyperlinkCtrlSee->SetLabel(_("See also: ")+translator->getURL());
		_hyperlinkCtrlSee->SetURL(translator->getURL());
	}
	Layout();
}

void WinManTranslator::onButton(wxCommandEvent& event)
{
	if(event.GetId() == wxID_UP)
		swapInList(_listBoxTranslator->GetSelection(), _listBoxTranslator->GetSelection()-1);
	else if(event.GetId() == wxID_DOWN)
		swapInList(_listBoxTranslator->GetSelection(), _listBoxTranslator->GetSelection()+1);
}

void WinManTranslator::swapInList(unsigned int itemFirst, unsigned int itemSecond)
{
	wxString itemFirstStr = _listBoxTranslator->GetString(itemFirst);
	_listBoxTranslator->SetString(itemFirst, _listBoxTranslator->GetString(itemSecond));
	_listBoxTranslator->SetString(itemSecond, itemFirstStr);
	
	_listBoxTranslator->SetSelection(itemSecond);
	updateButtons();
}

void WinManTranslator::updateButtons()
{
	//Activation des bouton ou pas
	_buttonUp->Enable();
	_buttonDown->Enable();
	if(_listBoxTranslator->GetSelection() == 0)
		_buttonUp->Enable(false);
	else if(_listBoxTranslator->GetSelection() == (int)_listBoxTranslator->GetCount()-1)
		_buttonDown->Enable(false);
}
