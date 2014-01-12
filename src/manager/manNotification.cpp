//! \file **************************************************************
//! \brief Source Gestion notification.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 1.3
//! \date 12.04.2013
//!
//! ********************************************************************

//App
#include "manager/manNotification.hpp"
#include "defs.hpp"
#include "utils.hpp"

//WxWidgets
#include <wx/window.h>
#include <wx/button.h>
#include <wx/artprov.h>
#include <wx/toplevel.h>
#include <wx/display.h>
#include <wx/utils.h> 
#include <wx/statbox.h>

#if defined(__UNIX__)
#include <libnotify/notify.h>
#include <wx/log.h> 
#include <wx/msgdlg.h>
#include <wx/rawbmp.h>
#else
#include <wx/notifmsg.h>
#endif

// *********************************************************************
// Class FrameNotification
// *********************************************************************

FrameNotification::FrameNotification(	wxString const& title,
										wxString const& message,
										long icon,
										int	maxWidth)
: wxFrame(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxFRAME_NO_TASKBAR), _timeout(this) 
{
	if(icon == wxICON_NONE)
		create(title, message, wxBitmap(), maxWidth);
	else
		create(title, message, wxArtProvider::GetBitmap(wxArtProvider::GetMessageBoxIconId(icon), wxART_MESSAGE_BOX), maxWidth);
}

FrameNotification::FrameNotification(	wxString const& title,
										wxString const& message,
										wxBitmap const& bitmap,
										int	maxWidth)
: wxFrame(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxFRAME_NO_TASKBAR), _timeout(this) 
{
	create(title, message, bitmap, maxWidth);
}

void FrameNotification::create(	wxString const& title,
								wxString const& message,
								wxBitmap const& bitmap,
								int	maxWidth)
{
	//Création du titre et du message.
	_staticTextTitle = new wxStaticText(this, wxID_ANY, wxEmptyString);
	_staticTextTitle->SetLabelMarkup("<big><b>"+title+"</b></big>");
	_staticTextMessage = new wxStaticText(this, wxID_ANY, wxEmptyString);
	_staticTextMessage->SetLabelMarkup(message);
	
	
	//Création de la statice line.
	_staticLine = new wxStaticLine(this);
	
	//Créations du wxStaticBitmap
	_staticBitmap = nullptr;
	if(bitmap.IsOk())
	{
		_staticBitmap = new wxStaticBitmap(this, wxID_ANY, bitmap);
		maxWidth -= _staticBitmap->GetSize().GetWidth()+SIZE_BORDER;
	}
	
	//Wrap le TextMessage
	_staticTextMessage->Wrap(maxWidth-5*SIZE_BORDER);
	
	//Mise en forme titre et du message avec un sizer.
	wxSizer* sizerNotification = new wxBoxSizer(wxVERTICAL);
	sizerNotification->Add(_staticTextTitle, 	0, wxEXPAND|wxLEFT, 		2*SIZE_BORDER);	
	sizerNotification->Add(_staticLine, 		0, wxEXPAND|wxTOP|wxBOTTOM,	SIZE_BORDER);	
	sizerNotification->Add(_staticTextMessage, 	0, wxEXPAND|wxLEFT, 		4*SIZE_BORDER);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);
	if(_staticBitmap != nullptr)
		sizerMain->Add(_staticBitmap, 	0, wxALIGN_CENTER|	wxLEFT|wxBOTTOM|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(sizerNotification, 	0, 					wxRIGHT|wxBOTTOM|wxTOP,	SIZE_BORDER);
	SetSizerAndFit(sizerMain);
	
	SetMaxClientSize(GetSize());
	
	//Modification de des couleurs
	SetBackgroundColour(ManNotification::get().getColourBackground());
	SetForegroundColour(ManNotification::get().getColourText());
	
	//Bind
	Bind(wxEVT_TIMER, &FrameNotification::onTimeout, this);
	_staticTextTitle->Bind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	_staticLine->Bind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	_staticTextMessage->Bind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	if(_staticBitmap)
		_staticBitmap->Bind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	Bind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
}
				
