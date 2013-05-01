//! \file **************************************************************
//! \brief Header Action de dire du texte.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 25.04.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef ACTION_SAY_H
#define ACTION_SAY_H

#include "action.hpp"
#include "action/guiPanelActSay.h"

// *********************************************************************
// Class PanelActSay
// *********************************************************************

class ActSay;

class PanelActSay : public GuiPanelActSay
{
	public:
		PanelActSay(wxWindow* parent, wxButton* buttonOK, ActSay* act);
		~PanelActSay();
		
		void OnOKButtonClick(wxCommandEvent& event);
	
	private:
		ActSay* _act;
		wxButton* _buttonOK;
};

// *********************************************************************
// Class ActSay
// *********************************************************************

class ActSay : public Action
{
	friend PanelActSay;
	
	public:
		ActSay();
		ActSay(wxString const& lgsrc);
		~ActSay();
		
		void execute();
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		wxString getStringPreferences()const;
		
	protected:
		void actLoad(wxFileConfig& fileConfig);
		void actSave(wxFileConfig& fileConfig)const;
		
	private:
		wxString _lgsrc;
};

#endif //ACTION_SAY_H
