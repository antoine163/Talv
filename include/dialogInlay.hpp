//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 08.01.2014
//!
//! ****************************************************************************

#ifndef PROXY_INFO_H
#define PROXY_INFO_H

//WxWidgets
#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/window.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/evtloop.h>

// *****************************************************************************
// Class DialogInlay
// *****************************************************************************

class DialogInlay : public wxWindow
{	
	public:
		DialogInlay(wxWindow* parent, wxString const& title);
		~DialogInlay();
		
		//wxOK, wxCANCEL, wxYES, wxNO, wxAPPLY, wxCLOSE, wxHELP, wxNO_DEFAULT.
		wxSizer* createButtonSizer (long flags);
		int showModal();
		
		int run();
		void exit(int returnCode);
		
		static wxWindow* findParent();
	
	private:
		void onButton(wxCommandEvent& event);
		
		long _buttonsFlags;
		wxGUIEventLoop* _GUIEventLoop;
};

// *****************************************************************************
// Class WithDialogInlayWindow
// *****************************************************************************

class WithDialogInlayWindow : public wxWindow
{	
	public:
		WithDialogInlayWindow(	wxWindow* parent,
								wxWindowID id,
								wxPoint const& pos=wxDefaultPosition,
								wxSize const& size=wxDefaultSize,
								long style=0,
								wxString const& name=wxPanelNameStr);
		~WithDialogInlayWindow();
		
		virtual int dialogShowModal(DialogInlay* dlg)=0;
		
	protected:
		DialogInlay* _dialogInlay;
	
	private:
};
 
// *****************************************************************************
// Class WithDialogInlayDialog
// *****************************************************************************

class WithDialogInlayDialog: public wxDialog
{	
	public:
		WithDialogInlayDialog(	wxWindow* parent,
								wxWindowID id,
								wxString const& title,
								wxPoint const& pos=wxDefaultPosition,
								wxSize const& size=wxDefaultSize,
								long style=wxDEFAULT_DIALOG_STYLE,
								wxString const& name=wxDialogNameStr);
		~WithDialogInlayDialog();
		
		virtual int dialogShowModal(DialogInlay* dlg)=0;
		
	protected:
		DialogInlay* _dialogInlay;
	
	private:
};

// *****************************************************************************
// Class WithDialogInlayFrame
// *****************************************************************************

class WithDialogInlayFrame: public wxFrame
{	
	public:
		WithDialogInlayFrame(	wxWindow* parent,
								wxWindowID id,
								wxString const& title,
								wxPoint const& pos=wxDefaultPosition,
								wxSize const& size=wxDefaultSize,
								long style=wxDEFAULT_FRAME_STYLE,
								wxString const& name=wxFrameNameStr);
		~WithDialogInlayFrame();
		
		virtual int dialogShowModal(DialogInlay* dlg)=0;
		
	protected:
		DialogInlay* _dialogInlay;
	
	private:
};

#endif //PROXY_INFO_H
