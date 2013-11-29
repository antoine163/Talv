//! \file **************************************************************
//! \brief Source DataText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 19.11.2013
//!
//! ********************************************************************

/*
*	Copyright © 2013 - Antoine Maleyrie.
*/

#include "dataText.hpp"

// *********************************************************************
// Class DataText
// *********************************************************************

DataText::DataText()
{
	_knowledge = KNOWLEDGE_UNKNOWN;
	_nbTranslation = 0;
}

DataText::DataText(wxString const& translation)
{
	_mainTranslation = translation;
	_knowledge = KNOWLEDGE_UNKNOWN;
	_nbTranslation = 0;
}

DataText::~DataText()
{
}

wxString DataText::getMainTranslation()const
{
	return _mainTranslation;
}

void DataText::setMainTranslation(wxString const& translation)
{
	_mainTranslation = translation;
}

std::map<wxString, wxArrayString> const& DataText::getTranslations()const
{
	return _translations;
}

wxArrayString DataText::getTranslations(wxString const& nature)const
{
	if(_translations.count(nature) == 0)
		return wxArrayString();
		
	return _translations.at(nature);
}
wxArrayString DataText::getNatures()const
{
	wxArrayString tmpArrayString;
	
	for(auto& it: _translations)
		tmpArrayString.Add(it.first);
  
  return tmpArrayString;
}

void DataText::addTranslation(wxString const& nature, wxString const& translation)
{
	_translations[nature].Add(translation);
}

Knowledge_e DataText::getKnowledge()const
{
	return _knowledge;
}

void DataText::setKnowledge(Knowledge_e knowledge)
{
	_knowledge = knowledge;
}

unsigned int DataText::getNbTranslation()const
{
	return _nbTranslation;
}

void DataText::setNbTranslation(unsigned int nbTranslation)
{
	_nbTranslation = nbTranslation;
}

void DataText::incrementNbTranslation()
{
	_nbTranslation++;
}

void DataText::clear()
{
	_mainTranslation.Clear();
	_translations.clear();
	_knowledge = KNOWLEDGE_UNKNOWN;
	_nbTranslation = 0;
}