FrameNotification::~FrameNotification()
{
	//Unbind
	Unbind(wxEVT_TIMER, &FrameNotification::onTimeout, this);
	_staticTextTitle->Unbind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	_staticLine->Unbind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	_staticTextMessage->Unbind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	if(_staticBitmap)
		_staticBitmap->Unbind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
	Unbind(wxEVT_LEFT_DOWN, &FrameNotification::onLeftDown, this);
}

void FrameNotification::show(int timeout)
{
	ShowWithoutActivating();
	_timeout.Start(timeout*1000, wxTIMER_ONE_SHOT);
}

void FrameNotification::show()
{
	ShowWithoutActivating();
}

void FrameNotification::onLeftDown(wxMouseEvent&)
{
	Close();
}

void FrameNotification::onTimeout(wxTimerEvent&)
{
	Close();
}

// *****************************************************************************
// Class WinManNotification
// *****************************************************************************

WinManNotification::WinManNotification(wxWindow* parent)
: WinManager(parent, _("Notification"))	
{
	//Créations des buttons radios pour choisie le type de notification à utiliser.
	StaticBox* staticBoxPickNotification = 		new StaticBox(this, wxID_ANY, _("Use notification:"));
	_radioButtonPickNotificationNative = 		new wxRadioButton(staticBoxPickNotification, 	wxID_ANY, _("Native notification"));
	_radioButtonPickNotificationRich = 			new wxRadioButton(staticBoxPickNotification, 	wxID_ANY, _("Rich notification"));
	
	//Mise en forme des buttons radios avec un sizer.
	wxSizer* sizerPickNotification = new wxBoxSizer(wxVERTICAL);
	sizerPickNotification->Add(_radioButtonPickNotificationNative,	0, wxEXPAND|wxRIGHT|wxTOP,		SIZE_BORDER);	
	sizerPickNotification->Add(_radioButtonPickNotificationRich, 	0, wxEXPAND|wxRIGHT|wxBOTTOM, 	SIZE_BORDER);
	staticBoxPickNotification->SetSizer(sizerPickNotification);
	
	//Créations du wxStaticBox "Rich notification setting:"
	_staticBoxNotificationSetting = 		new StaticBox(this, wxID_ANY, _("Rich notification setting:"));
	wxStaticText* staticTextchoicePosition =new wxStaticText(	_staticBoxNotificationSetting, wxID_ANY, _("Choose the position where show the notifications:"));
	wxString choicePositionString[] = {_("In top to left"), _("In top to right"), _("In bottom to left"), _("In bottom to right")};
	_choicePosition = 						new wxChoice(		_staticBoxNotificationSetting, wxID_ANY, wxDefaultPosition, wxDefaultSize, 4, choicePositionString);
	_checkBoxShowNearCursor = 				new wxCheckBox(		_staticBoxNotificationSetting, wxID_ANY, _("Show the notification near cursor when is appropriate."));
	_checkBoxMultipleNotifications = 		new wxCheckBox(		_staticBoxNotificationSetting, wxID_ANY, _("Authorize to show multiple notifications."));
		
	//Créations staticTextBorder	
	wxStaticText* staticTextBorder = 		new wxStaticText(	_staticBoxNotificationSetting, wxID_ANY, _("Size of the notifications border:"));
	_spinCtrlBorder = 						new wxSpinCtrl(		_staticBoxNotificationSetting, wxID_ANY);
	
	//Mise en forme avec un sizer.
	wxFlexGridSizer* flexGridSizerNotificationSetting = new wxFlexGridSizer(2, 2, SIZE_BORDER, SIZE_BORDER);
	flexGridSizerNotificationSetting->Add(staticTextchoicePosition, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerNotificationSetting->Add(_choicePosition,			0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	flexGridSizerNotificationSetting->Add(staticTextBorder, 		0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);
	flexGridSizerNotificationSetting->Add(_spinCtrlBorder,			0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	
	
	//Créations du wxStaticBox "Pick colors:"
	StaticBox* staticBoxPickColors = new StaticBox(_staticBoxNotificationSetting, wxID_ANY, _("Pick colors:"));
	wxStaticText* staticTextBackground =new wxStaticText(		staticBoxPickColors, wxID_ANY, 	_("Pick a color for the background of notification:"));
	_colourPickerCtrlBackground = 		new wxColourPickerCtrl(	staticBoxPickColors, wxID_ANY);
	wxStaticText* staticTextText = 		new wxStaticText(		staticBoxPickColors, wxID_ANY, 	_("Pick a color for the text of notification:"));
	_colourPickerCtrlText = 			new wxColourPickerCtrl(	staticBoxPickColors, wxID_ANY);
	
	//Mise en forme du wxStaticBox "Pick colors:" avec des sizers.
	wxFlexGridSizer* flexGridSizerPickColors = new wxFlexGridSizer(2, 2, SIZE_BORDER, SIZE_BORDER);
	flexGridSizerPickColors->Add(staticTextBackground,			0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);	
	flexGridSizerPickColors->Add(_colourPickerCtrlBackground,	0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);	    
	flexGridSizerPickColors->Add(staticTextText,				0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT);	
	flexGridSizerPickColors->Add(_colourPickerCtrlText,			0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxEXPAND);
	staticBoxPickColors->SetSizer(flexGridSizerPickColors);

	//Mise en forme du wxStaticBox "Rich notification setting:" avec un sizer.
	wxSizer* sizerNotificationSetting = new wxBoxSizer(wxVERTICAL);
	sizerNotificationSetting->Add(flexGridSizerNotificationSetting,	0, wxEXPAND|wxTOP|wxRIGHT,	SIZE_BORDER);	
	sizerNotificationSetting->Add(_checkBoxShowNearCursor, 			0, wxEXPAND,				SIZE_BORDER);
	sizerNotificationSetting->Add(_checkBoxMultipleNotifications, 	0, wxEXPAND|wxBOTTOM,		SIZE_BORDER);
	sizerNotificationSetting->Add(staticBoxPickColors,				0, wxEXPAND|wxBOTTOM,		SIZE_BORDER);
	_staticBoxNotificationSetting->SetSizer(sizerNotificationSetting);
	
	//Mise en forme du GUI avec un sizer.
	wxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(staticBoxPickNotification, 		0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxTOP, 	SIZE_BORDER);	
	sizerMain->Add(_staticBoxNotificationSetting, 	0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 		SIZE_BORDER);	
	SetSizer(sizerMain);
	
	//Bind
	Bind(wxEVT_RADIOBUTTON, &WinManNotification::onRadioButtonPickNotification, this);	
}

WinManNotification::~WinManNotification()
{
	//Unbind
	Unbind(wxEVT_RADIOBUTTON, &WinManNotification::onRadioButtonPickNotification, this);
}

void WinManNotification::refreshGuiFromManager()
{
	//Sélection du bon radioButton
	switch(ManNotification::get().getUseNotification())
	{
		case USE_NOTIFICATION_NATIVE:
		_radioButtonPickNotificationNative->SetValue(true);
		_staticBoxNotificationSetting->Enable(false);
		break;
		
		case USE_NOTIFICATION_RICH:
		_radioButtonPickNotificationRich->SetValue(true);
		_staticBoxNotificationSetting->Enable();
		break;
	}
	
	_choicePosition->SetSelection(				ManNotification::get().getNotificationPosition());
	_checkBoxShowNearCursor->SetValue(			ManNotification::get().getNearCursor());
	_checkBoxMultipleNotifications->SetValue(	ManNotification::get().getMultipleNotifications());
	_spinCtrlBorder->SetValue(					ManNotification::get().getBorder());
	_colourPickerCtrlBackground->SetColour(		ManNotification::get().getColourBackground());
	_colourPickerCtrlText->SetColour(			ManNotification::get().getColourText());
}

void WinManNotification::refreshManagerFromGui()const
{
	if(_radioButtonPickNotificationNative->GetValue())
		ManNotification::get().setUseNotification(USE_NOTIFICATION_NATIVE);
	else if(_radioButtonPickNotificationRich->GetValue())
		ManNotification::get().setUseNotification(USE_NOTIFICATION_RICH);
		
	ManNotification::get().setNotificationPosition((NotificationPosition_e)_choicePosition->GetSelection());
	ManNotification::get().setNearCursor(_checkBoxShowNearCursor->GetValue());	
	ManNotification::get().setMultipleNotifications(_checkBoxMultipleNotifications->GetValue());
	ManNotification::get().setBorder(_spinCtrlBorder->GetValue());
	ManNotification::get().setColourBackground(_colourPickerCtrlBackground->GetColour());
	ManNotification::get().setColourText(_colourPickerCtrlText->GetColour());
}

void WinManNotification::onRadioButtonPickNotification(wxCommandEvent&)
{
	if(_radioButtonPickNotificationRich->GetValue())
		_staticBoxNotificationSetting->Enable();
	else
		_staticBoxNotificationSetting->Enable(false);
}

// *****************************************************************************
// Class ManNotification
// *****************************************************************************

ManNotification::ManNotification()
: 	_frameNotify(nullptr), _frameNotifyNearCursor(nullptr),
	_useNotification(USE_NOTIFICATION_RICH),
	_notificationPosition(NOTIFICATION_POSITION_TOP_RIGHT),
	_nearCursor(true), _multipleNotifications(true), _border(SIZE_BORDER),
	_colourBackground((unsigned long)0x000000), _colourText((unsigned long)0xd2d2d2)
{
	#ifdef __UNIX__
	//Initialisation de la lib Libnotify.
	if(!notify_init(PROJECT_NAME))
	{
		wxLogError(_("Libnotify could not be initialized."));
	}
	#endif
		
	_workarea = wxDisplay().GetGeometry();
}

ManNotification::~ManNotification()
{
	#ifdef __UNIX__
		//dé-initialisation de la lib Libnotify.
		notify_uninit();
	#endif
		
	//On détruis les fenêtres de notification.
	deleteAllFramesNotify();
}

IMPLEMENT_MANAGER(ManNotification);

WinManager* ManNotification::newEditWindow(wxWindow* parent)
{
	return new WinManNotification(parent);
}

void ManNotification::manLoad(wxFileConfig& fileConfig)
{
	//On détruis les fenêtres de notification au préalable.
	deleteAllFramesNotify();
	
	_useNotification = (UseNotification_e)fileConfig.ReadLong("useNotification", (long)USE_NOTIFICATION_RICH);
	_notificationPosition = (NotificationPosition_e)fileConfig.ReadLong("notificationPosition", (long)NOTIFICATION_POSITION_TOP_RIGHT);
	_nearCursor = fileConfig.ReadBool("nearCursor", true);
	_multipleNotifications = fileConfig.ReadBool("multipleNotifications", true);
	_border = fileConfig.ReadLong("border", (long)SIZE_BORDER);
		
	_colourBackground.SetRGB(fileConfig.ReadLong("colourBackground", (long)0x000000));
	_colourText.SetRGB(fileConfig.ReadLong("colourText", (long)0xd2d2d2));
	
	
	fileConfig.SetPath("workarea/");
	
	//On lie -1 pour les valeur par défaut.
	_workarea = wxDisplay().GetGeometry();
	long readVal = -1;
	
		readVal = fileConfig.ReadLong("x", -1);
		if(readVal != -1)
			_workarea.x = readVal;
			
		readVal = fileConfig.ReadLong("y", -1);
		if(readVal != -1)
			_workarea.y = readVal;
			
			
		readVal = fileConfig.ReadLong("height", -1);
		if(readVal != -1)
			_workarea.height = readVal;
		else
			_workarea.height -= _workarea.y;
			
		readVal = fileConfig.ReadLong("width", -1);
		if(readVal != -1)
			_workarea.width = readVal;
		else
			_workarea.width -= _workarea.x;
	
	fileConfig.SetPath("..");
}

void ManNotification::manSave(wxFileConfig& fileConfig)const
{	
	fileConfig.Write("useNotification", (long)_useNotification);
	fileConfig.Write("notificationPosition", (long)_notificationPosition);
	fileConfig.Write("nearCursor", _nearCursor);
	fileConfig.Write("multipleNotifications", _multipleNotifications);
	fileConfig.Write("border", (long)_border);
	
	fileConfig.Write("colourBackground", (long)_colourBackground.GetRGB());
	fileConfig.Write("colourText", (long)_colourText.GetRGB());
	
	
	fileConfig.SetPath("workarea/");
	
	//On écrit -1 pour les valeur par défaut.
	wxRect workarea = wxDisplay().GetGeometry();
	
		if(workarea.x == _workarea.x)
			fileConfig.Write("x", (long)-1);
		else
			fileConfig.Write("x", (long)_workarea.x);
		if(workarea.y == _workarea.y)
			fileConfig.Write("y", (long)-1);
		else
			fileConfig.Write("y", (long)_workarea.y);
		if(workarea.height == _workarea.height)	
			fileConfig.Write("height", (long)-1);
		else
			fileConfig.Write("height", (long)_workarea.height);
		if(workarea.width == _workarea.width)	
			fileConfig.Write("width", (long)-1);
		else
			fileConfig.Write("width", (long)_workarea.width);
	
	fileConfig.SetPath("..");
}

void ManNotification::makeSpaceFrameMultipleNotification(int spaceY)
{		
	while(_framesNotifyMultiple.size() > 0)
	{
		//Récupération de la première notification.
		FrameNotification *firstFrameNotify = _framesNotifyMultiple.front();
	
		//Récupération de la dernière notification.
		FrameNotification *lastFrameNotify = _framesNotifyMultiple.back();
	
		//Récupère la position en y et la tille en y de la dernière notification.
		int lastNotifyPositionY = lastFrameNotify->GetPosition().y;
		int lastNotifySizeY = lastFrameNotify->GetSize().y;
		
		//Vérifie si il y a besoin de supprimer une notification.
		switch(_notificationPosition)
		{
			case NOTIFICATION_POSITION_TOP_LEFT:
			case NOTIFICATION_POSITION_TOP_RIGHT:
			{				
				if(lastNotifyPositionY+lastNotifySizeY+_border+spaceY+_border <= _workarea.GetBottom())
					return;
				else
					deleteFrameMultipleNotification(firstFrameNotify);
			}break;
			
			case NOTIFICATION_POSITION_BOTTOM_LEFT:
			case NOTIFICATION_POSITION_BOTTOM_RIGHT:
			{
				if(lastNotifyPositionY-_border-spaceY-_border >= _workarea.GetTop())
					return;
				else
					deleteFrameMultipleNotification(firstFrameNotify);
			}break;
		}
	}
}

void ManNotification::deleteAllFramesNotify()
{
	for(auto it : _framesNotifyMultiple)
		delete it;
	
	if(_frameNotify != nullptr)
		delete _frameNotify;
	
	if(_frameNotifyNearCursor != nullptr)
		delete _frameNotifyNearCursor;
}

void ManNotification::placeFrameNotification(FrameNotification* frame, bool nearCursor)
{
	//Pour calculer la nouvelle position.
	wxPoint newPosition;
	
	//Récupère la tille de la notification.
	wxSize frameSize = frame->GetSize();
	
	//On doit afficher prés du curseur ?
	if(nearCursor)//Oui
	{
		wxPoint mousePosition = wxGetMousePosition();
		
		newPosition.x = mousePosition.x-frameSize.x/2.;
		newPosition.y = mousePosition.y-frameSize.y/2.;
		
		//Si la frame dépasse du cadre on la replace dans le cadre.
		if(newPosition.x+frameSize.x > _workarea.GetRight()-_border)
			newPosition.x = _workarea.GetRight()-_border-frameSize.x;
			
		if(newPosition.x < _workarea.GetLeft()+_border)
			newPosition.x = _workarea.GetLeft()+_border;
			
		if(newPosition.y+frameSize.y > _workarea.GetBottom()-_border)
			newPosition.y = _workarea.GetBottom()-_border-frameSize.y;
			
		if(newPosition.y < _workarea.GetTop()+_border)
			newPosition.y = _workarea.GetTop()+_border;
	}
	else//Non
	{
		//Variable pour calculer la position finale.
		int positionY = 0;
		int sizeY = 0;
		
		//Les notifications multiple sont activer ? ET
		//Il y a déjà d'autre notification présent ?
		if(_multipleNotifications && _framesNotifyMultiple.size() > 0)//Oui
		{
			//Récupération de la dernière notification.
			FrameNotification *lastFrameNotify = _framesNotifyMultiple.back();
			
			positionY = lastFrameNotify->GetPosition().y;
			sizeY = lastFrameNotify->GetSize().y;
		}
		else//Non
		{
			switch(_notificationPosition)
			{
				case NOTIFICATION_POSITION_TOP_LEFT:
				case NOTIFICATION_POSITION_TOP_RIGHT:
				positionY = _workarea.GetTop();
				break;
				
				case NOTIFICATION_POSITION_BOTTOM_LEFT:
				case NOTIFICATION_POSITION_BOTTOM_RIGHT:
				positionY = _workarea.GetBottom();
				break;
			}
		}
			
		//Calcul de la position.
		switch(_notificationPosition)
		{
			case NOTIFICATION_POSITION_TOP_LEFT:
			newPosition.x = 	_workarea.GetTopLeft().x+_border;
			newPosition.y = 	positionY+sizeY+_border;
			break;
			
			case NOTIFICATION_POSITION_TOP_RIGHT:
			newPosition.x = 	_workarea.GetTopRight().x-_border-frameSize.x;
			newPosition.y = 	positionY+sizeY+_border;
			break;
			
			case NOTIFICATION_POSITION_BOTTOM_LEFT:
			newPosition.x = 	_workarea.GetBottomLeft().x+_border;
			newPosition.y = 	positionY-_border-frameSize.y;
			break;
			
			case NOTIFICATION_POSITION_BOTTOM_RIGHT:
			newPosition.x = 	_workarea.GetBottomRight().x-_border-frameSize.x;
			newPosition.y = 	positionY-_border-frameSize.y;
			break;
		}
	}
	
	//Affecte la positionne calculé à la nouvelle notification.
	frame->SetPosition(newPosition);
}

void ManNotification::notify(	wxString const& title,
								wxString const& message,
								long icon,
								bool nearCursor)
{
	//3s par défaut + 1s de plus tout les 10 caractères.
	int timeout = 3+message.Length()/10;
	
	switch(_useNotification)
	{
		case USE_NOTIFICATION_NATIVE:
		{
			#ifdef __UNIX__				
				//Préparation de la notification.
				NotifyNotification * notify = notify_notification_new(title.mb_str(wxConvUTF8), message.fn_str(), nullptr);
				notify_notification_set_timeout(notify, timeout*1000);
				
				if(icon != wxICON_NONE)
				{
					//Récupération de l'icon
					wxBitmap bmpIcon(wxArtProvider::GetBitmap(wxArtProvider::GetMessageBoxIconId(icon), wxART_MESSAGE_BOX));
					
					//Ajout de l'icône a la notification.
					notify_notification_set_icon_from_pixbuf(notify, bmpIcon.GetPixbuf());
				}
				
				
				//Affichage de la notification
				if(!notify_notification_show(notify, nullptr))
				{
					//Si problème
					wxLogError(_("The notify with libnotify could not be show."));
					wxLogMessage(_("The richs notifications go to use now."));
					wxMessageDialog dlg(nullptr, _("The notify with libnotify could not be show.\nThe richs notifications go to use now."),
										wxMessageBoxCaptionStr, wxOK|wxCENTRE|wxICON_INFORMATION);
					dlg.ShowModal();
									
					setUseNotification(USE_NOTIFICATION_RICH);
				}
				
				g_object_unref(G_OBJECT(notify));
			#else
				//Préparation de la notification.
				wxNotificationMessage notify(title, message);
				if(icon != wxICON_NONE)
					notify.SetFlags(icon);
				//Affichage de la notification
				notify.Show(timeout);
			#endif
		}break;
		
		case USE_NOTIFICATION_RICH:
		{
			//Création de la fenêtre de notification.
			FrameNotification *newFrameNotify = new FrameNotification(title, message, icon, _workarea.GetWidth()-2*_border);
				
			//On doit afficher la position près du curseur ?
			if(_nearCursor && nearCursor)
			{
				//Place la nouvelle notification au bonne endroit sur l'écran.
				placeFrameNotification(newFrameNotify, true);
				
				//On supprime au préalable l'ancienne notification.
				if(_frameNotifyNearCursor != nullptr)
					delete _frameNotifyNearCursor;
				//Et on y met la nouvelle.
				_frameNotifyNearCursor = newFrameNotify;
			}
			//A la suit de celle déjà existante ?
			else if(_multipleNotifications)
			{
				//Faire de la place.
				makeSpaceFrameMultipleNotification(newFrameNotify->GetSize().y);
				
				//Place la nouvelle notification au bonne endroit sur l'écran.
				placeFrameNotification(newFrameNotify, false);
			
				//Ajout de la notification à la pile.
				_framesNotifyMultiple.push_back(newFrameNotify);
			}
			//On doit afficher qu'une notification ?
			else
			{
				//Place la nouvelle notification au bonne endroit sur l'écran.
				placeFrameNotification(newFrameNotify, false);
			
				//On supprime au préalable l'ancienne notification.
				if(_frameNotify != nullptr)
					delete _frameNotify;
				//Et on y met la nouvelle.
				_frameNotify = newFrameNotify;
			}
				
			//Lier l'évènement de fermeture de la notification.
			newFrameNotify->Bind(wxEVT_CLOSE_WINDOW, &ManNotification::onCloseFrameNotification, this);
			//Enfin, affiche la notification.
			newFrameNotify->show(timeout);
		}break;
	}
}

void ManNotification::onCloseFrameNotification(wxCloseEvent& event)
{
	//Obtenir la (frame) notification qui a provoquer l'événement.
	FrameNotification* frameNotify = static_cast<FrameNotification*>(event.GetEventObject());
	
	//Unbind l'évènement de la notification.
	frameNotify->Unbind(wxEVT_CLOSE_WINDOW, &ManNotification::onCloseFrameNotification, this);
	
	//Supprime la notification.
	if(_frameNotify == frameNotify)
	{
		delete _frameNotify;
		_frameNotify = nullptr;
	}
	else if(_frameNotifyNearCursor == frameNotify)
	{
		delete _frameNotifyNearCursor;
		_frameNotifyNearCursor = nullptr;
	}
	else
		deleteFrameMultipleNotification(frameNotify);
}

void ManNotification::deleteFrameMultipleNotification(FrameNotification* frameNotify)
{	
	//Récupération de la tiller de la notification.
	wxSize frameNotifySize = frameNotify->GetSize();
	
	//Parcoure tout les notification actifs
	int iFrameNotify = -1;
	for(unsigned int i = 0; i<_framesNotifyMultiple.size(); i++)
	{
		//Si la notification a été trouver.
		if(iFrameNotify != -1)
		{
			//On décale les notifications qui se trouve après.
			wxPoint pos = _framesNotifyMultiple[i]->GetPosition();
			
			//Calcul de la nouvelle position.
			switch(_notificationPosition)
			{
				case NOTIFICATION_POSITION_TOP_LEFT:
				case NOTIFICATION_POSITION_TOP_RIGHT:
				pos.y -= frameNotifySize.y+_border;
				break;
				
				case NOTIFICATION_POSITION_BOTTOM_LEFT:
				case NOTIFICATION_POSITION_BOTTOM_RIGHT:
				pos.y += frameNotifySize.y+_border;
				break;
			}
			
			//Applique la nouvelle position.
			_framesNotifyMultiple[i]->SetPosition(pos);
		}
		//c'est la notification que l'on cherche ?
		else if(_framesNotifyMultiple[i] == frameNotify)
		{
			//On retiens sont index dans le vector
			iFrameNotify = i;
		}
	}
	
	//On détruis la notification
	delete _framesNotifyMultiple[iFrameNotify];
	//Et on l'enlève du vector
	_framesNotifyMultiple.erase(_framesNotifyMultiple.begin()+iFrameNotify);
}

UseNotification_e ManNotification::getUseNotification()
{
	return _useNotification;
}

void ManNotification::setUseNotification(UseNotification_e val)
{
	_useNotification = val;
}

NotificationPosition_e ManNotification::getNotificationPosition()
{
	return _notificationPosition;
}

void ManNotification::setNotificationPosition(NotificationPosition_e pos)
{
	_notificationPosition = pos;
}

bool ManNotification::getNearCursor()
{
	return _nearCursor;
}

void ManNotification::setNearCursor(bool val)
{
	_nearCursor = val;
}

bool ManNotification::getMultipleNotifications()
{
	return _multipleNotifications;
}

void ManNotification::setMultipleNotifications(bool val)
{
	_multipleNotifications = val;
}

int ManNotification::getBorder()
{
	return _border;
}

void ManNotification::setBorder(int border)
{
	_border = border;
}

wxColour ManNotification::getColourBackground()
{
	return _colourBackground;
}

void ManNotification::setColourBackground(wxColour const& colour)
{
	_colourBackground = colour;
}

wxColour ManNotification::getColourText()
{
	return _colourText;
}

void ManNotification::setColourText(wxColour const& colour)
{
	_colourText = colour;
}

