//02.01.2013

#include "dialogPreferences.hpp"

#include <wx/msgdlg.h>
#include <wx/fileconf.h>

#include <iostream>

//! ****************************************************************************
//! Class DialogPreferences
//! ****************************************************************************

DialogPreferences::DialogPreferences(std::map<ShortcutKey, Action*> const& shortcutAction)
: GuiDialogPreferences(nullptr), _firstUpdate(true), _oKButtonWasClick(false)
{	
	//Liste des langues
	_lang["af"] = _("Afrikaans");
	_lang["sq"] = _("Albanian");
	_lang["ar"] = _("Arabic");
	_lang["hy"] = _("Armenian");
	_lang["az"] = _("Azerbaijani");
	_lang["eu"] = _("Basque");
	_lang["be"] = _("Belarusian");
	_lang["bn"] = _("Bengali");
	_lang["bg"] = _("Bulgarian");
	_lang["ca"] = _("Catalan");
	_lang["zh-CN"] = _("Chinese");
	_lang["hr"] = _("Croatian");
	_lang["sr"] = _("Czech");
	_lang["da"] = _("Danish");
	_lang["nl"] = _("Dutch");
	_lang["en"] = _("English");
	_lang["eo"] = _("Esperanto");
	_lang["et"] = _("Estonian");
	_lang["tl"] = _("Filipino");
	_lang["fi"] = _("Finnish");
	_lang["fr"] = _("French");
	_lang["gl"] = _("Galician");
	_lang["ka"] = _("Georgian");
	_lang["de"] = _("German");
	_lang["el"] = _("Greek");
	_lang["gu"] = _("Gujarati");
	_lang["ht"] = _("Haitian Creole");
	_lang["iw"] = _("Hebrew");
	_lang["hi"] = _("Hindi");
	_lang["hu"] = _("Hungarian");
	_lang["is"] = _("Icelandic");
	_lang["id"] = _("Indonesian");
	_lang["ga"] = _("Irish");
	_lang["it"] = _("Italian");
	_lang["ja"] = _("Japanese");
	_lang["kn"] = _("Kannada");
	_lang["ko"] = _("Korean");
	_lang["lo"] = _("Lao");
	_lang["la"] = _("Latin");
	_lang["lv"] = _("Latvian");
	_lang["it"] = _("Lithuanian");
	_lang["mk"] = _("Macedonian");
	_lang["ms"] = _("Malay");
	_lang["mt"] = _("Maltese");
	_lang["no"] = _("Norwegian");
	_lang["fa"] = _("Persian");
	_lang["pl"] = _("Polish");
	_lang["pt"] = _("Portuguese");
	_lang["ro"] = _("Romanian");
	_lang["ru"] = _("Russian");
	_lang["sr"] = _("Serbian");
	_lang["sk"] = _("Slovak");
	_lang["sl"] = _("Slovenian");
	_lang["es"] = _("Spanish");
	_lang["sw"] = _("Swahili");
	_lang["sv"] = _("Swedish");
	_lang["ta"] = _("Tamil");
	_lang["te"] = _("Telugu");
	_lang["th"] = _("Thai");
	_lang["tr"] = _("Turkish");
	_lang["uk"] = _("Ukrainian");
	_lang["ur"] = _("Urdu");
	_lang["vi"] = _("Vietnamese");
	_lang["cy"] = _("Welsh");
	_lang["yi"] = _("Yiddish");
	
	//Chois des actions
	_actChs.Add(_("Translation"));
	#if defined(__USE_TTS__)
	_actChs.Add(_("Say"));
	#endif
	
	//Chois des langues
	for(auto &it: _lang)
		_lanChs.Add(it.second);
    
    //Magnifier 
    _staticTextSartup->SetLabelMarkup("<b>"+_("Option")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");
    
    //Remplissage des ligne avec les raccourcis connue
	for(auto &it: shortcutAction)
	{
		//Obtenir le raccourci en string et l'ajouter au PropertyGrid.
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		wxPGProperty* actProp = _propertyGridShortcut->Append(new wxEnumProperty(stringShortcut, wxPG_LABEL, _actChs));
		
		//Action du raccourcit
		Action const& action = *it.second;
		
		if(action.getName() == "tr")
		{
			ActTranslation const& actTranslation = static_cast<ActTranslation const&>(action);
			
			//Ajouter les paramètre dans la PropertyGrid.
			actProp->SetValueFromString(_("Translation"));
			wxPGProperty* srcLanProp = new wxEnumProperty(_("Source language"), wxPG_LABEL, _lanChs);
			srcLanProp->SetValueFromString(_lang[actTranslation.getLanguageScr()]);
			_propertyGridShortcut->AppendIn(actProp, srcLanProp);
			wxPGProperty* destLanProp = new wxEnumProperty(_("to"), wxPG_LABEL, _lanChs);
			destLanProp->SetValueFromString(_lang[actTranslation.getLanguageTo()]);
			_propertyGridShortcut->AppendIn(actProp, destLanProp);
		}
		#if defined(__USE_TTS__)
		else if(action.getName() == "ts")
		{
			ActSay const& actSay = static_cast<ActSay const&>(action);
			
			//Ajouter les paramètre dans la PropertyGrid.
			actProp->SetValueFromString(_("Say"));
			wxPGProperty* lanProp = new wxEnumProperty(_("Language"), wxPG_LABEL, _lanChs);
			lanProp->SetValueFromString(_lang[actSay.getLanguage()]);
			_propertyGridShortcut->AppendIn(actProp, lanProp);
		}
		#endif
	}
	
	//Cacher tout les paramètres (Source language,to,Language).
	_propertyGridShortcut->ExpandAll(false);
	
	//Événement
	Bind(wxEVT_PG_SELECTED, &DialogPreferences::OnSelected, this);
	Bind(wxEVT_PG_DOUBLE_CLICK, &DialogPreferences::OnDoubleClick, this);
	Bind(wxEVT_PG_CHANGED, &DialogPreferences::OnChanged, this);
}

DialogPreferences::~DialogPreferences()
{
}

void DialogPreferences::OnButtonClickDelete(wxCommandEvent&)
{
	//Affiche un dialogue de confirmation.
	wxMessageDialog dlg(this, _("Do you want really delete this shortcut?"),  wxMessageBoxCaptionStr, wxYES_NO|wxCENTRE|wxICON_QUESTION);
    if(dlg.ShowModal() == wxID_YES)
	{
		//Suppression de la wxPGProperty
		wxPGProperty* slectProp = _propertyGridShortcut->GetSelectedProperty();
		_propertyGridShortcut->DeleteProperty(slectProp);
		
		_buttonDelete->Enable(false);
	}
}

void DialogPreferences::OnButtonClickAdd(wxCommandEvent&)
{
	//Lance le dialogue de sélection de raccourci.
	DialogChoiceShortcut dlg(this);
	if(dlg.ShowModal() == wxID_OK)
	{
		//Chois des actions
		wxPGChoices actChs;
		actChs.Add(_("Translation"));
		#if defined(__USE_TTS__)
		actChs.Add(_("Say"));
		#endif
		
		//Récupération du wxPGProperty si le raccourci existe déjà.
		wxPGProperty* prop = _propertyGridShortcut->GetPropertyByLabel(dlg.GetShortcut());
	
		//Affiche le wxPGProperty si le raccourci existe déjà.
		if(prop)
		{
			_propertyGridShortcut->SelectProperty(prop);

			wxMessageDialog dlg(this, _("This shortcut already exist !"),  wxMessageBoxCaptionStr, wxOK|wxCENTRE|wxICON_INFORMATION);
			dlg.ShowModal();
		}
		//Création d'un nouveau wxPGProperty
		else 
		{
			wxPGProperty* prop = _propertyGridShortcut->Append(new wxEnumProperty(dlg.GetShortcut(), wxPG_LABEL, actChs));
			changedAction(prop, prop->GetDisplayedString());
		}
	}
}

void DialogPreferences::OnSelected(wxPropertyGridEvent& event)
{
	//Obtenir le wxPGProperty sélectionner
	wxPGProperty* slectProp = event.GetProperty();
	
	if(slectProp != nullptr)
	{	
		//La ligne shortcut,action à été choisie.
		#if defined(__USE_TTS__)
		if(	slectProp->GetDisplayedString() == _("Translation") ||
			slectProp->GetDisplayedString() == _("Say"))
		#else
		if(slectProp->GetDisplayedString() == _("Translation"))
		#endif
		{
			_buttonDelete->Enable();
		}
		else
		{
			_buttonDelete->Enable(false);
		}
	}
}

void DialogPreferences::OnDoubleClick(wxPropertyGridEvent& event)
{	
	//Obtenir le wxPGProperty sélectionner
	wxPGProperty* slectProp = event.GetProperty();
	
	if(slectProp != nullptr)
	{	
		//Déplie le wxPGProperty
		_propertyGridShortcut->Expand(slectProp);
		
		//Lance le dialogue de sélection de raccourci.
		DialogChoiceShortcut dlg(this, slectProp->GetLabel());
		if(dlg.ShowModal() == wxID_OK)
			slectProp->SetLabel(dlg.GetShortcut());
	}
}

void DialogPreferences::OnChanged(wxPropertyGridEvent& event)
{	
	//Obtenir le wxPGProperty sélectionner
	wxPGProperty* slectProp = event.GetProperty();
	
	if(slectProp != nullptr)
		changedAction(slectProp, slectProp->GetDisplayedString());
}

void DialogPreferences::OnOkButtonClick(wxCommandEvent& event)
{	
	_oKButtonWasClick = true;
	
	soveInFileConfig();
	event.Skip();
}

void DialogPreferences::OnApplyButtonClick(wxCommandEvent& event)
{	
	soveInFileConfig();	
	event.Skip();
}

void DialogPreferences::OnUpdateUIPropertyGridShortcut(wxUpdateUIEvent& event)
{
	if(_firstUpdate)
	{
		_propertyGridShortcut->SetSplitterPosition(_propertyGridShortcut->GetSize().GetWidth()/2, 0);
		_firstUpdate = false;
	}
	event.Skip();
}

void DialogPreferences::changedAction(wxPGProperty* property, wxString const& action)
{		
	//Quelle action ?
	if(action == _("Translation"))
	{
		//Ranplaser le raccourci (paramètre) au PropertyGrid.
		wxPGProperty* actProp = new wxEnumProperty(property->GetLabel(), wxPG_LABEL, _actChs);
		actProp->SetValueFromString(action);
		_propertyGridShortcut->ReplaceProperty(property, actProp);
	
		//Ajouter les paramètre dans la PropertyGrid.
		wxPGProperty* srcLanProp = new wxEnumProperty(_("Source language"), wxPG_LABEL, _lanChs);
		_propertyGridShortcut->AppendIn(actProp, srcLanProp);
		wxPGProperty* destLanProp = new wxEnumProperty(_("to"), wxPG_LABEL, _lanChs);
		_propertyGridShortcut->AppendIn(actProp, destLanProp);
	}
	#if defined(__USE_TTS__)
	else if(action == _("Say"))
	{
		//Ranplaser le raccourci (paramètre) au PropertyGrid.
		wxPGProperty* actProp = new wxEnumProperty(property->GetLabel(), wxPG_LABEL, _actChs);
		actProp->SetValueFromString(action);
		_propertyGridShortcut->ReplaceProperty(property, actProp);
	
		//Ajouter les paramètre dans la PropertyGrid.
		wxPGProperty* lanProp = new wxEnumProperty(_("Language"), wxPG_LABEL, _lanChs);
		_propertyGridShortcut->AppendIn(actProp, lanProp);
	}
	#endif
}

void DialogPreferences::soveInFileConfig()const
{
	//Chargement de la config
	wxFileConfig fileConfig(	PROJECT_NAME,
								wxEmptyString,
								wxGetUserHome()+"/."+PROJECT_NAME);
	fileConfig.DeleteAll();
	
	//Ajout du menu dans le fichier de config
	fileConfig.Write("show_menu", _checkBoxShowMenu->GetValue());


	//Parcour la liste des raccourcis
	wxPropertyGridIterator it = _propertyGridShortcut->GetIterator();
	wxString varShortcut;
	int i = 1;
	while(!it.AtEnd())
	{
		//Récupération du wxPGProperty
		wxPGProperty* prop = it.GetProperty();
	
		//std::cout << prop->GetLabel() << " : " << prop->GetDisplayedString() << std::endl;
		varShortcut.Clear();
		varShortcut << prop->GetLabel();
		
		if(prop->GetDisplayedString() == _("Translation"))
		{
			varShortcut << " tr ";
			//Récupération des paramètres.
			it.Next();
			prop = it.GetProperty();
			varShortcut << longLangToShortLang(prop->GetDisplayedString()) << " ";
			it.Next();
			prop = it.GetProperty();
			varShortcut << longLangToShortLang(prop->GetDisplayedString());
		}
		#if defined(__USE_TTS__)
		else if(prop->GetDisplayedString() == _("Say"))
		{
			//Récupération des paramètres.
			varShortcut << " ts ";
			it.Next();
			prop = it.GetProperty();
			varShortcut << longLangToShortLang(prop->GetDisplayedString());
		}
		#endif
		
		//Ajout du raccourci dans le fichier de config
		fileConfig.Write(wxString("shortcut")<<i, varShortcut);
		
		//Raccourci suivent
		it.Next();
		i++;
	}
	
	
}

wxString DialogPreferences::longLangToShortLang(wxString const& longLang)const
{
	for(auto &it: _lang)
	{
		if(it.second == longLang)
			return it.first;
	}
	
	return "";
}

bool DialogPreferences::shutdown()const
{
	if(_oKButtonWasClick)
	{
		return _toggleBtnTurnOff->GetValue();
	}
		
	return false;
}

//! ****************************************************************************
//! Class DialogChoiceShortcut
//! ****************************************************************************

DialogChoiceShortcut::DialogChoiceShortcut(wxWindow* parent, wxString const& strShortcut) : GuiDialogChoiceShortcut(parent)
{
	//Un racoursi est à afficher
	if(!strShortcut.IsEmpty())
		_staticTextChoisShortcut->SetLabel(strShortcut);
	else
		_sdbSizerOK->Enable(false);
		
	//Initialisation des variable
	_keyCtrlIsPressed = false;
	_keyAltIsPressed = false;
	_keyShiftIsPressed = false;
	_keyWinIsPressed = false;
	
	_shortKeyIsValide = false;
		
	//Les événement
	_sdbSizerOK->Bind(wxEVT_KEY_UP, &DialogChoiceShortcut::OnKeyUp, this);
	_sdbSizerOK->Bind(wxEVT_KEY_DOWN, &DialogChoiceShortcut::OnKeyDown, this);
	_sdbSizerCancel->Bind(wxEVT_KEY_UP, &DialogChoiceShortcut::OnKeyUp, this);
	_sdbSizerCancel->Bind(wxEVT_KEY_DOWN, &DialogChoiceShortcut::OnKeyDown, this);
}

DialogChoiceShortcut::~DialogChoiceShortcut()
{
}

void DialogChoiceShortcut::OnKeyUp(wxKeyEvent& event)
{
	std::cout << "OnKeyUp" << std::endl;
	
	//Mise à jour des touches modifier
	switch(event.GetRawKeyFlags())
	{
		case RAW_KEY_CODE_MODIFIER_CONTROL:
		_keyCtrlIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_ALT:
		_keyAltIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_SHIFT:
		_keyShiftIsPressed = false;
		break;
		case RAW_KEY_CODE_MODIFIER_WIN:
		_keyWinIsPressed = false;
		break;
	}
	
	//Mise à jour du texte.
	updateStaticTextChoisShortcut(event.GetUnicodeKey());
	
	event.Skip();
}

void DialogChoiceShortcut::OnKeyDown(wxKeyEvent& event)
{	
	std::cout << "OnKeyDown" << std::endl;
	//Mise a jour des touches modifier
	switch(event.GetRawKeyFlags())
	{
		case RAW_KEY_CODE_MODIFIER_CONTROL:
		_keyCtrlIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_ALT:
		_keyAltIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_SHIFT:
		_keyShiftIsPressed = true;
		break;
		case RAW_KEY_CODE_MODIFIER_WIN:
		_keyWinIsPressed = true;
		break;
	}
	
	//Mise à jour du texte (Et du bouton OK).
	_shortKeyIsValide = false;
	_sdbSizerOK->Enable(false);
	updateStaticTextChoisShortcut(event.GetUnicodeKey());
	
	event.Skip();
}

void DialogChoiceShortcut::updateStaticTextChoisShortcut(wxChar key)
{
	//Tempe que le raccourci n'est pas valide, on met à jour le texte.
	if(!_shortKeyIsValide)
	{
		wxString strShortcut;

		if(_keyCtrlIsPressed)
			strShortcut << "ctrl";
		if(_keyAltIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "alt";
		}
		if(_keyShiftIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "shift";
		}
		if(_keyWinIsPressed)
		{
			if(!strShortcut.IsEmpty())
				strShortcut << "+";
				
			strShortcut << "win";
		}
			
		if(!strShortcut.IsEmpty() && key)
		{
			strShortcut << "+" << key;
			_shortKeyIsValide = true;
			_sdbSizerOK->Enable();
		}
		
		strShortcut.MakeLower();
		_staticTextChoisShortcut->SetLabel(strShortcut);
	}
}

wxString DialogChoiceShortcut::GetShortcut()
{
	return _staticTextChoisShortcut->GetLabel();
}
		
