///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogListAdd.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogListAdd::GuiDialogListAdd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextName;
	staticTextName = new wxStaticText( this, wxID_ANY, _("Name :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextName->Wrap( -1 );
	bSizer2->Add( staticTextName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( _textCtrlName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Language source :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer4->Add( m_staticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString _choiceLanguageSourceChoices;
	_choiceLanguageSource = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageSourceChoices, 0 );
	_choiceLanguageSource->SetSelection( 0 );
	bSizer4->Add( _choiceLanguageSource, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer3->Add( bSizer4, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* _staticTextTo;
	_staticTextTo = new wxStaticText( this, wxID_ANY, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextTo->Wrap( -1 );
	bSizer3->Add( _staticTextTo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Language of translation :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer5->Add( m_staticText11, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString _choiceLanguageOfTranslationChoices;
	_choiceLanguageOfTranslation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageOfTranslationChoices, 0 );
	_choiceLanguageOfTranslation->SetSelection( 0 );
	bSizer5->Add( _choiceLanguageOfTranslation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer3->Add( bSizer5, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticLine* staticline;
	staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline, 0, wxEXPAND | wxALL, 5 );
	
	_sdbSizer = new wxStdDialogButtonSizer();
	_sdbSizerOK = new wxButton( this, wxID_OK );
	_sdbSizer->AddButton( _sdbSizerOK );
	_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	_sdbSizer->AddButton( _sdbSizerCancel );
	_sdbSizer->Realize();
	bSizer1->Add( _sdbSizer, 0, wxEXPAND|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogListAdd::OnOKButtonClick ), NULL, this );
}

GuiDialogListAdd::~GuiDialogListAdd()
{
	// Disconnect Events
	_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogListAdd::OnOKButtonClick ), NULL, this );
	
}
