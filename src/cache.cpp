//! \file **********************************************************************
//! \brief Source Cache
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 16.11.2013
//!
//! ****************************************************************************

//App
#include "cache.hpp"

// *****************************************************************************
// Class Cache
// *****************************************************************************

Cache::Cache()
{
}

Cache::~Cache()
{
}

Status_e Cache::existText(wxString const& text)const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
		
	Status_e valReturn = findOffsetTextAndDataTextInFile(file, text, nullptr, nullptr);
		
	file.Close();
	return valReturn;
}

Status_e Cache::addText(wxString const& text, DataText const& dataText)
{
	Status_e valReturn = existText(text);
	
	if(valReturn != STATUS_TEXT_NO_EXIST)
		return valReturn;
	
	std::map<wxString, DataText> texts;
	texts[text] = dataText;
	return addTexts(texts);
}

Status_e Cache::updateText(wxString const& text, DataText const& dataText)
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read_write))
		return STATUS_FILE_OPEN_FAILED;
		
	//On cherche le texte
	wxFileOffset offsetText;
	wxFileOffset offsetDataText;
	Status_e valReturn = findOffsetTextAndDataTextInFile(file, text, &offsetText, &offsetDataText);
	if(valReturn != STATUS_TEXT_EXIST)
	{
		file.Close();
		return valReturn;
	}
	
	//On récupère les données du texte.
	DataText tmpDataText;
	valReturn = readDataTextInFile(file, &tmpDataText);
	if(valReturn != STATUS_SUCCESS)
	{
		file.Close();
		return valReturn;
	}
	
	//Compare si les traductions du nouveau dataText est identique avec
	//l'ancien (celui que l'on viens de lire)
	if(	dataText.getMainTranslation() == tmpDataText.getMainTranslation() &&
		dataText.getTranslations() == tmpDataText.getTranslations())
	{
		//Si comparaison égale on récrit juste la connaissance et le
		//nombre de traduction.
		file.Seek(offsetDataText);
		valReturn = writeDataTextInFile(file, 	dataText.getKnowledge(),
												dataText.getNbTranslation());
	}
	else
	{
		wxMemoryBuffer topFile;
		wxMemoryBuffer bottomFile;
		size_t sizeRead;
		
		//Mis en buffer du bas du fichier
		sizeRead = file.Length() - file.Tell();
		if((size_t)file.Read(bottomFile.GetWriteBuf(sizeRead), sizeRead) != sizeRead)
		{
			file.Close();
			return STATUS_FILE_READ_ERROR;
		}
		bottomFile.UngetWriteBuf(sizeRead);
		
		//Mis en buffer du haut du fichier
		sizeRead = offsetText;
		file.Seek(0);
		if((size_t)file.Read(topFile.GetWriteBuf(sizeRead), sizeRead) != sizeRead)
		{
			file.Close();
			return STATUS_FILE_READ_ERROR;
		}
		topFile.UngetWriteBuf(sizeRead);
		
		//On ferme le fichier et on en crée un nouveau.
		file.Close();
		if(!file.Create(_fileName.GetFullPath(), true))
			valReturn = STATUS_FILE_CREATE_FAILED;
		else
		{
			//On écris les données précédemment lu (mais bien sur sen le
			//texte que le doit supprimer).
			
			size_t sizeWrite = topFile.GetDataLen();
			if(file.Write(topFile.GetData(), sizeWrite) != sizeWrite)
			{
				file.Close();
				return STATUS_FILE_WRITE_ERROR;
			}
			
			sizeWrite = bottomFile.GetDataLen();
			if(file.Write(bottomFile.GetData(), sizeWrite) != sizeWrite)
			{
				file.Close();
				return STATUS_FILE_WRITE_ERROR;
			}
			
			//On fini par écrire le texte et les données du texte.
			valReturn = writeStringInFile(file, text);
			if(valReturn != STATUS_SUCCESS)
			{
				file.Close();
				return valReturn;
			}
	
			valReturn = writeDataTextInFile(file, dataText);
		}
	}
	
	file.Close();
	return valReturn;
}


Status_e Cache::replaceTexts(std::map<wxString, DataText> const& texts)
{
	wxString lgsrc;
	wxString lgto;
	Status_e valReturn = getLanguages(&lgsrc, &lgto);
	if(valReturn != STATUS_SUCCESS)
		return valReturn;
		
	wxFileName tmpFileName = _fileName;
	
	valReturn = clear();
	if(valReturn != STATUS_SUCCESS)
		return valReturn;
	
	_fileName = tmpFileName;
	
	valReturn = setLanguages(lgsrc, lgto);
	if(valReturn != STATUS_SUCCESS)
		return valReturn;
	
	return addTexts(texts);
}

