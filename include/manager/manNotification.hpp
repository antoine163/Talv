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
#include <wx/sizer.h>
#include <wx/radiobut.h>
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
	USE_NOTIFICATION_NATIVE=0,	//!< Utilisation des notification native a la plate-forme.
	USE_NOTIFICATION_RICH		//!< Utilisation les notification propre a l'application.
};

// *****************************************************************************
// Enum NotificationPosition_e
// *****************************************************************************
enum NotificationPosition_e
{
	NOTIFICATION_POSITION_TOP_LEFT=0,	//!< Position des notifications commencent a s'afficher en haut a gauche.
	NOTIFICATION_POSITION_TOP_RIGHT,	//!< Position des notifications commencent a s'afficher en haut a droit.
	NOTIFICATION_POSITION_BOTTOM_LEFT,	//!< Position des notifications commencent a s'afficher en bas a gauche.
	NOTIFICATION_POSITION_BOTTOM_RIGHT	//!< Position des notifications commencent a s'afficher en bas a droit.
};

// *********************************************************************
// Class FrameNotification
// *********************************************************************

//! \brief Fenêtre de notification.
//! \see ManNotification
class FrameNotification : public wxFrame
{	
	public:
		//! \brief Constructeur.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param icon l'icône à afficher. Seul les valeurs \b wxICON_NONE ou
		//! \b wxICON_ERROR ou \b wxICON_INFORMATION ou \b wxICON_WARNING peut
		//! être passer en paramètre.
		FrameNotification(	wxString const& title,
							wxString const& message,
							long icon = wxICON_NONE);
							
		//! \brief Constructeur.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param bitmap le bitmap à afficher.
		FrameNotification(	wxString const& title,
							wxString const& message,
							wxBitmap const& bitmap);
							
		//! \brief Destructeur.
		~FrameNotification();
		
		//! \brief Afficher la notification.
		//! \param timeout est le temps d'affichage de la notification en second.
		void show(int timeout);
		
		//! \brief Afficher la notification sans timeout.
		void show();
	
	protected:
		//! \brief Callback appeler l'ordre d'un clique gauche sur la fenêtre.
		//! Se qui aura pour effet de fermer la fenêtre.
		void onLeftDown(wxMouseEvent& event);
		//! \brief Callback appeler à la fin du temps écouler par le timer.
		//! Se qui aura pour effet de fermer la fenêtre.
		void onTimeout(wxTimerEvent& event);
	
	private:
		//! \brief Créations de la notification.
		//! \param title est le titre de la notification.
		//! \param message est le message de la notification.
		//! \param bitmap le bitmap a afficher.
		void create(	wxString const& title,
						wxString const& message,
						wxBitmap const& bitmap);
							
		//! \brief Timer de la notification.
		wxTimer _timeout;
		
		//Élément graphique.
		wxStaticText* _staticTextTitle;
		wxStaticLine* _staticLine;
		wxStaticText* _staticTextMessage;
		wxStaticBitmap* _staticBitmap;
};

// *****************************************************************************
// Class WinManNotification
// *****************************************************************************

//! \brief Fenêtre de configuration du manager de notification \ref ManNotification.
class WinManNotification : public WinManager
{
	public:
		//! \brief Constructeur.
		//! \param parent parent de la fenêtre.
		WinManNotification(wxWindow* parent);
		//! \brief Destructeur.
		~WinManNotification();
		
		//! \brief Rafraîchie les composants qui constitues le GUI
		//! avec les données provenant du manager \ref ManNotification.
		virtual void refreshGuiFromManager();
		//! \brief Rafraîchie le manager \ref ManNotification avec les données
		//! provenant des composants qui constitues le GUI.
		virtual void refreshManagerFromGui()const;
	
	private:
		//! \brief Callback appeler l'osque  un bouton Radio a été cliquet.
		//! Se qui aura pour effet d'activer ou pas les paramètre pour les
		//! NotificationRich.
		void onRadioButtonPickNotification(wxCommandEvent& event);
		
		//Élément graphique.
		wxRadioButton* _radioButtonPickNotificationNative;
		wxRadioButton* _radioButtonPickNotificationRich; 
		wxSizer* _sizerNotificationSetting;
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
//! \brief Manager pour la gestion des notifications.
//! \see WinManNotification
//! \see FrameNotification
class ManNotification : public Manager
{
	DECLARE_MANAGER(ManNotification);
	
	public:
		//! \brief Permet de crées un nouveau gui pour configurer le manager.
		//! \see WinManNotification
		virtual WinManager* newEditWindow(wxWindow* parent);
		
