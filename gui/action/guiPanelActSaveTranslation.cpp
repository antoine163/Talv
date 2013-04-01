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
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* staticTextFolder;
	staticTextFolder = new wxStaticText( this, wxID_ANY, _("Folder where save the translations :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextFolder->Wrap( -1 );
	bSizer7->Add( staticTextFolder, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	wxStaticText* staticTextFile;
	staticTextFile = new wxStaticText( this, wxID_ANY, _("Name of file where save the translations :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextFile->Wrap( -1 );
	bSizer7->Add( staticTextFile, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	bSizer6->Add( bSizer7, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	_dirPickerFolder = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer8->Add( _dirPickerFolder, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	_textCtrlFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( _textCtrlFile, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );
	
	bSizer6->Add( bSizer8, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxStaticLine* staticline2;
	staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	_radioBtnSaveAllTranslations = new wxRadioButton( this, wxID_ANY, _("Save all translations from google."), wxDefaultPosition, wxDefaultSize, 0 );
	_radioBtnSaveAllTranslations->SetValue( true ); 
	bSizer11->Add( _radioBtnSaveAllTranslations, 0, wxRIGHT|wxLEFT, 5 );
	
	_radioBtnSaveATranslation = new wxRadioButton( this, wxID_ANY, _("Save a translation from google."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( _radioBtnSaveATranslation, 0, wxRIGHT|wxLEFT, 5 );
	
	bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );
	
	wxStaticLine* staticline3;
	staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer10->Add( staticline3, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	_checkBoxNoDoublon = new wxCheckBox( this, wxID_ANY, _("Don't create doublon."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxNoDoublon->SetValue(true); 
	bSizer12->Add( _checkBoxNoDoublon, 0, wxRIGHT|wxLEFT, 5 );
	
	_checkBoxShowDialog = new wxCheckBox( this, wxID_ANY, _("Show a dialog for select the translation."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxShowDialog->SetValue(true); 
	bSizer12->Add( _checkBoxShowDialog, 0, wxRIGHT|wxLEFT, 5 );
	
	bSizer10->Add( bSizer12, 1, wxEXPAND, 5 );
	
	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer9, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_choiceLanguageSource->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActSaveTranslation::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActSaveTranslation::OnChoiceTo ), NULL, this );
}

GuiPanelActSaveTranslation::~GuiPanelActSaveTranslation()
{
	// Disconnect Events
	_choiceLanguageSource->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActSaveTranslation::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActSaveTranslation::OnChoiceTo ), NULL, this );
	
}
