//! \file **************************************************************
//! \brief Header ListBase
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 17.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#ifndef LIST_BASE_H
#define LIST_BASE_H

#include <wx/string.h>
#include <wx/filename.h>

// *********************************************************************
// Class ListBase
// *********************************************************************

//! \brief Manipulation d'une liste.
//!
//! Temps que vous ne spécifier pas de fichier ( avec \ref setFileName() )
//! tout est stoker dans la mémoire ram. Au contraire, si 
//! vous spécifier un n'on de fichier avec \ref setFileName(), dans ce
//! cas tout est sont stoker dans le fichier spécifier. \n
//! Vous pouvez appeler la méthode \ref setFileName() avec comme argument
//! \b wxFileName() qui aura pour effet de passer au mode sans fichier.
class ListBase
{
	public:		
		//! \brief Constructeur par défaut.
		ListBase();
				
		//! \brief Destructeur.
		virtual ~ListBase();
		
		//! \brief Obtenir les langages de la liste.
		//! \param lgsrc le langage source sera stoker dans cette variable.
		//! \param lgto le langage de destinassions sera stoker dans
		//! cette variable.
		void getLanguages(wxString* lgsrc, wxString* lgto)const;
		
		//! \brief Modifier les langages de la liste.
		//! \attention Cette méthode et utilisable seulement si la liste
		//! est vide (vous pouvez utiliser \ref isEmpty()), a la
		//! création ou après un \ref clear() par exemple. Vous pouvez
		//! vérifier en appellent \ref getLanguages().
		//! \return true si les langes ont put être changés.
		bool setLanguages(wxString const& lgsrc, wxString const& lgto);
		
		//! \brief Pour savoir si la liste est vide ou pas.
		bool isEmpty()const;
		
		//! \brief Suppression de tous les textes et de leur fichier associer.
		//! 
		//! Si un non de fichier à été spécifier avec \ref setFileName() ,
		//! alors se fichier sera aussi supprimer du disque dur.
		void clear();
		
		//! \brief Suppression d'un texte.
		//! \param text texte à supprimer.
		//! \return true si le texte a put être supprimer.
		//! false si le texte n'existe pas ou problème sur le fichier.
		bool removeText(wxString const& text);
		
		//! \brief Pour savoir si un texte existe.
		//! \param text texte à chercher.
		//! \return true si le texte existe.
		bool existText(wxString const& text)const;
		
		//! \brief Charger la lite à partir d'un fichier.
		//!
		//! Si vous avez au préalable spécifier un fichier avec
		//! \ref setFileName() , alors le contenue du fichier spécifier
		//! sera remplacer par le contenue du fichier passer en
		//! paramètre à cette méthode ( \p file).
		//! \param file fichier à partir du quel les données seront charger.
		//! \return false si problème avec le fichier.
		bool load(wxFileName const& fileName);
		//! \brief Sauvegarder la lite dans un fichier.
		//! \param file fichier où serons stoker les données.
		//! \return false si problème avec le fichier.
		bool save(wxFileName const& fileName)const;
		
		//! \brief Obtenir le non de fichier.
		wxFileName getFileName()const;
		//! \brief Attribuer un fichier à la liste.
		//!
		//! Après cette appelle de méthode, toutes les opérations se
		//! ferons dans le fichier et non pas dans la mémoire.
		//! Si il y a, au préalable des données dans la liste, elle serons
		//! perdue. De nouvelle données serons charger à partir 
		//! du fichier évidement si il y en existe et le langage sera
		//! aussi charger.
		//!
		//! Dans le cas inverse, si vous passez \b wxFileName()
		//! (mode sans fichier) toutes les opération se ferons dans la ram.
		//! Si il y a, au préalable des données dans la liste, elle serons
		//! aussi perdue (elle resterons écrite dans le fichier).
		virtual void setFileName(wxFileName const& fileName);
		
	protected:
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref isEmpty() appellera cette méthode.
		//! \see isEmpty()
		virtual bool isEmptyFile()const=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref isEmpty() appellera cette méthode.
		//! \see isEmpty()
		virtual bool isEmptyMemory()const=0;
		
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref clear() appellera cette méthode.
		//! \see clear()
		virtual void clearFile()=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref clear() appellera cette méthode.
		//! \see clear()
		virtual void clearMemory()=0;
		
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref removeText() appellera cette méthode.
		//! \see removeText()
		virtual bool removeTextFile(wxString const& text)=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref removeText() appellera cette méthode.
		//! \see removeText()
		virtual bool removeTextMemory(wxString const& text)=0;
		
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref existText() appellera cette méthode.
		//! \see existText()
		virtual bool existTextFile(wxString const& text)const=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref existText() appellera cette méthode.
		//! \see existText()
		virtual bool existTextMemory(wxString const& text)const=0;
		
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref load() appellera cette méthode.
		//! \see load()
		virtual bool loadFile(wxFileName const& fileName)=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref load() appellera cette méthode.
		//! \see load()
		virtual bool loadMemory(wxFileName const& fileName)=0;
		
		//! \brief Dans le cas ou il y a un fichier spécifier la méthode
		//! \ref save() appellera cette méthode.
		//! \see save()
		virtual bool saveFile(wxFileName const& fileName)const=0;
		//! \brief Dans le cas ou il n'y a pas de fichier spécifier la méthode
		//! \ref save() appellera cette méthode.
		//! \see save()
		virtual bool saveMemory(wxFileName const& fileName)const=0;
		
	
		//! \brief Fichier de la liste.
		wxFileName _fileName;
		//! \brief Langage source de la liste.
		wxString _lgsrc;
		//! \brief Langage de destination de la liste.
		wxString _lgto;
};

#endif //LIST_BASE_H
