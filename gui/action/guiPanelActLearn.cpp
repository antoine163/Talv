///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActLearn.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActLearn::GuiPanelActLearn( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextPickList;
	staticTextPickList = new wxStaticText( this, wxID_ANY, _("Pick a list you want to learn :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextPickList->Wrap( -1 );
	bSizer2->Add( staticTextPickList, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString _choiceListChoices;
	_choiceList = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceListChoices, 0 );
	_choiceList->SetSelection( 0 );
	bSizer2->Add( _choiceList, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	_checkBoxTime = new wxCheckBox( this, wxID_ANY, _("Run this action evrey :"), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxTime->SetValue(true); 
	bSizer3->Add( _checkBoxTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_panelTime = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	_spinCtrlHours = new wxSpinCtrl( _panelTime, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer4->Add( _spinCtrlHours, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* staticTextHours;
	staticTextHours = new wxStaticText( _panelTime, wxID_ANY, _("Hours"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextHours->Wrap( -1 );
	bSizer4->Add( staticTextHours, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_spinCtrlMinutes = new wxSpinCtrl( _panelTime, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 30 );
	bSizer4->Add( _spinCtrlMinutes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* staticTextMinutes;
	staticTextMinutes = new wxStaticText( _panelTime, wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextMinutes->Wrap( -1 );
	bSizer4->Add( staticTextMinutes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_panelTime->SetSizer( bSizer4 );
	_panelTime->Layout();
	bSizer4->Fit( _panelTime );
	bSizer3->Add( _panelTime, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_checkBoxTime->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GuiPanelActLearn::OnCheckBox ), NULL, this );
}

GuiPanelActLearn::~GuiPanelActLearn()
{
	// Disconnect Events
	_checkBoxTime->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GuiPanelActLearn::OnCheckBox ), NULL, this );
	
}

MyDialog1::MyDialog1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer6->Add( m_staticText4, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_textCtrl1, 1, wxALL, 5 );
	
	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer5->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer5->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button1 = new wxButton( this, wxID_ANY, _("fermer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button1, 0, wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, _("verifier"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button2, 0, wxALL, 5 );
	
	bSizer5->Add( bSizer7, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer5 );
	this->Layout();
	bSizer5->Fit( this );
	
	this->Centre( wxBOTH );
}

MyDialog1::~MyDialog1()
{
}
