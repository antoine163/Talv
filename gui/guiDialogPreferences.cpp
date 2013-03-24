///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogPreferences.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogPreferences::GuiDialogPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,300 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxNotebook* _notebook;
	_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	_panelGeneral = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextSetting = new wxStaticText( _panelGeneral, wxID_ANY, _("Setting"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextSetting->Wrap( -1 );
	bSizer2->Add( _staticTextSetting, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	_checkBoxShowMenu = new wxCheckBox( _panelGeneral, wxID_ANY, _("Show a icon in notification bar."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxShowMenu->SetValue(true); 
	bSizer2->Add( _checkBoxShowMenu, 0, wxLEFT, 20 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( _panelGeneral, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	_staticTextShutdown = new wxStaticText( _panelGeneral, wxID_ANY, _("Shutdown this application"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextShutdown->Wrap( -1 );
	bSizer3->Add( _staticTextShutdown, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_toggleBtnTurnOff = new wxToggleButton( _panelGeneral, wxID_ANY, _("Turn off"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _toggleBtnTurnOff, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	_panelGeneral->SetSizer( bSizer2 );
	_panelGeneral->Layout();
	bSizer2->Fit( _panelGeneral );
	_notebook->AddPage( _panelGeneral, _("General"), true );
	_panelShortcut = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	_listCtrlAction = new wxListCtrl( _panelShortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
	bSizer4->Add( _listCtrlAction, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonActDelete = new wxButton( _panelShortcut, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonActDelete->Enable( false );
	
	bSizer5->Add( _buttonActDelete, 0, wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonActPreferences = new wxButton( _panelShortcut, wxID_ANY, _("Preferences"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonActPreferences->Enable( false );
	
	bSizer5->Add( _buttonActPreferences, 0, wxALL, 5 );
	
	_buttonActAdd = new wxButton( _panelShortcut, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonActAdd, 0, wxALL, 5 );
	
	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	_panelShortcut->SetSizer( bSizer4 );
	_panelShortcut->Layout();
	bSizer4->Fit( _panelShortcut );
	_notebook->AddPage( _panelShortcut, _("Shortcut"), false );
	
	bSizer1->Add( _notebook, 1, wxEXPAND | wxALL, 5 );
	
	_sdbSizer = new wxStdDialogButtonSizer();
	_sdbSizerOK = new wxButton( this, wxID_OK );
	_sdbSizer->AddButton( _sdbSizerOK );
	_sdbSizerApply = new wxButton( this, wxID_APPLY );
	_sdbSizer->AddButton( _sdbSizerApply );
	_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	_sdbSizer->AddButton( _sdbSizerCancel );
	_sdbSizer->Realize();
	bSizer1->Add( _sdbSizer, 0, wxEXPAND|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_buttonActDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ), NULL, this );
	_buttonActPreferences->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ), NULL, this );
	_buttonActAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ), NULL, this );
	_sdbSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
}

GuiDialogPreferences::~GuiDialogPreferences()
{
	// Disconnect Events
	_buttonActDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ), NULL, this );
	_buttonActPreferences->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ), NULL, this );
	_buttonActAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ), NULL, this );
	_sdbSizerApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
	
}
