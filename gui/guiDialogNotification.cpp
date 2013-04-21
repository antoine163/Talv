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
	this->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
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
	bSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GuiDialogNotification::OnClose ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ) );
	_staticTextTitle->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ), NULL, this );
	_staticTextMessage->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ), NULL, this );
}

GuiDialogNotification::~GuiDialogNotification()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GuiDialogNotification::OnClose ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ) );
	_staticTextTitle->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ), NULL, this );
	_staticTextMessage->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GuiDialogNotification::OnLeftDown ), NULL, this );
	
}
