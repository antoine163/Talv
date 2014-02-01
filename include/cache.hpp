//! \file **********************************************************************
//! \brief Header Cache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.2
//! \date 16.11.2013
//!
//! ****************************************************************************

#ifndef CACHE_H
#define CACHE_H

//App
#include "dataText.hpp"
#include "fileText.hpp"

//Stl
#include <map>

//WxWidgets
#include <wx/filename.h>
#include <wx/file.h>

// *****************************************************************************
// Class Cache
// *****************************************************************************

//! \brief Manipulation de donnée de texte.
//!
//! Cette classe permet de manipuler un fichier contenant des données de textes.
//!
//! Pour crée un cache vous devais commencer par renseigner le non du fichier
//! avec \ref setFileName(). Ensuit vous dévirez appeler \ref setLanguages() dans 
//! quele cas le fichier ne sera pas crée sur le disque.
class Cache : public FileText
{
	public:		
		//! \brief Constructeur.
		Cache();
				
		//! \brief Destructeur.
		virtual ~Cache();
		
		//! \brief Savoir si un texte est déjà existent dans le fichier.
		//! \param text Le texte rechercher.
		//! \return \ref STATUS_TEXT_EXIST, \ref STATUS_TEXT_NO_EXIST, 
		//! \ref STATUS_FILE_OPEN_FAILED, \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e existText(wxString const& text)const;
		
		//! \brief Ajout un texte et c'est données à la liste si il
		//! n'est pas déjà existent.
		//! \param text le texte à ajouter.
		//! \param dataText les données du texte à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_TEXT_EXIST, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e addText(wxString const& text, DataText const& dataText);
		
		//! \brief Mise a jour des données d'un texte.
		//! \param text le texte à mètre à jour.
		//! \param dataText les nouvelle données du texte.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_TEXT_NO_EXIST, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e updateText(wxString const& text, DataText const& dataText);
		
		//! \brief Remplace touts les textes et leur données pas de nouveaux.
		//! \param texts les textes et données à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e replaceTexts(std::map<wxString, DataText> const& texts);
		
		//! \brief Obtenir tout les textes (sent les données) contenue
		//! dans le fichier.
		//! \param texts là où seront stoker les texte.
		//! Ce paramètre ne doit pas être nullptr.
		//! \param KnowledgeFilter filtre pour récupérer que les textes
		//! avec une certaine connaissance. Vous pouvez utiliser le \b |.
		//! Par exemple, si vous voulez récupère que les textes inconnue et
		//! connue, vous pouvez écrire : \p KNOWLEDGE_UNKNOWN \b |
		//! \p KNOWLEDGE_KNOWN
		//! \param nbTranslationFilter filtre pour récupérer que les textes
		//! \b >= à un nombre de traduction. Par exemple si vous voulez
		//! récupérer que les textes avec un nombre de traductions 
		//! supérieur ou égale a 7. Il vous faudra passer 7 comme argument.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED, 
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e getTexts(	wxArrayString* texts,
							Knowledge_e KnowledgeFilter = KNOWLEDGE_ALL,
							unsigned int nbTranslationFilter = 0)const;
							
		//! \brief Obtenir tout les textes contenue dans le fichier.
		//! \param texts là où seront stoker les texte et les données.
		//! Ce paramètre ne doit pas être nullptr.
		//! \param KnowledgeFilter filtre pour récupérer que les textes
		//! avec une certaine connaissance. Vous pouvez utiliser le \b |.
		//! Par exemple, si vous voulez récupère que les textes inconnue et
		//! connue, vous pouvez écrire : \p KNOWLEDGE_UNKNOWN \b |
		//! \p KNOWLEDGE_KNOWN
		//! \param nbTranslationFilter filtre pour récupérer que les textes
		//! \b >= à un nombre de traduction. Par exemple si vous voulez
		//! récupérer que les textes avec un nombre de traductions 
		//! supérieur ou égale a 7. Il vous faudra passer 7 comme argument.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED, 
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()
		Status_e getTextsAndData(	std::map<wxString, DataText>* texts,
									Knowledge_e KnowledgeFilter = KNOWLEDGE_ALL,
									unsigned int nbTranslationFilter = 0)const;		
					
