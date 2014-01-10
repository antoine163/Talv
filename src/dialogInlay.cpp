//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.01.2014
//!
//! ****************************************************************************

//App
#include "dialogInlay.hpp"
#include "defs.hpp"

//WxWidgets
#include <wx/evtloop.h>
#include <wx/sizer.h>
#include <wx/button.h>

// *****************************************************************************
// Class DialogInlay
// *****************************************************************************

DialogInlay::DialogInlay(wxWindow* parent, wxString const& title)
: 	wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, title),
	_buttonsFlags(0), _GUIEventLoop(nullptr)
{
}

DialogInlay::~DialogInlay()
{
	if(_GUIEventLoop)
		delete _GUIEventLoop;
		
	if(_buttonsFlags&wxHELP)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_HELP);
	if(_buttonsFlags&wxCLOSE)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_CLOSE);
	if(_buttonsFlags&wxAPPLY)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_APPLY);
	if(_buttonsFlags&wxNO)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_NO);
	if(_buttonsFlags&wxYES)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_YES);
	if(_buttonsFlags&wxCANCEL)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_CANCEL);
	if(_buttonsFlags&wxOK)
		Unbind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_OK);
}

wxSizer* DialogInlay::createButtonSizer(long flags)
{
	if(_buttonsFlags != 0)
		return nullptr;
	
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* button = nullptr;
	_buttonsFlags = flags;
	
	if(_buttonsFlags&wxHELP)
	{
		button = new wxButton(this, wxID_HELP);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_HELP);
		sizer->Add(button, 0, wxEXPAND|wxLEFT, SIZE_BORDER);
	}
	
	sizer->AddStretchSpacer(1);
	
	if(_buttonsFlags&wxCLOSE)
	{
		button = new wxButton(this, wxID_CLOSE);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_CLOSE);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	}
	if(_buttonsFlags&wxAPPLY)
	{
		button = new wxButton(this, wxID_APPLY);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_APPLY);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	}
	if(_buttonsFlags&wxNO)
	{
		button = new wxButton(this, wxID_NO);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_NO);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	}
	if(_buttonsFlags&wxYES)
	{
		button = new wxButton(this, wxID_YES);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_YES);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	}
	if(_buttonsFlags&wxCANCEL)
	{
		button = new wxButton(this, wxID_CANCEL);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_CANCEL);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	}
	if(_buttonsFlags&wxOK)
	{
		button = new wxButton(this, wxID_OK);
		Bind(wxEVT_BUTTON, &DialogInlay::onButton, this, wxID_OK);
		sizer->Add(button, 0, wxEXPAND|wxRIGHT, SIZE_BORDER);
	} 
	
	return sizer;
}

int DialogInlay::showModal()
{
	//Recherche d'un window avec le nom "WithDialogInlay*"
	wxWindow* win = nullptr;

	//Si on a trouver on affiche le dialog grâce a se window	
	win = wxWindow::FindWindowByName("WithDialogInlayDialog");
	if(win)
		return static_cast<WithDialogInlayDialog*>(win)->dialogShowModal(this);
		
	win = wxWindow::FindWindowByName("WithDialogInlayFrame");
	if(win)
		return static_cast<WithDialogInlayFrame*>(win)->dialogShowModal(this);
		
	win = wxWindow::FindWindowByName("WithDialogInlayWindow");
	if(win)
		return static_cast<WithDialogInlayWindow*>(win)->dialogShowModal(this);

	return wxID_ANY;
}

int DialogInlay::run()
{
	_GUIEventLoop = new wxGUIEventLoop();
	int returnCode = _GUIEventLoop->Run();
	_GUIEventLoop = nullptr;
	
	return returnCode;
}

void DialogInlay::exit(int returnCode)
{
	if(_GUIEventLoop != nullptr)
		_GUIEventLoop->Exit(returnCode);
}

wxWindow* DialogInlay::findParent()
{
	//Recherche d'un window avec le nom "WithDialogInlay*"
	wxWindow* parent = nullptr;

	//Si on a trouver on affiche le dialog grâce a se window	
	parent = wxWindow::FindWindowByName("WithDialogInlayDialog");
	if(parent)
		return parent;
		
	parent = wxWindow::FindWindowByName("WithDialogInlayFrame");
	if(parent)
		return parent;
		
	parent = wxWindow::FindWindowByName("WithDialogInlayWindow");
	if(parent)
		return parent;

	return nullptr;
}

void DialogInlay::onButton(wxCommandEvent& event)
{
	if(event.GetId()&(wxID_CLOSE|wxID_NO|wxID_YES|wxID_CANCEL|wxID_OK))
		_GUIEventLoop->Exit(event.GetId());
}

// *****************************************************************************
// Class WithDialogInlayWindow
// *****************************************************************************

WithDialogInlayWindow::WithDialogInlayWindow(wxWindow* parent, wxWindowID id, wxPoint const& pos, wxSize const& size, long style, wxString const& name)
: wxWindow(parent, id, pos, size, style, name), _dialogInlay(nullptr)
{
	SetName("WithDialogInlayWindow");
}

WithDialogInlayWindow::~WithDialogInlayWindow()
{
}

// *****************************************************************************
// Class WithDialogInlayDialog
// *****************************************************************************

WithDialogInlayDialog::WithDialogInlayDialog(wxWindow* parent, wxWindowID id, wxString const& title, wxPoint const& pos, wxSize const& size, long style, wxString const& name)
: wxDialog(parent, id, title, pos, size, style, name), _dialogInlay(nullptr)
{
	SetName("WithDialogInlayDialog");
}

WithDialogInlayDialog::~WithDialogInlayDialog()
{
}

// *****************************************************************************
// Class WithDialogInlayFrame
// *****************************************************************************

WithDialogInlayFrame::WithDialogInlayFrame(wxWindow* parent, wxWindowID id, wxString const& title, wxPoint const& pos, wxSize const& size, long style, wxString const& name)
: wxFrame(parent, id, title, pos, size, style, name), _dialogInlay(nullptr)
{
	SetName("WithDialogInlayFrame");
}

WithDialogInlayFrame::~WithDialogInlayFrame()
{
}