Status_e Cache::getTexts(	wxArrayString* texts,
							Knowledge_e KnowledgeFilter,
							unsigned int nbTranslationFilter)const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
		
	Status_e valReturn = filePointerAfterHeader(file);
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier.
	wxString tmpText;
	Knowledge_e tmpDataTextKnowledge = KNOWLEDGE_UNKNOWN;
	unsigned int tmpDataTextnbTranslation = 0;
	while(valReturn == STATUS_SUCCESS && !file.Eof())
	{
		valReturn = readStringInFile(file, &tmpText);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		valReturn = readDataTextInFile(file, 	&tmpDataTextKnowledge,
												&tmpDataTextnbTranslation);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		//Ajout le texte lus si ok avec les filtres.
		if(	tmpDataTextKnowledge & KnowledgeFilter &&
			tmpDataTextnbTranslation >= nbTranslationFilter)
		{
			texts->Add(tmpText);
		}
	}
		
	file.Close();
	return valReturn;
}

Status_e Cache::getTextsAndData(	std::map<wxString, DataText>* texts,
									Knowledge_e KnowledgeFilter,
									unsigned int nbTranslationFilter)const
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::read))
		return STATUS_FILE_OPEN_FAILED;
		
	Status_e valReturn = filePointerAfterHeader(file);
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier.
	wxString tmpText;
	DataText tmpDataText;
	while(valReturn == STATUS_SUCCESS && !file.Eof())
	{
		valReturn = readStringInFile(file, &tmpText);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		tmpDataText.clear();
		valReturn = readDataTextInFile(file, &tmpDataText);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		//Ajout le texte lus si ok avec les filtres.
		if(	tmpDataText.getKnowledge() & KnowledgeFilter &&
			tmpDataText.getNbTranslation() >= nbTranslationFilter)
		{
			(*texts)[tmpText] = tmpDataText;
		}
	}
		
	file.Close();
	return valReturn;
}

Status_e Cache::addTexts(std::map<wxString, DataText> const& texts)
{
	if(!_fileName.HasName())
		return STATUS_FILE_NO_NAME;
		
	wxFile file;
	if(!file.Open(_fileName.GetFullPath(), wxFile::write_append))
		return STATUS_FILE_OPEN_FAILED;
		
	Status_e valReturn = STATUS_SUCCESS;
	for(auto& it: texts)
	{
		
		//Écriture du texte.
		valReturn = writeStringInFile(file, it.first);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		//Écriture des données du texte.
		valReturn = writeDataTextInFile(file, it.second);
		if(valReturn != STATUS_SUCCESS)
			break;
	}
		
	file.Close();
	return valReturn;
}

Status_e Cache::findOffsetTextAndDataTextInFile(	wxFile& file,
													wxString const& text,
													wxFileOffset* offsetText,
													wxFileOffset* offsetDataText)const
{
	Status_e valReturn = filePointerAfterHeader(file);
	
	//On lie les textes tend que la lecture réussi et que l'on
	//est pas arriver a la fin du fichier.
	wxString tmpText;
	while(valReturn == STATUS_SUCCESS && !file.Eof())
	{	
		//On mémorise l'offset du texte.
		if(offsetText != nullptr)
			*offsetText = file.Tell();
		
		//Lecture du texte.
		valReturn = readStringInFile(file, &tmpText);
		if(valReturn != STATUS_SUCCESS)
			break;
			
		//On mémorise l'offset des données du texte.
		if(offsetDataText != nullptr)
			*offsetDataText = file.Tell();
			
		//C'est le texte que l'on recherche ?
		if(tmpText == text)
		{
			valReturn = STATUS_TEXT_EXIST;
			break;
		}
			
		uint16_t totalSize;
		//Lecture de la taille totale.
		if(file.Read(&totalSize, sizeof totalSize) != sizeof totalSize)
		{
			valReturn = STATUS_FILE_READ_ERROR;
			break;
		}
		
		//On saut au texte suivent.
		file.Seek((wxFileOffset)totalSize, wxFromCurrent);
	}
	
	//Si SUCCESS c'est que le texte n'a pas été trouver.
	if(valReturn == STATUS_SUCCESS)
		valReturn = STATUS_TEXT_NO_EXIST;
	
	return valReturn;
}

