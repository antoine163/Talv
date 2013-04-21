///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogNotification.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogNotification::GuiDialogNotification( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	_staticTextTitle = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextTitle->Wrap( -1 );
	bSizer->Add( _staticTextTitle, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	_staticTextMessage = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextMessage->Wrap( -1 );
	bSizer->Add( _staticTextMessage, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

GuiDialogNotification::~GuiDialogNotification()
{
}
