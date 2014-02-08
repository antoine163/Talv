//! \file **********************************************************************
//! \brief Source.
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

//App
#include "textFilter.hpp"

// *****************************************************************************
// Class TextFilter
// *****************************************************************************

TextFilter::TextFilter(Knowledge_e knowledge, unsigned int weight)
: _knowledge(knowledge), _weight(weight)
{
}

TextFilter::~TextFilter()
{
}

Knowledge_e TextFilter::getKnowledge()const
{
	return _knowledge;
}

void TextFilter::setKnowledge(Knowledge_e knowledge)
{
	_knowledge = knowledge;
}

unsigned int TextFilter::getWeight()const
{
	return _weight;
}

void TextFilter::setWeight(unsigned int weight)
{
	_weight = weight;
}
