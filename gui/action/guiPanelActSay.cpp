///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActSay.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActSay::GuiPanelActSay( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticText;
	staticText = new wxStaticText( this, wxID_ANY, _("Language of diction :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText->Wrap( -1 );
	bSizer1->Add( staticText, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString _choiceChoices;
	_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceChoices, 0 );
	_choice->SetSelection( 0 );
	bSizer1->Add( _choice, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

GuiPanelActSay::~GuiPanelActSay()
{
}