		//! \brief Gêner une notification.
		//! Pour le \p title et le \p message vous pouvez utiliser le maquillage
		//! (markup) voir http://docs.wxwidgets.org/stable/classwx_control.html#afeb308dc3b54d8d735b33cb250395503 .
		//! \param title le titre de la notification.
		//! \param message le message de la notification.
		//! \param icon l'icône à afficher. Seul les valeurs \b wxICON_NONE ou
		//! \b wxICON_ERROR ou \b wxICON_INFORMATION ou \b wxICON_WARNING peut
		//! être passer en paramètre.
		//! \param nearCursor si vous voulez que la notification soi afficher près du curseur.
		//! Se paramètre et pris en compte seulement si la configuration du manager le permet.
		//! \see getNearCursor()
		//! \see setNearCursor()
		void notify(	wxString const& title,
						wxString const& message,
						long icon = wxICON_NONE,
						bool nearCursor = false);

		//! @name Configuration
		//! @{
		
		//! \brief Pour connaître le type de notification utiliser.
		UseNotification_e getUseNotification();
		
		//! \brief Pour modifier le type de notification utiliser.
		void setUseNotification(UseNotification_e val);
		
		//! \brief Pour connaître la position où s'affiner le notification.
		NotificationPosition_e getNotificationPosition();
		
		//! \brief Pour modifier la position où s'affiner le notification.
		void setNotificationPosition(NotificationPosition_e pos);
		
		//! \brief Pour connaître si le manager permet de d'afficher les
		//! notifications prés du curseur.
		bool getNearCursor();
		
		//! \brief Pour permet ou pas au manager d'afficher les notifications
		//! prés du curseur.
		void setNearCursor(bool val);
		
		//! \brief Pour connaître si le manager permet de d'afficher plusieurs
		//! notifications.
		bool getMultipleNotifications();
		
		//! \brief Pour permet ou pas au manager d'afficher les plusieurs
		//! notifications.
		void setMultipleNotifications(bool val);
		
		//! \brief Pour connaître la taille de la bordure.
		int getBorder();
		
		//! \brief Pour modifier la taille de la bordure.
		void setBorder(int border);
		
		//! \brief Pour connaître la couleur de fond des notifications.
		wxColour getColourBackground();
		
		//! \brief Pour modifier la couleur de fond des notifications.
		void setColourBackground(wxColour const& colour);
		
		//! \brief Pour connaître la couleur du texte des notifications.
		wxColour getColourText();
		
		//! \brief Pour modifier la couleur du texte des notifications.
		void setColourText(wxColour const& colour);
		
		//! @} //Configuration
	
	private:
		//! \brief Pour charger la configuration du manager a partir d'un
		//! fichier.
		virtual void manLoad(wxFileConfig& fileConfig);
		//! \brief Pour sauvegarder la configuration du manager a partir d'un
		//! fichier.
		virtual void manSave(wxFileConfig& fileConfig)const;
		
		//! \brief Pour faire de la place dans la liste des notification multiple.
		//! Cette méthode commence par supprimer les plus ancienne notification.
		//! \param spaceY est l'espace à faire en pixels. Les bordures sont
		//! ajouter a spaceY il n'est donc pas utile de les inclures dedans.
		void makeSpaceFrameMultipleNotification(int spaceY);
		
		//! \brief Pour positionner une notification dans l'écran.
		//! 
		//! Cette méthode vérifie si les notifications multiple sont activer.
		//! En notifications multiple il ne faut pas que la notification soi ajouter 
		//! a _framesNotifyMultiple aven l'appelle de cette méthode.
		//! \param frame la notification a plaser.
		//! \param nearCursor true pour positionner la notification près du curseur.
		//! Se paramètre et pris en compte seulement si la configuration du manager le permet.
		//! \see getNearCursor()
		//! \see setNearCursor()
		//!
		//! \bug des fois quand on demande a plein de notification de s'afficher 
		//! elle ne se positionne pas o bonne endroit.
		void placeFrameNotification(FrameNotification* frame, bool nearCursor);
		
		//! \brief Callback appeler l'osque qu'une notification est fermer.
		//! Cela aura pour effet de supprimer complément la notification qui
		//! viens d'être fermer.
		void onCloseFrameNotification(wxCloseEvent& event);
		
		//! \brief Pour supprimer un notification qui est dans la liste Multiple
		//! notification. Cela a aussi pour effet de décaler tout les autres notification,
		//! pour qu'il n'y est pas de trou a l'écran.
		//! \param frameNotify la notification a supprimer.
		void deleteFrameMultipleNotification(FrameNotification* frameNotify);
		
		//! \brief Supprime tout les notifications active.
		void deleteAllFramesNotify();
		
		//Variables pour grader en mémoire les pointeur des notification active.
		std::vector<FrameNotification*> _framesNotifyMultiple;
		FrameNotification* _frameNotify;
		FrameNotification* _frameNotifyNearCursor;
		
		//Variables pour grader en mémoire la configuration du manager.
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
