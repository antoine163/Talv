// *********************************************************************
// Class ActSay
// *********************************************************************

class ActSay : public Action
{	
	public:
		//Le constructeur par défaut qui doit prévoir une configuration par défaut.
		//Il faut que n'autre action soit fonctionnelle rien que-en créent une instance de notre classe.
		ActSay();
		//Le constructeur qui prend en paramètre tout les configurations, dans notre cas on en n'a qu'un.
		ActSay(wxString const& lgsrc);
		//Ici le destructeur n'est pas vraiment utile. A voir donc en fonction de l'implémentation de vautre action.
		~ActSay();
		
		//C'est peut être la méthode la plus importe. Elle est appeler par le programme lorsque celui-ci veux exécuter l'action
		void execute();
		//Ici, vous devais fournir un panel qui sera présenter a l'utilisateur du programme pour configurer l'action.
		//A par a la création, il y a que deux manière de modifier les paramètres de l'action.
		//Le wxPanel sera capable de modifier les paramètre de vautre classe, (Voir plus loin pour l'implémentation).
		wxPanel* getPanelPreferences(wxWindow* parent, wxButton* buttonOK);
		//Vois devais fournier une version texte et simplifier des paramètre de configuration de votre action.
		wxString getStringPreferences()const;
		
	protected:
		//Le wxFileConfig doit être utiliser pour charger vaux paramètre.
		//C'est la deuxième manière de modifier les paramètres de l'action.
		void actLoad(wxFileConfig& fileConfig);
		//Le wxFileConfig doit être utiliser pour enregistre vaux paramètre.
		void actSave(wxFileConfig& fileConfig)const;
		
	private:
		//Ici, le seul paramètre que l'on a à stoker est le langage dans le quelle on dois dire le texte (voir la méthode execute).
		wxString _lgsrc;
};
