//! \file **************************************************************
//! \brief Header Gestion notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.1
//! \date 12.04.2013
//!
//! ********************************************************************

#ifndef MAN_NOTIFICATION_H
#define MAN_NOTIFICATION_H

//App
#include "manager.hpp"

//WxWidgets
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/bitmap.h>
#include <wx/gdicmn.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/statbmp.h>

// *****************************************************************************
// Enum UseNotification_e
// *****************************************************************************
enum UseNotification_e
{
	USE_NOTIFICATION_NATIVE=0,
	USE_NOTIFICATION_RICH
};

// *****************************************************************************
// Enum NotificationPosition_e
// *****************************************************************************
enum NotificationPosition_e
{
	NOTIFICATION_POSITION_TOP_LEFT=0,
	NOTIFICATION_POSITION_TOP_RIGHT,
	NOTIFICATION_POSITION_BOTTOM_LEFT,
	NOTIFICATION_POSITION_BOTTOM_RIGHT
};

// *********************************************************************
// Class FrameNotification
// *********************************************************************

//! \brief Fenêtre de notification.
class FrameNotification : public wxFrame
{	
	public:
		//! \brief Constructeur.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param icon l'icône a afficher. Seul les valeurs \b wxICON_NONE ou
		//! \b wxICON_ERROR ou \b wxICON_INFORMATION ou \b wxICON_WARNING peut
		//! être passer en paramètre.
		FrameNotification(	wxString const& title,
							wxString const& message,
							long icon = wxICON_NONE);
							
		//! \brief Constructeur.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param bitmap le bitmap a afficher.
		FrameNotification(	wxString const& title,
							wxString const& message,
							wxBitmap const& bitmap);
							
		//! \brief Destructeur.
		~FrameNotification();
		
		//! \brief Afficher la notification.
		//! \param timeout est le temps d'affichage de la notification en second.
		void show(int timeout);
		
		//! \brief Afficher la notification.
		void show();
	
	protected:
		//! \brief Appeler l'ordre d'un clique gauche sur la fenêtre.
		void OnLeftDown(wxMouseEvent& event);
		//! \brief Appeler a la fin du temps écouler par le timer.
		void OnTimeout(wxTimerEvent& event);
	
	private:
		//! \brief Créations de la notification.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param bitmap le bitmap a afficher.
		void Create(	wxString const& title,
						wxString const& message,
						wxBitmap const& bitmap);
							
		//! \brief Timer de la notification.
		wxTimer _timeout;
		
		wxStaticText* _staticTextTitle;
		wxStaticLine* _staticLine;
		wxStaticText* _staticTextMessage;
		wxStaticBitmap* _staticBitmap;
};

// *****************************************************************************
// Class WinManNotification
// *****************************************************************************

class WinManNotification : public WinManager
{
	public:
		WinManNotification(wxWindow* parent);
		~WinManNotification();
		
		virtual void refreshGuiFromManager();
		virtual void refreshManagerFromGui()const;
	
	private:
		void onRadioButtonPickNotification(wxCommandEvent& event);
		
		wxRadioButton* _radioButtonPickNotificationNative;
		wxRadioButton* _radioButtonPickNotificationRich; 
		
		wxStaticBox* _staticBoxNotificationSetting;
		wxChoice* _choicePosition;
		wxCheckBox* _checkBoxShowNearCursor;
		wxCheckBox* _checkBoxMultipleNotifications;
		wxSpinCtrl* _spinCtrlBorder;
		wxColourPickerCtrl* _colourPickerCtrlBackground;
		wxColourPickerCtrl* _colourPickerCtrlText;
};

// *****************************************************************************
// Class ManNotification
// *****************************************************************************

//! \ingroup manager
//! \brief ManNotification
class ManNotification : public Manager
{
	DECLARE_MANAGER(ManNotification);
	
	public:
		virtual WinManager* newEditWindow(wxWindow* parent);
		
		void notify(	wxString const& title,
						wxString const& message,
						long icon = wxICON_NONE,
						bool nearCursor = false);

		//Configuration
		UseNotification_e getUseNotification();
		void setUseNotification(UseNotification_e val);
		NotificationPosition_e getNotificationPosition();
		void setNotificationPosition(NotificationPosition_e pos);
		bool getNearCursor();
		void setNearCursor(bool val);
		bool getMultipleNotifications();
		void setMultipleNotifications(bool val);
		int getBorder();
		void setBorder(int border);
		wxColour getColourBackground();
		void setColourBackground(wxColour const& colour);
		wxColour getColourText();
		void setColourText(wxColour const& colour);
	
	private:
		virtual void manLoad(wxFileConfig& fileConfig);
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		//Dans spaceY il n'est pas néssaiser d'ajouter les bordure
		void makeSpaceFrameMultipleNotification(int spaceY);
		//Cette méthode vérifie si les notifications multiple sont activer.
		//En notifications multiple il ne faut pas que la notification soi ajouter 
		// a _framesNotifyMultiple aven l'appelle de cette méthode.
		//! \bug des fois quand on demande a plein de notification de s'afficher 
		//! elle ne se positionne pas o bonne endroit.
		void placeFrameNotification(FrameNotification* frame, bool nearCursor);
		
		void onCloseFrameNotification(wxCloseEvent& event);
		void deleteFrameMultipleNotification(FrameNotification* frameNotify);
		
		void deleteAllFramesNotify();
		
		std::vector<FrameNotification*> _framesNotifyMultiple;
		FrameNotification* _frameNotify;
		FrameNotification* _frameNotifyNearCursor;
		
		//Configuration
		UseNotification_e _useNotification;
		NotificationPosition_e _notificationPosition;
		bool _nearCursor;
		bool _multipleNotifications;
		int _border;
		wxColour _colourBackground;
		wxColour _colourText;
		
		wxRect _workarea;
};

#endif //MAN_NOTIFICATION_H
