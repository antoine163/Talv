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
	
	_staticTextSartup = new wxStaticText( _panelGeneral, wxID_ANY, _("Option"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextSartup->Wrap( -1 );
	bSizer2->Add( _staticTextSartup, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	_checkBoxShowMenu = new wxCheckBox( _panelGeneral, wxID_ANY, _("Show the popup menu"), wxDefaultPosition, wxDefaultSize, 0 );
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
	_notebook->AddPage( _panelGeneral, _("General"), false );
	_panelShortcut = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	_propertyGridShortcut = new wxPropertyGrid(_panelShortcut);
	bSizer4->Add( _propertyGridShortcut, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonDelete = new wxButton( _panelShortcut, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonDelete->Enable( false );
	
	bSizer5->Add( _buttonDelete, 0, wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonAdd = new wxButton( _panelShortcut, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonAdd, 0, wxALL, 5 );
	
	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	_panelShortcut->SetSizer( bSizer4 );
	_panelShortcut->Layout();
	bSizer4->Fit( _panelShortcut );
	_notebook->AddPage( _panelShortcut, _("Shortcut"), true );
	
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
	_propertyGridShortcut->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GuiDialogPreferences::OnUpdateUIPropertyGridShortcut ), NULL, this );
	_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickDelete ), NULL, this );
	_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickAdd ), NULL, this );
	_sdbSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnApplyButtonClick ), NULL, this );
}

GuiDialogPreferences::~GuiDialogPreferences()
{
	// Disconnect Events
	_propertyGridShortcut->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GuiDialogPreferences::OnUpdateUIPropertyGridShortcut ), NULL, this );
	_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickDelete ), NULL, this );
	_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickAdd ), NULL, this );
	_sdbSizerApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnApplyButtonClick ), NULL, this );
	
}

GuiDialogChoiceShortcut::GuiDialogChoiceShortcut( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 350,80 ), wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticText;
	_staticText = new wxStaticText( this, wxID_ANY, _("Press your shortcut :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticText->Wrap( -1 );
	bSizer6->Add( _staticText, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_staticTextChoisShortcut = new wxStaticText( this, wxID_ANY, _("The shurtcute is not valide"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextChoisShortcut->Wrap( -1 );
	bSizer7->Add( _staticTextChoisShortcut, 10, wxALL, 5 );
	
	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );
	
	_sdbSizer = new wxStdDialogButtonSizer();
	_sdbSizerOK = new wxButton( this, wxID_OK );
	_sdbSizer->AddButton( _sdbSizerOK );
	_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	_sdbSizer->AddButton( _sdbSizerCancel );
	_sdbSizer->Realize();
	bSizer6->Add( _sdbSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( GuiDialogChoiceShortcut::OnKeyDown ) );
	this->Connect( wxEVT_KEY_UP, wxKeyEventHandler( GuiDialogChoiceShortcut::OnKeyUp ) );
}

GuiDialogChoiceShortcut::~GuiDialogChoiceShortcut()
{
	// Disconnect Events
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( GuiDialogChoiceShortcut::OnKeyDown ) );
	this->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( GuiDialogChoiceShortcut::OnKeyUp ) );
	
}
