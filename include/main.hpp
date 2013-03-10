//12/12/12
//version : 1.0

#ifndef MAIN_H
#define MAIN_H

#include <wx/app.h>

#include "menuIcon.hpp"

class App : public wxApp
{
	public:				
		virtual bool OnInit();
		virtual int OnExit();
		
		//Menu Item Methode
		void creatMenuItem();
		void deleteMenuItem();
		
		//Menu Item Event Methode
		void OnPreferences(wxCommandEvent&);
		void OnEnable(wxCommandEvent& event);
		void OnAbout(wxCommandEvent&);
		void OnExit(wxCommandEvent&);
	
	private:
		MenuIcon *_menuIcon;
};

DECLARE_APP(App);

#endif //MAIN_H
