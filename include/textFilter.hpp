//! \file **********************************************************************
//! \brief Header 
//! 
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie
//! \version 0.1
//! \date 07.02.2014
//!
//! ****************************************************************************

#ifndef TEXT_FILTER_H
#define TEXT_FILTER_H

#include "dataText.hpp"

// *****************************************************************************
// Class TextFilter
// *****************************************************************************

class TextFilter
{
	public:
		//! \brief Constructeur.
		//! \param knowledge filtre pour inclure dans une recherche que les textes
		//! avec une certaine connaissance. Vous pouvez utiliser le \b |.
		//! Par exemple, si vous voulez récupère que les textes inconnue et
		//! connue, vous pouvez écrire : \p KNOWLEDGE_UNKNOWN \b |
		//! \p KNOWLEDGE_KNOWN
		//! \param weight filtre pour pour inclure dans une recherche que les textes
		//! \b >= à un poids. Par exemple si vous voulez
		//! récupérer que les textes avec un poids 
		//! supérieur ou égale a 7. Il vous faudra passer 7 comme argument.
		TextFilter(Knowledge_e knowledge=KNOWLEDGE_ALL, unsigned int weight=0);
		//! \brief Destructeur.
		virtual ~TextFilter();
		
		Knowledge_e getKnowledge()const;
		void setKnowledge(Knowledge_e knowledge);
		
		unsigned int getWeight()const;
		void setWeight(unsigned int weight);

	private:
		Knowledge_e _knowledge;
		unsigned int _weight;
};

#endif //TEXT_FILTER_H