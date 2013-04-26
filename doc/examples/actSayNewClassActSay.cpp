// *********************************************************************
// Class ActSay
// *********************************************************************

//Par défaut la classe sera fonctionnelle pour dire du texte en anglais ("en").
ActSay::ActSay()
: ActSay("en")
{
}

//On avec les paramètre a l'action
ActSay::ActSay(wxString const& lgsrc)
: Action(						//On appel le constructeur de la classe maire.
_("Say text"),					//Le nom de l'action que verra l'utilisateur.
"ActSay",						//Le nom de la classe (non vu par l'utilisateur)
_("Say a text with google.")) 	//On brève description de l'action.
{
	_lgsrc = lgsrc;
}

//Rien a faire dans notre cas.
ActSay::~ActSay()
{
}

//Pour le moment on va se contenter d'afficher un message. Pour voir quand la méthode est exécuter. 
void ActSay::execute()
{
	std::cout << "ActSay::execute" << std::endl;
}

//Voir la section suivent pour l'implantation.
wxPanel* ActSay::getPanelPreferences(wxWindow* parent, wxButton* buttonOK)
{
	//...
}

//On retourne une version simplifier et textuelle des paramètre.
wxString ActSay::getStringPreferences()const
{
	//Ici on fais intervenir les ressources, pour convertir notre paramètre ("en") en une version plus compréhensible pour l'utilisateur ("Anglais").
	return _("Say Text in ") + Resource::getInstance()->abbreviationToLanguage(_lgsrc);
}

//sauvegarde de touts les paramètres
void ActSay::actLoad(wxFileConfig & fileConfig)
{
	//Encore une fois, ici on a que langage dans le quelle on dois dire le texte qui doit être sauvegarder.
	fileConfig.Read("lgsrc", &_lgsrc);
}

//On charge et donc on modifie n'aux paramètres.
void ActSay::actSave(wxFileConfig & fileConfig)const
{
	fileConfig.Write("lgsrc", _lgsrc);
}
