///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  1 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	wxMenu* _menuTaskBarIcon;
	_menuTaskBarIcon = new wxMenu();
	wxMenuItem* _menuItemPreferences;
	_menuItemPreferences = new wxMenuItem( _menuTaskBarIcon, wxID_ANY, wxString( wxT("Preferences") ) , wxEmptyString, wxITEM_NORMAL );
	_menuTaskBarIcon->Append( _menuItemPreferences );
	
	wxMenuItem* _menuItemEnable;
	_menuItemEnable = new wxMenuItem( _menuTaskBarIcon, wxID_ANY, wxString( wxT("Enable") ) , wxEmptyString, wxITEM_CHECK );
	_menuTaskBarIcon->Append( _menuItemEnable );
	
	wxMenuItem* _menuItemExit;
	_menuItemExit = new wxMenuItem( _menuTaskBarIcon, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	_menuTaskBarIcon->Append( _menuItemExit );
	
	m_menubar1->Append( _menuTaskBarIcon, wxT("MenuTaskBarIcon") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( _menuItemEnable->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::test ) );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::test ) );
	
}
