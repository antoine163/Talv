///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 10 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiPanelActLearn.h"

///////////////////////////////////////////////////////////////////////////

GuiPanelActLearn::GuiPanelActLearn( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextPickList;
	staticTextPickList = new wxStaticText( this, wxID_ANY, _("Pick a list you want to learn :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextPickList->Wrap( -1 );
	bSizer2->Add( staticTextPickList, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString _choiceListChoices;
	_choiceList = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceListChoices, 0 );
	_choiceList->SetSelection( 0 );
	bSizer2->Add( _choiceList, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextNbText;
	staticTextNbText = new wxStaticText( this, wxID_ANY, _("Number of texts at learning for every call this action :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextNbText->Wrap( -1 );
	bSizer3->Add( staticTextNbText, 0, wxTOP|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	_spinCtrlNbText = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );
	bSizer3->Add( _spinCtrlNbText, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	_checkBoxTime = new wxCheckBox( this, wxID_ANY, _("Run this action evrey :"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( _checkBoxTime, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	_panelTime = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	_panelTime->Enable( false );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer5->Add( 32, 0, 0, wxEXPAND, 5 );
	
	wxStaticText* staticTextHours;
	staticTextHours = new wxStaticText( _panelTime, wxID_ANY, _("Hours :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextHours->Wrap( -1 );
	bSizer5->Add( staticTextHours, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_spinCtrlHours = new wxSpinCtrl( _panelTime, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer5->Add( _spinCtrlHours, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* staticTextMinutes;
	staticTextMinutes = new wxStaticText( _panelTime, wxID_ANY, _("Minutes :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextMinutes->Wrap( -1 );
	bSizer5->Add( staticTextMinutes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_spinCtrlMinutes = new wxSpinCtrl( _panelTime, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 30 );
	bSizer5->Add( _spinCtrlMinutes, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	_panelTime->SetSizer( bSizer5 );
	_panelTime->Layout();
	bSizer5->Fit( _panelTime );
	bSizer4->Add( _panelTime, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	_checkBoxTime->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GuiPanelActLearn::OnCheckBox ), NULL, this );
}

GuiPanelActLearn::~GuiPanelActLearn()
{
	// Disconnect Events
	_checkBoxTime->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GuiPanelActLearn::OnCheckBox ), NULL, this );
	
}

GuiDialogActLearn::GuiDialogActLearn( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	_staticTextInfo = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	_staticTextInfo->Wrap( -1 );
	bSizer2->Add( _staticTextInfo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Text") ), wxHORIZONTAL );
	
	wxPanel* panelLg;
	panelLg = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_staticTextPropose = new wxStaticText( panelLg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextPropose->Wrap( -1 );
	bSizer3->Add( _staticTextPropose, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_staticTextAnswer = new wxStaticText( panelLg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	_staticTextAnswer->Wrap( -1 );
	bSizer3->Add( _staticTextAnswer, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	panelLg->SetSizer( bSizer3 );
	panelLg->Layout();
	bSizer3->Fit( panelLg );
	sbSizer1->Add( panelLg, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_buttonTextPropose = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT|wxBU_LEFT|wxNO_BORDER );
	bSizer4->Add( _buttonTextPropose, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	_textCtrlAnswer = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_PROCESS_ENTER );
	bSizer4->Add( _textCtrlAnswer, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	sbSizer1->Add( bSizer4, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer1, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextKnowledge;
	staticTextKnowledge = new wxStaticText( this, wxID_ANY, _("Knowledge :"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextKnowledge->Wrap( -1 );
	bSizer6->Add( staticTextKnowledge, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString _choiceKnowledgeChoices[] = { _("unknown"), _("little known"), _("known"), _("very known") };
	int _choiceKnowledgeNChoices = sizeof( _choiceKnowledgeChoices ) / sizeof( wxString );
	_choiceKnowledge = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choiceKnowledgeNChoices, _choiceKnowledgeChoices, 0 );
	_choiceKnowledge->SetSelection( 0 );
	bSizer6->Add( _choiceKnowledge, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer5->Add( bSizer6, 0, wxEXPAND, 5 );
	
	_buttonDelete = new wxButton( this, wxID_DELETE, _("Delete of the list"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( _buttonDelete, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	_buttonCancel = new wxButton( this, wxID_CANCEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( _buttonCancel, 1, wxALL|wxALIGN_BOTTOM, 5 );
	
	_buttonViewNext = new wxButton( this, wxID_ANY, _("View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( _buttonViewNext, 1, wxALL|wxALIGN_BOTTOM, 5 );
	
	bSizer5->Add( bSizer7, 0, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer5, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	_buttonTextPropose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickPropose ), NULL, this );
	_textCtrlAnswer->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GuiDialogActLearn::OnTextAnswer ), NULL, this );
	_textCtrlAnswer->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GuiDialogActLearn::OnTextEnterAnswer ), NULL, this );
	_choiceKnowledge->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiDialogActLearn::OnChoiceKnowledge ), NULL, this );
	_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickDelete ), NULL, this );
	_buttonViewNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickViewNext ), NULL, this );
}

GuiDialogActLearn::~GuiDialogActLearn()
{
	// Disconnect Events
	_buttonTextPropose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickPropose ), NULL, this );
	_textCtrlAnswer->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GuiDialogActLearn::OnTextAnswer ), NULL, this );
	_textCtrlAnswer->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GuiDialogActLearn::OnTextEnterAnswer ), NULL, this );
	_choiceKnowledge->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GuiDialogActLearn::OnChoiceKnowledge ), NULL, this );
	_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickDelete ), NULL, this );
	_buttonViewNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GuiDialogActLearn::OnButtonClickViewNext ), NULL, this );
	
}
