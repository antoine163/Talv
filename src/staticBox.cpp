//! \file **********************************************************************
//! \brief Source
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 10.01.2014
//!
//! ****************************************************************************

//App
#include "staticBox.hpp"
#include "defs.hpp"
#include "utils.hpp"

//WxWidgets
#include <wx/statline.h>
#include <wx/colour.h>

// *****************************************************************************
// Class StaticBox
// *****************************************************************************

StaticBox::StaticBox(wxWindow *parent, wxWindowID id, const wxString &label, bool withCheckBox, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxWindow(parent, id, pos, size, style, name), _sizerMain(nullptr), _sizerWork(nullptr), _checkBox(nullptr)
{	
	//Création de la statice line.
	wxStaticLine* staticLine = new wxStaticLine(this);
	
	//Création du wxStaticText ou wxCheckBox.
	_staticText = new wxStaticText(this, wxID_ANY, wxEmptyString);
	_staticText->SetLabelMarkup("<b>"+label+"</b>");
	
	//Mise en forme du label avec la ligne avec un sizer.
	_sizerLabel = new wxBoxSizer(wxHORIZONTAL);
	_sizerLabel->Add(_staticText,	0, wxALIGN_CENTER_VERTICAL);
	_sizerLabel->Add(staticLine, 	1, wxALIGN_CENTER_VERTICAL|wxLEFT, SIZE_BORDER);
	
	//Création ou wxCheckBox.
	if(withCheckBox)
	{
		_checkBox = new wxCheckBox(this, wxID_ANY, wxEmptyString);
		_checkBox->SetValue(true);
		_sizerLabel->Prepend(_checkBox,	0, wxALIGN_CENTER_VERTICAL);
		
		//Bind
		_staticText->Bind(wxEVT_LEFT_UP, &StaticBox::onClick, this);
		_checkBox->Bind(wxEVT_CHECKBOX, &StaticBox::onCheck, this);
		
	}
	
	//Mise en forme du StaticBox avec un sizer.
	_sizerMain = new wxBoxSizer(wxVERTICAL);
	_sizerMain->Add(_sizerLabel, 0, wxEXPAND);
	wxWindow::SetSizer(_sizerMain);
}

StaticBox::~StaticBox()
{
	//Unbind
	if(_checkBox)
	{
		_staticText->Unbind(wxEVT_LEFT_UP, &StaticBox::onClick, this);
		_checkBox->Unbind(wxEVT_CHECKBOX, &StaticBox::onCheck, this);
	}
}

bool StaticBox::IsChecked()
{
	if(_checkBox)
		return _checkBox->IsChecked();
		
	return true;
}

void StaticBox::setChecked(bool val)
{
	if(_checkBox)
	{
		if(val == IsChecked())
			return;
			
		_checkBox->SetValue(val);
			
		if(_sizerWork && IsEnabled())
			enableWindowsFromSizer(_sizerWork, val);
	}
}

void StaticBox::SetSizer(wxSizer* sizer, bool deleteOld)
{
	if(deleteOld && _sizerWork)
		delete _sizerWork;
		
	_sizerWork = sizer;
	_sizerMain->Add(_sizerWork, 1, wxEXPAND|wxLEFT, 4*SIZE_BORDER);
}

bool StaticBox::Enable(bool enable)
{
	if(enable == IsThisEnabled())
        return false;

    m_isEnabled = enable;

	enableWindowsFromSizer(_sizerLabel, enable);
	
	if(IsChecked())
		enableWindowsFromSizer(_sizerWork, enable);

    return true;
}

void StaticBox::onClick(wxMouseEvent& event)
{
	if(_checkBox && _sizerWork)
	{
		if(_checkBox->IsChecked())
		{
			_checkBox->SetValue(false);
			enableWindowsFromSizer(_sizerWork, false);
		}
		else
		{
			_checkBox->SetValue(true);
			enableWindowsFromSizer(_sizerWork, true);
		}
	}
	
	event.Skip();
}

void StaticBox::onCheck(wxCommandEvent& event)
{
	if(_checkBox->IsChecked())
		enableWindowsFromSizer(_sizerWork, true);
	else
		enableWindowsFromSizer(_sizerWork, false);
		
	event.Skip();
}

