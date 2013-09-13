///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 24 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiDialogPreferences.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelList::GuiPanelList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
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
	_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( GuiPanelList::OnListItemDeselected ), NULL, this );
	_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( GuiPanelList::OnListItemRightClick ), NULL, this );
	_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GuiPanelList::OnListItemSelected ), NULL, this );
	_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickDelete ), NULL, this );
	_buttonPreferences->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickPreferences ), NULL, this );
	_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickAdd ), NULL, this );
}

GuiPanelList::~GuiPanelList()
{
	// Disconnect Events
	_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( GuiPanelList::OnListItemDeselected ), NULL, this );
	_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( GuiPanelList::OnListItemRightClick ), NULL, this );
	_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GuiPanelList::OnListItemSelected ), NULL, this );
	_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickDelete ), NULL, this );
	_buttonPreferences->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickPreferences ), NULL, this );
	_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiPanelList::OnButtonClickAdd ), NULL, this );
	
}

GuiDialogPreferences::GuiDialogPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,300 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	_panelSetting = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextGeneral = new wxStaticText( _panelSetting, wxID_ANY, _("General :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextGeneral->Wrap( -1 );
	bSizer2->Add( _staticTextGeneral, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_checkBoxShowMenu = new wxCheckBox( _panelSetting, wxID_ANY, _("Show a icon in notification bar."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxShowMenu->SetValue(true); 
	bSizer3->Add( _checkBoxShowMenu, 20, wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_checkBoxPowerOn = new wxCheckBox( _panelSetting, wxID_ANY, _("Launch after power on."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( _checkBoxPowerOn, 20, wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( 0, 0, 1, 0, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( _panelSetting, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	_staticTextShutdown = new wxStaticText( _panelSetting, wxID_ANY, _("Shutdown this application"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextShutdown->Wrap( -1 );
	bSizer6->Add( _staticTextShutdown, 0, wxALL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_toggleBtnTurnOff = new wxToggleButton( _panelSetting, wxID_ANY, _("Turn off"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( _toggleBtnTurnOff, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	_panelSetting->SetSizer( bSizer2 );
	_panelSetting->Layout();
	bSizer2->Fit( _panelSetting );
	_notebook->AddPage( _panelSetting, _("Setting"), false );
	
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
