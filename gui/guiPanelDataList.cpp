///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelDataList.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelDataList::GuiPanelDataList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	_listCtrl = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE|wxDV_ROW_LINES);
	bSizer1->Add( _listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonDelete = new wxButton( this, wxID_DELETE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonDelete->Enable( false );
	
	bSizer2->Add( _buttonDelete, 0, wxALL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonPreferences = new wxButton( this, wxID_PREFERENCES, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonPreferences->Enable( false );
	
	bSizer2->Add( _buttonPreferences, 0, wxALL, 5 );
	
	_buttonAdd = new wxButton( this, wxID_ADD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( _buttonAdd, 0, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickDelete ), NULL, this );
	_buttonPreferences->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickPreferences ), NULL, this );
	_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickAdd ), NULL, this );
}

GuiPanelDataList::~GuiPanelDataList()
{
	// Disconnect Events
	_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickDelete ), NULL, this );
	_buttonPreferences->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickPreferences ), NULL, this );
	_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelDataList::OnButtonClickAdd ), NULL, this );
	
}
