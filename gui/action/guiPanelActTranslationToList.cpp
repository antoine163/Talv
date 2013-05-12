///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActTranslationToList.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActTranslationToList::GuiPanelActTranslationToList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* staticTextLanguageSource;
	staticTextLanguageSource = new wxStaticText( this, wxID_ANY, _("Language source :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextLanguageSource->Wrap( -1 );
	bSizer3->Add( staticTextLanguageSource, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString _choiceLanguageSourceChoices;
	_choiceLanguageSource = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageSourceChoices, 0 );
	_choiceLanguageSource->SetSelection( 0 );
	bSizer3->Add( _choiceLanguageSource, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer4->Add( 0, 0, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticText* staticTextTo;
	staticTextTo = new wxStaticText( this, wxID_ANY, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextTo->Wrap( -1 );
	bSizer4->Add( staticTextTo, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* staticTextlanguageOfTranslation;
	staticTextlanguageOfTranslation = new wxStaticText( this, wxID_ANY, _("Language of translation :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextlanguageOfTranslation->Wrap( -1 );
	bSizer5->Add( staticTextlanguageOfTranslation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString _choiceLanguageOfTranslationChoices;
	_choiceLanguageOfTranslation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageOfTranslationChoices, 0 );
	_choiceLanguageOfTranslation->SetSelection( 0 );
	bSizer5->Add( _choiceLanguageOfTranslation, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxStaticLine* staticline1;
	staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextList;
	staticTextList = new wxStaticText( this, wxID_ANY, _("Choose list for save the translations :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextList->Wrap( -1 );
	bSizer6->Add( staticTextList, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	_comboBoxList = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer6->Add( _comboBoxList, 1, wxALL, 5 );
	
	bSizer1->Add( bSizer6, 0, wxEXPAND, 5 );
	
	_checkBoxShowDialog = new wxCheckBox( this, wxID_ANY, _("Show a dialog for select the main translation."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxShowDialog->SetValue(true); 
	bSizer1->Add( _checkBoxShowDialog, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_choiceLanguageSource->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslationToList::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslationToList::OnChoiceTo ), NULL, this );
}

GuiPanelActTranslationToList::~GuiPanelActTranslationToList()
{
	// Disconnect Events
	_choiceLanguageSource->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslationToList::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslationToList::OnChoiceTo ), NULL, this );
	
}

GuiDialogPickMainTranslation::GuiDialogPickMainTranslation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 300,150 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	_staticText = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticText->Wrap( -1 );
	bSizer2->Add( _staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_buttonMainTranslation = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT|wxNO_BORDER );
	bSizer2->Add( _buttonMainTranslation, 1, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxStaticLine* staticline1;
	staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline1, 0, wxEXPAND | wxALL, 5 );
	
	_bSizerTranslation = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer1->Add( _bSizerTranslation, 1, wxEXPAND, 5 );
	
	wxStaticLine* staticline2;
	staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextHelp;
	staticTextHelp = new wxStaticText( this, wxID_ANY, _("Click on text you want save"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextHelp->Wrap( -1 );
	bSizer3->Add( staticTextHelp, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	wxStdDialogButtonSizer* sdbSizer;
	wxButton* sdbSizerCancel;
	sdbSizer = new wxStdDialogButtonSizer();
	sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	sdbSizer->AddButton( sdbSizerCancel );
	sdbSizer->Realize();
	bSizer3->Add( sdbSizer, 1, wxEXPAND|wxBOTTOM, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

GuiDialogPickMainTranslation::~GuiDialogPickMainTranslation()
{
}

GuiPanelTranslation::GuiPanelTranslation( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextKind = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextKind->Wrap( -1 );
	bSizer1->Add( _staticTextKind, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticLine* staticline;
	staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer2->Add( staticline, 0, wxEXPAND | wxALL, 5 );
	
	_bSizerTranslation = new wxBoxSizer( wxVERTICAL );
	
	bSizer2->Add( _bSizerTranslation, 10, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

GuiPanelTranslation::~GuiPanelTranslation()
{
}
