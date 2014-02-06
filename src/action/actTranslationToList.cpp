//! \file **********************************************************************
//! \brief Source Action, traduction et sauvegarde dans une liste.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.O
//! \date 31.03.2013
//!
//! ****************************************************************************
//App
#include "action/actTranslationToList.hpp"
#include "manager/manGeneral.hpp"
#include "manager/manList.hpp"
#include "manager/manNotification.hpp"
#include "list.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>

// *****************************************************************************
// Class ActTranslationToList
// *****************************************************************************

ActTranslationToList::ActTranslationToList()
: _dlgPick(false)
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;
}

ActTranslationToList::~ActTranslationToList()
{
}

IMPLEMENT_ACTION(ActTranslationToList, _("Translation to list"), _("Translation a text from clipboard into a list."));

WinAction* ActTranslationToList::newEditWindow(wxWindow* parent)
{
	return new WinActTranslationToList(parent, this);
}

wxString ActTranslationToList::getStringPreferences()const
{
	return 	wxLocale::GetLanguageName(_lgsrc) +
			' ' + _("to") + ' ' +
			wxLocale::GetLanguageName(_lgto) +
			" in " + _listName;
}

void ActTranslationToList::execute()
{
	ManNotification::get().notify("ActTranslationToList::execute", getStringPreferences(), wxICON_INFORMATION, true);
}

bool ActTranslationToList::listIsUsed(wxString const& listName)
{
	if(_listName == listName)
		return true;
		
	return false;
}

void ActTranslationToList::getLanguages(wxLanguage* lgsrc, wxLanguage* lgto)const
{
	*lgsrc = _lgsrc;
	*lgto = _lgto;
}

void ActTranslationToList::setLanguages(wxLanguage lgsrc, wxLanguage lgto)
{
	_lgsrc = lgsrc;
	_lgto = lgto;
}

wxString ActTranslationToList::getList()const
{
	return _listName;
}

void ActTranslationToList::setList(wxString const& listName)
{
	_listName = listName;
}

bool ActTranslationToList::IsUsedDlgPick()const
{
	return _dlgPick;
}

void ActTranslationToList::UseDlgPick(bool use)
{
	_dlgPick = use;
}

void ActTranslationToList::actLoad(wxFileConfig& fileConfig)
{
	_lgto = ManGeneral::get().getSystemLanguage();                                  
	if(	_lgto == wxLANGUAGE_ENGLISH)
		_lgsrc = wxLANGUAGE_FRENCH;
	else
		_lgsrc = wxLANGUAGE_ENGLISH;	
	
	//On récupère les préférences.
	wxString lg;
	lg = fileConfig.Read("lgsrc", wxLocale::GetLanguageName(_lgsrc));
	_lgsrc = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
	lg = fileConfig.Read("lgto", wxLocale::GetLanguageName(_lgto));
	_lgto = (wxLanguage)wxLocale::FindLanguageInfo(lg)->Language;
	
	_listName = fileConfig.Read("listName", wxEmptyString);
	_dlgPick = fileConfig.ReadBool("showDlgPick", false);
}
		
void ActTranslationToList::actSave(wxFileConfig& fileConfig)const
{
	fileConfig.Write("lgsrc", wxLocale::GetLanguageName(_lgsrc));
	fileConfig.Write("lgto", wxLocale::GetLanguageName(_lgto));
	fileConfig.Write("listName", _listName);
	fileConfig.Write("showDlgPick", _dlgPick);
}

// *****************************************************************************
// Class WinActTranslationToList
// *****************************************************************************

WinActTranslationToList::WinActTranslationToList(wxWindow* parent, ActTranslationToList const* act)
: WinAction(parent, act)
{		
	//Créations du _comboBoxList.
	wxArrayString namesLists = ManList::get().getNamesLists();
	if(namesLists.GetCount() > 0)
	{
		_comboBoxList = new wxComboBox(this, wxID_ANY, act->getList(), wxDefaultPosition, wxDefaultSize, namesLists.GetCount(), &namesLists.Item(0));
		_comboBoxList->AutoComplete(namesLists);
	}
	else
		_comboBoxList = new wxComboBox(this, wxID_ANY);
		
	wxStaticText* staticTextNameList = new wxStaticText(this, wxID_ANY, _("List name:"));
	
	//Mise en fore dans un sizer
	wxSizer* sizeNameList	 = new wxBoxSizer(wxHORIZONTAL);
	sizeNameList->Add(staticTextNameList,	0, wxALIGN_CENTER_VERTICAL|wxRIGHT, SIZE_BORDER);
	sizeNameList->Add(_comboBoxList,	 	1, wxALIGN_CENTER_VERTICAL);
	
	//Créations du _checkBoxShowDlgPick.
	_checkBoxShowDlgPick = new wxCheckBox(this, wxID_ANY, _("Show a dialog for pick your main translation."));
	_checkBoxShowDlgPick->SetValue(act->IsUsedDlgPick());
	
	//Créations du CtrlPickLanguages.
	wxLanguage lgsrc;
	wxLanguage lgto;
	act->getLanguages(&lgsrc, &lgto);
	_ctrlPickLanguages = new CtrlPickLanguages(this, lgsrc, lgto);
	
	GetSizer()->Add(sizeNameList, 			0, wxEXPAND|wxLEFT|wxRIGHT, 			SIZE_BORDER);
	GetSizer()->Add(_checkBoxShowDlgPick, 	0, wxEXPAND|wxLEFT|wxRIGHT, 			SIZE_BORDER);
	GetSizer()->Add(_ctrlPickLanguages, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
	
	updateCtrlPickLanguages();
	
	//Bind
	_comboBoxList->Bind(wxEVT_TEXT, &WinActTranslationToList::onText, this);
}

WinActTranslationToList::~WinActTranslationToList()
{
	//Unbind
	_comboBoxList->Unbind(wxEVT_TEXT, &WinActTranslationToList::onText, this);
}

void WinActTranslationToList::refreshActionFromGui()
{
	ActTranslationToList* act = static_cast<ActTranslationToList*>(_act);
	
	act->setList(_comboBoxList->GetValue());
	act->UseDlgPick(_checkBoxShowDlgPick->GetValue());
	
	wxLanguage lgsrc;
	wxLanguage lgto;
	_ctrlPickLanguages->getLanguages(&lgsrc, &lgto);
	act->setLanguages(lgsrc, lgto);
	
	//Si la liste n'existe pas on la crée.
	if(!ManList::get().existList(_comboBoxList->GetValue()))
		ManList::get().createList(_comboBoxList->GetValue(), lgsrc, lgto);
}

void WinActTranslationToList::onText(wxCommandEvent&)
{	
	updateCtrlPickLanguages();
}

void WinActTranslationToList::updateCtrlPickLanguages()
{
	if(ManList::get().existList(_comboBoxList->GetValue()))
	{
		wxLanguage tmpLgsrc;
		wxLanguage tmpLgto;
		List tmpList = ManList::get().getList(_comboBoxList->GetValue());
		tmpList.getLanguages(&tmpLgsrc, &tmpLgto);
		_ctrlPickLanguages->setLanguages(tmpLgsrc, tmpLgto);
		
		_ctrlPickLanguages->Enable(false);
	}
	else
		_ctrlPickLanguages->Enable();
}
