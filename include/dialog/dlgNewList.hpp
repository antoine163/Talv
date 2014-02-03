//! \file **********************************************************************
//! \brief Header
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 03.02.2014
//!
//! ****************************************************************************

#ifndef DLG_NEW_LIST_H
#define DLG_NEW_LIST_H

//App
#include "dialogInlay.hpp"
#include "control/ctrlPickLanguages.hpp"

//WxWidgets
#include <wx/intl.h>
#include <wx/textctrl.h>

// *****************************************************************************
// Class DlgNewList
// *****************************************************************************

class DlgNewList : public DialogInlay 
{
	public:
		//! \brief Constructeur.
		DlgNewList(wxWindow* parent);
		//! \brief Destructeur.
		~DlgNewList();
		
		wxString getNameList()const;
		void getLanguages(wxLanguage *lgsrc, wxLanguage *lgto)const;
		
	private:
		wxTextCtrl* _textCtrlNameList;
		CtrlPickLanguages* _ctrlPickLanguages;
};

#endif //DLG_NEW_LIST_H
