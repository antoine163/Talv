//version : 1.0
//02.01.2013

#include "dialogPreferences.hpp"
#include "dialogShortcutPreferences.hpp"

#include <wx/msgdlg.h>

//! ****************************************************************************
//! Class DialogPreferences
//! ****************************************************************************

DialogPreferences::DialogPreferences() : GuiDialogPreferences(nullptr)
{	
    //Magnifier 
    _staticTextSetting->SetLabelMarkup("<b>"+_("Setting")+"</b>");
	_staticTextShutdown->SetLabelMarkup("<b>"+_("Shutdown this application")+"</b>");
}

DialogPreferences::~DialogPreferences()
{
}

void DialogPreferences::OnButtonClickActDelete(wxCommandEvent&)
{
}

void DialogPreferences::OnButtonClickActPreferences(wxCommandEvent&)
{
}

void DialogPreferences::OnButtonClickActAdd(wxCommandEvent&)
{
	DialogShortcutPreferences *dlg = new DialogShortcutPreferences(this);
	dlg->ShowModal();
	delete dlg;
}

void DialogPreferences::OnButtonClickOK(wxCommandEvent& event)
{	
	event.Skip();
}

void DialogPreferences::OnButtonClickApply(wxCommandEvent& event)
{	
	event.Skip();
}

bool DialogPreferences::shutdownIsToggle()const
{
	return _toggleBtnTurnOff->GetValue();
}
		
