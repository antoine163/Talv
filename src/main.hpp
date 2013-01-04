//12/12/12

#ifndef MAIN_H
#define MAIN_H

#include <wx/app.h>
#include <wx/fileconf.h>

#include <map>

#include "shortcut.hpp"
#include "menuIcon.hpp"
#include "word.hpp"
#include "action.hpp"

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
		void OnShortcut(ShortcutEvent& event);
		
		//Shortcut
		void loadShortcut(wxFileConfig const& fileConfig);
	
	private:
		Shortcut *_shortcut;
		MenuIcon *_menuIcon;
		Word _word;
		
		//Association des recousis à des actions
		std::map<ShortcutKey, Action &> _shortcutAction;
};

#endif //MAIN_H
