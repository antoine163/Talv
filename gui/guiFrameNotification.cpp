///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiFrameNotification.h"

///////////////////////////////////////////////////////////////////////////

GuiFrameNotification::GuiFrameNotification( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	_staticTextTitle = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextTitle->Wrap( -1 );
	_staticTextTitle->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer->Add( _staticTextTitle, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	_staticTextMessage = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextMessage->Wrap( -1 );
	_staticTextMessage->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer->Add( _staticTextMessage, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	this->SetSizer( bSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_staticTextTitle->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiFrameNotification::OnLeftDown ), NULL, this );
	_staticTextMessage->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiFrameNotification::OnLeftDown ), NULL, this );
}

GuiFrameNotification::~GuiFrameNotification()
{
	// Disconnect Events
	_staticTextTitle->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiFrameNotification::OnLeftDown ), NULL, this );
	_staticTextMessage->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiFrameNotification::OnLeftDown ), NULL, this );
	
}
