///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogActionPreferences.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogActionPreferences::GuiDialogActionPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 450,200 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticTextShortcutText;
	_staticTextShortcutText = new wxStaticText( this, wxID_ANY, _("Shortcut :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextShortcutText->Wrap( -1 );
	bSizer3->Add( _staticTextShortcutText, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT|wxALIGN_RIGHT, 5 );
	
	bSizer2->Add( bSizer3, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	_textCtrlChortcut = new wxTextCtrl( this, wxID_ANY, _("Click here"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_NOHIDESEL|wxTE_READONLY );
	_textCtrlChortcut->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	bSizer2->Add( _textCtrlChortcut, 4, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticTextActionText;
	_staticTextActionText = new wxStaticText( this, wxID_ANY, _("Action :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextActionText->Wrap( -1 );
	bSizer5->Add( _staticTextActionText, 1, wxTOP|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	bSizer4->Add( bSizer5, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString _choiceActionChoices;
	_choiceAction = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceActionChoices, 0 );
	_choiceAction->SetSelection( 0 );
	bSizer4->Add( _choiceAction, 4, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticTextDescriptionText;
	_staticTextDescriptionText = new wxStaticText( this, wxID_ANY, _("Description :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextDescriptionText->Wrap( -1 );
	bSizer7->Add( _staticTextDescriptionText, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	bSizer6->Add( bSizer7, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	_staticTextDescription = new wxStaticText( this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextDescription->Wrap( -1 );
	bSizer6->Add( _staticTextDescription, 4, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer6, 0, wxEXPAND|wxTOP, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	_bSizerActPreference = new wxBoxSizer( wxVERTICAL );
	
	bSizer1->Add( _bSizerActPreference, 1, wxEXPAND, 5 );
	
	wxStaticLine* m_staticline2;
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	_sdbSizer = new wxStdDialogButtonSizer();
	_sdbSizerOK = new wxButton( this, wxID_OK );
	_sdbSizer->AddButton( _sdbSizerOK );
	_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	_sdbSizer->AddButton( _sdbSizerCancel );
	_sdbSizer->Realize();
	bSizer1->Add( _sdbSizer, 0, wxEXPAND|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_textCtrlChortcut->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( GuiDialogActionPreferences::OnKeyDown ), NULL, this );
	_textCtrlChortcut->Connect( wxEVT_KEY_UP, wxKeyEventHandler( GuiDialogActionPreferences::OnKeyUp ), NULL, this );
	_textCtrlChortcut->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GuiDialogActionPreferences::OnKillFocus ), NULL, this );
	_textCtrlChortcut->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogActionPreferences::OnLeftDown ), NULL, this );
	_choiceAction->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiDialogActionPreferences::OnChoiceAction ), NULL, this );
	_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActionPreferences::OnOKButtonClick ), NULL, this );
}

GuiDialogActionPreferences::~GuiDialogActionPreferences()
{
	// Disconnect Events
	_textCtrlChortcut->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( GuiDialogActionPreferences::OnKeyDown ), NULL, this );
	_textCtrlChortcut->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( GuiDialogActionPreferences::OnKeyUp ), NULL, this );
	_textCtrlChortcut->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GuiDialogActionPreferences::OnKillFocus ), NULL, this );
	_textCtrlChortcut->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogActionPreferences::OnLeftDown ), NULL, this );
	_choiceAction->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiDialogActionPreferences::OnChoiceAction ), NULL, this );
	_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActionPreferences::OnOKButtonClick ), NULL, this );
	
}
