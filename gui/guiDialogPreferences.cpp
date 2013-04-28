///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
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
	
	wxNotebook* _notebook;
	_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	_panelSetting = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextGeneral = new wxStaticText( _panelSetting, wxID_ANY, _("General :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextGeneral->Wrap( -1 );
	bSizer2->Add( _staticTextGeneral, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_checkBoxShowMenu = new wxCheckBox( _panelSetting, wxID_ANY, _("Show a icon in notification bar."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxShowMenu->SetValue(true); 
	bSizer6->Add( _checkBoxShowMenu, 20, wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_checkBoxPowerOn = new wxCheckBox( _panelSetting, wxID_ANY, _("Launch after power on."), wxDefaultPosition, wxDefaultSize, 0 );
	_checkBoxPowerOn->SetValue(true); 
	bSizer7->Add( _checkBoxPowerOn, 20, wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer7, 0, wxEXPAND, 5 );
	
	_staticTextVolumeTts = new wxStaticText( _panelSetting, wxID_ANY, _("Volume for text to speech (Say a text) :"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextVolumeTts->Wrap( -1 );
	bSizer2->Add( _staticTextVolumeTts, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_spinCtrlVolumeTts = new wxSpinCtrl( _panelSetting, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 400, 100 );
	bSizer8->Add( _spinCtrlVolumeTts, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	wxStaticText* staticTextPercent;
	staticTextPercent = new wxStaticText( _panelSetting, wxID_ANY, _("in %"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextPercent->Wrap( -1 );
	bSizer8->Add( staticTextPercent, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer8->Add( 0, 0, 15, wxEXPAND, 5 );
	
	bSizer2->Add( bSizer8, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( 0, 0, 1, 0, 5 );
	
	wxStaticLine* m_staticline1;
	m_staticline1 = new wxStaticLine( _panelSetting, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	_staticTextShutdown = new wxStaticText( _panelSetting, wxID_ANY, _("Shutdown this application"), wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextShutdown->Wrap( -1 );
	bSizer3->Add( _staticTextShutdown, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_toggleBtnTurnOff = new wxToggleButton( _panelSetting, wxID_ANY, _("Turn off"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( _toggleBtnTurnOff, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	_panelSetting->SetSizer( bSizer2 );
	_panelSetting->Layout();
	bSizer2->Fit( _panelSetting );
	_notebook->AddPage( _panelSetting, _("Setting"), true );
	_panelShortcut = new wxPanel( _notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	_listCtrlAction = new wxListCtrl( _panelShortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
	_menuListAction = new wxMenu();
	_menuItemListAdd = new wxMenuItem( _menuListAction, wxID_ADD, wxString( _("Add") ) , _("Add an action"), wxITEM_NORMAL );
	_menuListAction->Append( _menuItemListAdd );
	
	_menuItemListPreferences = new wxMenuItem( _menuListAction, wxID_ANY, wxString( _("Preferences") ) , _("Preferences of this actions"), wxITEM_NORMAL );
	_menuListAction->Append( _menuItemListPreferences );
	_menuItemListPreferences->Enable( false );
	
	_menuItemListDelete = new wxMenuItem( _menuListAction, wxID_DELETE, wxString( _("Delete") ) , _("Delete this actions"), wxITEM_NORMAL );
	_menuListAction->Append( _menuItemListDelete );
	_menuItemListDelete->Enable( false );
	
	_listCtrlAction->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GuiDialogPreferences::_listCtrlActionOnContextMenu ), NULL, this ); 
	
	bSizer4->Add( _listCtrlAction, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonActDelete = new wxButton( _panelShortcut, wxID_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonActDelete->Enable( false );
	
	bSizer5->Add( _buttonActDelete, 0, wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonActPreferences = new wxButton( _panelShortcut, wxID_PREFERENCES, _("Preferences"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	_buttonActPreferences->Enable( false );
	
	bSizer5->Add( _buttonActPreferences, 0, wxALL, 5 );
	
	_buttonActAdd = new wxButton( _panelShortcut, wxID_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer5->Add( _buttonActAdd, 0, wxALL, 5 );
	
	bSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	_panelShortcut->SetSizer( bSizer4 );
	_panelShortcut->Layout();
	bSizer4->Fit( _panelShortcut );
	_notebook->AddPage( _panelShortcut, _("Shortcut"), false );
	
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
	_listCtrlAction->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( GuiDialogPreferences::OnListItemDeselectedAction ), NULL, this );
	_listCtrlAction->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GuiDialogPreferences::OnListItemSelectedAction ), NULL, this );
	this->Connect( _menuItemListAdd->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ) );
	this->Connect( _menuItemListPreferences->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ) );
	this->Connect( _menuItemListDelete->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ) );
	_buttonActDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ), NULL, this );
	_buttonActPreferences->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ), NULL, this );
	_buttonActAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ), NULL, this );
	_sdbSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
}

GuiDialogPreferences::~GuiDialogPreferences()
{
	// Disconnect Events
	_listCtrlAction->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( GuiDialogPreferences::OnListItemDeselectedAction ), NULL, this );
	_listCtrlAction->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GuiDialogPreferences::OnListItemSelectedAction ), NULL, this );
	this->Disconnect( wxID_ADD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ) );
	this->Disconnect( wxID_DELETE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ) );
	_buttonActDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActDelete ), NULL, this );
	_buttonActPreferences->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActPreferences ), NULL, this );
	_buttonActAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickActAdd ), NULL, this );
	_sdbSizerApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickApply ), NULL, this );
	_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogPreferences::OnButtonClickOK ), NULL, this );
	
	delete _menuListAction; 
}
