//! \file **********************************************************************
//! \brief Source DataText
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.3
//! \date 19.11.2013
//!
//! ****************************************************************************

#include "dataText.hpp"

// *****************************************************************************
// Class DataText
// *****************************************************************************

DataText::DataText()
{
	_knowledge = KNOWLEDGE_UNKNOWN;
	_weight = 0;
}

DataText::DataText(wxString const& translation)
{
	_mainTranslation = translation;
	_knowledge = KNOWLEDGE_UNKNOWN;
	_weight = 0;
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

unsigned int DataText::getWeight()const
{
	return _weight;
}

void DataText::setWeight(unsigned int weight)
{
	_weight = weight;
}

void DataText::incrementWeight(int increment)
{
	_weight += increment;
}

void DataText::clear()
{
	_mainTranslation.Clear();
	_translations.clear();
	_knowledge = KNOWLEDGE_UNKNOWN;
	_weight = 0;
}
