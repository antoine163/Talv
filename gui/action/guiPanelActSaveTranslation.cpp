///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActSaveTranslation.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActSaveTranslation::GuiPanelActSaveTranslation( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("/home/antoine/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_dirPicker1 = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer1->Add( m_dirPicker1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

GuiPanelActSaveTranslation::~GuiPanelActSaveTranslation()
{
}
