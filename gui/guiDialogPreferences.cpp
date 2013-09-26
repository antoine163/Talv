///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogPreferences.h"

///////////////////////////////////////////////////////////////////////////

GuiDialogPreferences::GuiDialogPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,300 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer1->Add( _notebook, 1, wxEXPAND | wxALL, 5 );
	
	_sdbSizer = new wxStdDialogButtonSizer();
	_sdbSizerOK = new wxButton( this, wxID_OK );
	_sdbSizer->AddButton( _sdbSizerOK );
	_sdbSizerApply = new wxButton( this, wxID_APPLY );
	_sdbSizer->AddButton( _sdbSizerApply );
	_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	_sdbSizer->AddButton( _sdbSizerCancel );
	_sdbSizer->Realize();
	bSizer1->Add( _sdbSizer, 0, wxEXPAND|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GuiDialogPreferences::OnNotebookPageChanged ), NULL, this );
	_sdbSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
}

GuiDialogPreferences::~GuiDialogPreferences()
{
	// Disconnect Events
	_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GuiDialogPreferences::OnNotebookPageChanged ), NULL, this );
	_sdbSizerApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
	
}
