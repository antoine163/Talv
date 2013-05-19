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
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* staticTextLanguageSource;
	staticTextLanguageSource = new wxStaticText( this, wxID_ANY, _("Language source :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextLanguageSource->Wrap( -1 );
	bSizer2->Add( staticTextLanguageSource, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 32, 0, 0, wxEXPAND, 5 );
	
	wxArrayString _choiceLanguageSourceChoices;
	_choiceLanguageSource = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageSourceChoices, 0 );
	_choiceLanguageSource->SetSelection( 0 );
	bSizer3->Add( _choiceLanguageSource, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 1, 0, 5 );
	
	wxStaticText* staticTextTo;
	staticTextTo = new wxStaticText( this, wxID_ANY, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextTo->Wrap( -1 );
	bSizer1->Add( staticTextTo, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* staticTextlanguageOfTranslation;
	staticTextlanguageOfTranslation = new wxStaticText( this, wxID_ANY, _("Language of translation :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextlanguageOfTranslation->Wrap( -1 );
	bSizer4->Add( staticTextlanguageOfTranslation, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer5->Add( 32, 0, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString _choiceLanguageOfTranslationChoices;
	_choiceLanguageOfTranslation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceLanguageOfTranslationChoices, 0 );
	_choiceLanguageOfTranslation->SetSelection( 0 );
	bSizer5->Add( _choiceLanguageOfTranslation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer4->Add( bSizer5, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer4, 1, 0, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

GuiPanelActTranslation::~GuiPanelActTranslation()
{
}
