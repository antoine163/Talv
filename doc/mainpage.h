//! \file **********************************************************************
//!
//! \brief main page de la documentation du code du logicielle flydocs.
//!
//! - Compilateur : GCC,MinGW
//!
//! \author Antoine Maleyrie.
//! \version 0.2
//! \date 13/12/12
//!
//! ****************************************************************************

/*
*	Copyright © 2012-2013 - Antoine Maleyrie.
*/

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

//! \mainpage flydocs
//! Documentation du code de flydocs.
//!
//! <b>Website</b> \n <a href="http://antoine163.github.com/flydocs/">http://antoine163.github.com/flydocs/</a>
//! 
//! \author Antoine Maleyrie : antoine.maleyrie@gmail.com
//! \version  1.0
//!
//! \page pageCreateAction Création d'une nouvelle action.
//! \tableofcontents
//! \section pageCreateActionSectionExemple Exemple avec la classe ActSay.
//! Ci dessous est décrit une procédure pour écrire une nouvelle action. On prendras comme exemple la class \ref ActSay.
//!
//! \subsection pageCreateActionSubsectionCreateFiles Création des fichiers.
//! On va commencer par créé deux fichiers dans le répertoire action se trouvent dans include et src.
//! Dans notre cas (avec la class \ref ActSay), on crée le fichier include/action/actSay.hpp et src/action/actSay.cpp
//!
//! A ce state les fichier devrais ressembler a ceci :
//! - actSay.hpp
//!  \verbinclude actSayNewFile.hpp
//! - actSay.cpp
//!  \verbinclude actSayNewFile.cpp
//!
//! \subsection pageCreateActionSubsectionCreateClass Création des classes.
//! Pour implémenter une action correctement on a besoint de crée deux classe.
//! - Une pour gérais l'action en elle même, sauvegarde et chargement des paramètre et exécution de l'action en question.
//! - Et une autre, qui est en fait un panel pour que l'utilisateur configure sont action graphiquement.
//! \subsubsection pageCreateActionSubsubsectionCreateClassAction Création de l'action.
//! Tout action doit hériter de la classe \ref Action et implémenter ces méthodes virtuelle pur.
//! On doit aussi prévoir un constructeur par défaut qui initialiseras la classe avec une configuration par défaut.
//! On peut prévoir un constructeur prenant des paramètres pour la configuration de l'action.
//! Et au besoin un destructeur.
//!
//! Voila a quoi devrai ressemble n'autre classe ActSay (avec quelle que explication sur les différent méthode):
//! - actSay.hpp
//!  \include actSayNewClassActSay.hpp
//! - actSay.cpp
//!  \include actSayNewClassActSay.cpp
//! \subsubsection pageCreateActionSubsubsectionCreateClassPanel Création du panel de configuration.
//! Dans un premier temps, on va faire ça simplement et on va juste crée les bases de la classe.
//! Si on se réfère \ref Action::getPanelPreferences(wxWindow* parent, wxButton* buttonOK).
//! On constate les deux paramètres \p parent et \p buttonOK. Il va donc falloir que l'on construise n'autre panel
//! autour wxWindow parent qui est en fait le dialog de configuration des actions.
//! Le paramètre \p buttonOK et le bouton ok du dialogue parent. On peut l'utiliser pour récupérer les événements de se bouton.
//! Quand l'utilisateur clique sur ce bouton il et bon de vérifier si les paramètres configurais par l'utilisateur sont correcte.
//! Dans le cas contraire on peut afficher un message lui indique ce qu'il ne vas pas.
//!
//! \subsection pageCreateActionSubsectionLink Prise en compte de l'action dans le projet.
//! texte ...
//!
//! \subsection pageCreateActionSubsectionFirstTest Premier test.
//! texte ...
//!
//! \subsection pageCreateActionSubsectionCreateGUI Création du GUI.
//! texte ...



#endif // MAIN_PAGE_H

