//02.01.2013

#include "dialogPreferences.hpp"

DialogPreferences::DialogPreferences(std::map<ShortcutKey, Action*> const& shortcutAction) : GuiDialogPreferences(nullptr)
{
	_staticTextSartup->SetLabelMarkup("<b>"+_("Sartup")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");
	
	
	//On attend la version 2.9.5
	//_listCtrlShortcut->EnableAlternateRowColours();
	//SetAlternateRowColour
	
	//Création de colonnes
	_listCtrlShortcut->InsertColumn(0, _("Shortcut"));
	_listCtrlShortcut->InsertColumn(1, _("Action"));
	_listCtrlShortcut->InsertColumn(2, _("Setting"));
	
	//Remplissage des ligne avec les raccourcis connue
	for(auto &it: shortcutAction)
	{
		wxString stringShortcut = ShortcutKey::shortcutKeyToString(it.first);
		_listCtrlShortcut->InsertItem(0, stringShortcut);
		
		Action const& action = *it.second;
		
		
		if(action.getName() == "tr")
		{
			ActTranslation const& actTranslation = static_cast<ActTranslation const&>(action);
			
			_listCtrlShortcut->SetItem(0, 1, _("Translation"));
			_listCtrlShortcut->SetItem(0, 2, 	actTranslation.getLanguageScr()+
												_(" to ")+
												actTranslation.getLanguageTo());
		}
		#if defined(__USE_TTS__)
		else if(action.getName() == "ts")
		{
			ActSay const& actSay = static_cast<ActSay const&>(action);
			
			_listCtrlShortcut->SetItem(0, 1, _("Say"));
			_listCtrlShortcut->SetItem(0, 2, actSay.getLanguage());
		}
		#endif

	}
}

DialogPreferences::~DialogPreferences()
{
}

void DialogPreferences::OnButtonClickDelete(wxCommandEvent&)
{
}

void DialogPreferences::OnButtonClickSetting(wxCommandEvent&)
{
	DialogShurtcut *dlg = new DialogShurtcut(this, _("Setting shurtcut"));
	dlg->ShowModal();
	dlg->Destroy();
}

void DialogPreferences::OnButtonClickAdd(wxCommandEvent&)
{
	DialogShurtcut *dlg = new DialogShurtcut(this, _("Add shurtcut"));
	dlg->ShowModal();
	dlg->Destroy();
}

DialogShurtcut::DialogShurtcut(wxWindow* parent, const wxString& title)
: GuiDialogShurtcut(parent, wxID_ANY, title)
{
	_staticTextShortcut->SetLabelMarkup("<b>"+_("Sartup")+"</b>");
	_staticTextAction->SetLabelMarkup("<b>"+_("Action")+"</b>");
	_staticTextSetting->SetLabelMarkup("<b>"+_("Setting")+"</b>");
}

DialogShurtcut::~DialogShurtcut()
{
}