Status_e Cache::readDataTextInFile(wxFile& file, DataText* data)const
{
	wxFileOffset fileOffsetStartData = file.Tell();
	
	uint16_t totalSize;
	
	//Lecture de la taille totale.
	if(file.Read(&totalSize, sizeof totalSize) != sizeof totalSize)
		return STATUS_FILE_READ_ERROR;
	
	//Lecture de la connaissance.
	Knowledge_e knowledge;
	if(file.Read((uint8_t*)&knowledge, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_READ_ERROR;
	data->setKnowledge(knowledge);
	
	//Lecture du nombre de traduction.
	unsigned int nbTranslation;
	if(file.Read((uint8_t*)&nbTranslation, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_READ_ERROR;
	data->setNbTranslation(nbTranslation);
		
	//Lecture de la traduction principale.
	wxString mainTranslation;
	if(readStringInFile(file, &mainTranslation) != STATUS_SUCCESS)
		return STATUS_FILE_READ_ERROR;
	data->setMainTranslation(mainTranslation);
			
	//Lecture des autres traductions.
	wxString tmpNature;
	wxString tmpTranslation;
	while(file.Tell() - (fileOffsetStartData+2) < totalSize)
	{
		//Lecture du nombre de traduction dans une nature.
		uint8_t nbTrInNature;
		if(file.Read(&nbTrInNature, sizeof nbTrInNature) != sizeof nbTrInNature)
			return STATUS_FILE_READ_ERROR;
						
		//Nature
		if(readStringInFile(file, &tmpNature) != STATUS_SUCCESS)
			return STATUS_FILE_READ_ERROR;
					
		//Traductions
		for(int8_t i = 0; i < nbTrInNature; i++)
		{
			if(readStringInFile(file, &tmpTranslation) != STATUS_SUCCESS)
				return STATUS_FILE_READ_ERROR;
			
			data->addTranslation(tmpNature, tmpTranslation);
		}
	}

	return STATUS_SUCCESS;
}

Status_e Cache::readDataTextInFile(wxFile& file, 	Knowledge_e* dataKnowledge,
													unsigned int* nbTranslation)const
{
	wxFileOffset fileOffsetStartData = file.Tell();
	uint16_t totalSize;
	
	//Lecture de la taille totale.
	if(file.Read(&totalSize, sizeof totalSize) != sizeof totalSize)
		return STATUS_FILE_READ_ERROR;
	
	//Lecture de la connaissance.
	if(file.Read((uint8_t*)dataKnowledge, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_READ_ERROR;
	
	//Lecture du nombre de traduction.
	if(file.Read((uint8_t*)nbTranslation, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_READ_ERROR;
		
	//Positionne le curseur sur le prochain texte ou la fin du fichier.
	file.Seek(fileOffsetStartData+2+totalSize);

	return STATUS_SUCCESS;
}
									
Status_e Cache::writeDataTextInFile(wxFile& file, DataText const& data)
{	
	//Taille de la connaissance + tailler du nombre de traduction traduit.
	uint16_t totalSize = 1+1;
	
	//Taille de la traduction principale
	totalSize += 1+strlen(data.getMainTranslation().fn_str());
	
	//Taille des autre traductions.
	auto traductions = data.getTranslations();
	for(auto &itNature: traductions)
	{
		totalSize += 1+1+strlen(itNature.first.fn_str());
		for(auto &it: itNature.second)
			totalSize += 1+strlen(it.fn_str());
	}
	
	//Écriture de la taille totale.
	if(file.Write(&totalSize, sizeof totalSize) != sizeof totalSize)
		return STATUS_FILE_WRITE_ERROR;
		
	//Écriture de la connaissance.
	Knowledge_e knowledge = data.getKnowledge();
	if(file.Write((uint8_t*)&knowledge, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_WRITE_ERROR;
	
	//Écriture du nombre de traduction.
	unsigned int nbTranslation = data.getNbTranslation();
	if(file.Write((uint8_t*)&nbTranslation, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_WRITE_ERROR;
		
	//Écriture de la traduction principale.
	if(writeStringInFile(file, data.getMainTranslation()) != STATUS_SUCCESS)
		return STATUS_FILE_WRITE_ERROR;
		
	//Écriture des autres traductions.
	auto translations = data.getTranslations();
	for(auto &itNature: translations)
	{
		//Nombre de traductions dans une nature.
		uint8_t nbTrInNature = itNature.second.GetCount();
		if(file.Write(&nbTrInNature, sizeof nbTrInNature) != sizeof nbTrInNature)
			return STATUS_FILE_WRITE_ERROR;
		
		//Nature
		if(writeStringInFile(file, itNature.first) != STATUS_SUCCESS)
			return STATUS_FILE_WRITE_ERROR;

		//Traductions
		for(auto &it: itNature.second)
		{
			if(writeStringInFile(file, it) != STATUS_SUCCESS)
				return STATUS_FILE_WRITE_ERROR;
		}
	}
	
	return STATUS_SUCCESS;
}

Status_e Cache::writeDataTextInFile(wxFile& file, 	Knowledge_e dataKnowledge,
													unsigned int dataNbTranslation)
{
	wxFileOffset fileOffsetStartData = file.Tell();
	uint16_t totalSize;
	
	//Lecture de la taille totale.
	if(file.Read(&totalSize, sizeof totalSize) != sizeof totalSize)
		return STATUS_FILE_READ_ERROR;
	
	//Écriture de la connaissance.
	if(file.Write((uint8_t*)&dataKnowledge, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_WRITE_ERROR;
	
	//Écriture du nombre de traduction.
	if(file.Write((uint8_t*)&dataNbTranslation, sizeof(uint8_t)) != sizeof(uint8_t))
		return STATUS_FILE_WRITE_ERROR;
		
	//Positionne le curseur sur le prochain texte ou la fin du fichier.
	file.Seek(fileOffsetStartData+2+totalSize);
	
	return STATUS_SUCCESS;
}

