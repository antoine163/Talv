///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActTranslation.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActTranslation::GuiPanelActTranslation( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticTextLanguageSource;
	_staticTextLanguageSource = new wxStaticText( this, wxID_ANY, _("Language source :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextLanguageSource->Wrap( -1 );
	bSizer2->Add( _staticTextLanguageSource, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString _choiceLanguageSourceChoices;
	_choiceLanguageSource = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageSourceChoices, 0 );
	_choiceLanguageSource->SetSelection( 0 );
	bSizer2->Add( _choiceLanguageSource, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer5->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer3->Add( 0, 0, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticText* _staticTextTo;
	_staticTextTo = new wxStaticText( this, wxID_ANY, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextTo->Wrap( -1 );
	bSizer3->Add( _staticTextTo, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer5->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* _staticTextlanguageOfTranslation;
	_staticTextlanguageOfTranslation = new wxStaticText( this, wxID_ANY, _("Language of translation :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextlanguageOfTranslation->Wrap( -1 );
	bSizer4->Add( _staticTextlanguageOfTranslation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString _choiceLanguageOfTranslationChoices;
	_choiceLanguageOfTranslation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageOfTranslationChoices, 0 );
	_choiceLanguageOfTranslation->SetSelection( 0 );
	bSizer4->Add( _choiceLanguageOfTranslation, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer5->Add( bSizer4, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer5, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_choiceLanguageSource->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslation::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslation::OnChoiceTo ), NULL, this );
}

GuiPanelActTranslation::~GuiPanelActTranslation()
{
	// Disconnect Events
	_choiceLanguageSource->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslation::OnChoiceSrc ), NULL, this );
	_choiceLanguageOfTranslation->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiPanelActTranslation::OnChoiceTo ), NULL, this );
	
}
