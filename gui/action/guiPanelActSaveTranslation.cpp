///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActSaveTranslation.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActSaveTranslation::GuiPanelActSaveTranslation( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Folder where save the translations :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer6->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	_dirPicker = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer6->Add( _dirPicker, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	bSizer1->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Name of file where save the translations :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer9->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_textCtrl1, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	bSizer1->Add( bSizer9, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtn4 = new wxRadioButton( this, wxID_ANY, _("Save a translation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_radioBtn4, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer12->Add( m_staticline2, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	bSizer1->Add( bSizer12, 0, wxEXPAND|wxTOP, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_checkBox2 = new wxCheckBox( m_panel2, wxID_ANY, _("Show a dialog for select the translation."), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox2->SetValue(true); 
	bSizer14->Add( m_checkBox2, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel2, wxID_ANY, _("Separate the translation by :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer14->Add( m_staticText4, 0, wxALL, 5 );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_radioBtn12 = new wxRadioButton( m_panel2, wxID_ANY, _("tab"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_radioBtn12, 0, wxALL, 5 );
	
	m_radioBtn13 = new wxRadioButton( m_panel2, wxID_ANY, _(","), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_radioBtn13, 0, wxALL, 5 );
	
	m_radioBtn14 = new wxRadioButton( m_panel2, wxID_ANY, _(";"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_radioBtn14, 0, wxALL, 5 );
	
	m_radioBtn15 = new wxRadioButton( m_panel2, wxID_ANY, _("escape"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_radioBtn15, 0, wxALL, 5 );
	
	bSizer14->Add( gSizer2, 1, wxEXPAND, 5 );
	
	m_panel2->SetSizer( bSizer14 );
	m_panel2->Layout();
	bSizer14->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtn5 = new wxRadioButton( this, wxID_ANY, _("Save all translation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_radioBtn5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer13->Add( m_staticline3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	bSizer1->Add( bSizer13, 0, wxEXPAND|wxTOP, 5 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3->SetSizer( bSizer15 );
	m_panel3->Layout();
	bSizer15->Fit( m_panel3 );
	bSizer1->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

GuiPanelActSaveTranslation::~GuiPanelActSaveTranslation()
{
}