		//! \brief Obtenir les données d'un textes contenue dans le fichier.
		//! \param texts le texte rechercher.
		//! \param data les données du texte. Ce paramètre de doit pas être a nullptr.
		//! \return \ref STATUS_SUCCESS, , \ref STATUS_TEXT_NO_EXIST, \ref STATUS_FILE_OPEN_FAILED, 
		//! \ref STATUS_FILE_READ_ERROR, \ref STATUS_FILE_NO_NAME
		//!
		//! - Si \ref STATUS_FILE_NO_NAME vous devriez appeler \ref setFileName()										
		Status_e getData(wxString const& text, DataText* data)const;								
	protected:
		//! \brief Ajoute des textes et leur données au cache.
		//! Ne vérifie pas si les textes son déjà existent.
		//! \param texts les text et leur données à ajouter.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_OPEN_FAILED,
		//! \ref STATUS_FILE_WRITE_ERROR, \ref STATUS_FILE_NO_NAME
		virtual Status_e addTexts(std::map<wxString, DataText> const& texts);
		
		//! \brief Cherche l'offset d'un texte et de c'est données dans
		//! un fichier.
		//!
		//! Le fichier devra déjà être ouvert en lecture. 
		//! \param file Le fichier où cherche les offsets.
		//! \param text le texte a rechercher.
		//! \param offsetText Là où sera stoker l'offset où se trouve le 
		//! texte. Vous pouvez passer nullptr si l'informations ne vous
		//!intéresse pas.
		//! \param offsetDataText Là où sera stoker l'offset où se trouve le 
		//! les données du texte. Vous pouvez passer nullptr si
		//! l'informations ne vous intéresse pas.
		//! \return \ref STATUS_TEXT_EXIST, \ref STATUS_TEXT_NO_EXIST, \ref STATUS_FILE_READ_ERROR
		//!
		//! \note La valeur des offsets peuvent avoir été modifier même si le texte
		//! na pas été trouver.
		//! 
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après les données (l'octet
		//! juste après la fin des données. Si il y a un texte après
		//! les données alors le curseur pointera dessus. Sa peut être
		//! aussi la fin du fichier).
		virtual Status_e findOffsetTextAndDataTextInFile(	wxFile& file,
															wxString const& text,
															wxFileOffset* offsetText,
															wxFileOffset* offsetDataText)const;
		
		//! \brief Lis les données d'un texte a partir du curseur
		//! actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en lecture. 
		//! \param file Le fichier où lire les données du texte.
		//! \param data là ou sera stoker le résulta de la lecture.
		//! Doit être un pointeur valide.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_READ_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après les données (l'octet
		//! juste après la fin des données sa peut être aussi la fin
		//! du fichier).
		virtual Status_e readDataTextInFile(wxFile& file,
											DataText* data)const;
											
		//! \brief Lis les une parti des données d'un texte a partir du
		//! curseur actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en lecture. 
		//! \param file Le fichier où lire les données du texte.
		//! \param dataKnowledge là ou sera stoker la connaissance.
		//! Doit être un pointeur valide.
		//! \param nbTranslation là ou sera stoker le nombre de traductions.
		//! Doit être un pointeur valide.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_READ_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après les données (l'octet
		//! juste après la fin des données sa peut être aussi la fin
		//! du fichier).
		virtual Status_e readDataTextInFile(wxFile& file, 
											Knowledge_e* dataKnowledge,
											unsigned int* nbTranslation)const;
		
		//! \brief Écrire les données d'un texte a partir du curseur
		//! actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en écriture. 
		//! \param file Le fichier où écrire les données.
		//! \param data les données à écrie.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_WRITE_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après les données (l'octet
		//! juste après les données sa peut être aussi la fin du fichier).
		virtual Status_e writeDataTextInFile(	wxFile& file, 
												DataText const& data);
												
		//! \brief Écrire une partir des données d'un texte a partir
		//! du curseur actuelle du fichier.
		//!
		//! Le fichier devra déjà être ouvert en écriture et lecture. 
		//! \param file Le fichier où écrire le texte.
		//! \param dataKnowledge la connaissance a écrier.
		//! \param dataNbTranslation le nombre d traduction a écrier.
		//! \return \ref STATUS_SUCCESS, \ref STATUS_FILE_READ_ERROR,
		//! \ref STATUS_FILE_WRITE_ERROR
		//!
		//! Après l'appelle de cette méthode, le curseur du fichier
		//! pointera sur là position juste après les données (l'octet
		//! juste après les données sa peut être aussi la fin du fichier).
		virtual Status_e writeDataTextInFile(	wxFile& file,
												Knowledge_e dataKnowledge,
												unsigned int dataNbTranslation);
	private:
};

#endif //CACHE_H
