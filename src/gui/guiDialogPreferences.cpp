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
	
	_panelGeneral->SetSizer( bSizer2 );
	_panelGeneral->Layout();
	bSizer2->Fit( _panelGeneral );
	_notebook->AddPage( _panelGeneral, _("General"), true );
	_panelShortcut = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_listCtrl1 = new wxListCtrl( _panelShortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT );
	bSizer3->Add( m_listCtrl1, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( _panelShortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonDelete = new wxButton( _panelShortcut, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonDelete->Enable( false );
	
	bSizer4->Add( _buttonDelete, 0, wxALL, 5 );
	
	_addShortCut = new wxButton( _panelShortcut, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer4->Add( _addShortCut, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	_panelShortcut->SetSizer( bSizer3 );
	_panelShortcut->Layout();
	bSizer3->Fit( _panelShortcut );
	_notebook->AddPage( _panelShortcut, _("Shortcut"), false );
	
	bSizer1->Add( _notebook, 1, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Apply = new wxButton( this, wxID_APPLY );
	m_sdbSizer1->AddButton( m_sdbSizer1Apply );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer1->Add( m_sdbSizer1, 0, wxEXPAND|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

GuiDialogPreferences::~GuiDialogPreferences()
{
}
