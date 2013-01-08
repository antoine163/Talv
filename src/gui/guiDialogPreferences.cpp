///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  1 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogPreferences.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogPreferences::GuiDialogPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxNotebook* _notebook;
	_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	_panelGeneral = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextSartup = new wxStaticText( _panelGeneral, wxID_ANY, _("Sartup"), wxDefaultPosition, wxDefaultSize, 0 );
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
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextShortcut = new wxStaticText( _panelShortcut, wxID_ANY, _("Shortcut"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextShortcut->Wrap( -1 );
	bSizer4->Add( _staticTextShortcut, 0, wxALL, 5 );
	
	_listCtrlShortcut = new wxListCtrl( _panelShortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_EDIT_LABELS|wxLC_REPORT|wxLC_VRULES );
	bSizer4->Add( _listCtrlShortcut, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonDelete = new wxButton( _panelShortcut, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonDelete, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonSetting = new wxButton( _panelShortcut, wxID_ANY, _("Setting"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonSetting, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonAdd = new wxButton( _panelShortcut, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonAdd, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
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
}

GuiDialogPreferences::~GuiDialogPreferences()
{
}
