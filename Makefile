########################################################################
#
#	Makfile.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	1.0
# - date 	:	24/11/2012
#
########################################################################


########################################################################
# Paramètre généraux.
########################################################################
#Non du projet
PROJECT_NAME=\"flydocs\"
#Numéro de version
PROJECT_VERSION=\"1.0\"


########################################################################
# Action à compiler.
########################################################################
#Traduction du mot/phrase
ACT_TRANSLATION=yes
#Sovgarde de la raduction du mot/phrase
ACT_SAVE_TRANSLATION=no
#Dire le mot/phrase
ACT_SAY=no
#Lance une application
ACT_RUN=no

########################################################################
# Utiliser libnotify pour les notifications. (Option réserver pour unix)
########################################################################
USE_LIBNOTIFY=yes


########################################################################
# Compilateur et flags C++.
########################################################################
#Compilateur
CXX=g++
#Option de compilation généraux
CXX_FLAGS=-W -Wall -Wextra -std=gnu++11
#Flage en plus pour la compilation en release.
CXX_FLAGS_RELESE=-s -O2
#Flage en plus pour la compilation en debug.
CXX_FLAGS_DEBUG=-g


########################################################################
# Exportation de tout les variables dans les makefiles enfants.
########################################################################
export


########################################################################
# Détection de l'os (Pas de détection pour le moment, mais un simple
# passage d'augment permer de compiler pour les différence os supporter.
# ex pour windows: make release OS_NAME=msw).
########################################################################
OS_NAME=unix


########################################################################
# Par défaut la compilation release est active.
########################################################################
all:release


########################################################################
# Compilation en release.
########################################################################
release:
	@cd $(OS_NAME) && $(MAKE) release
	
########################################################################
# Compilation en debug.
########################################################################
debug:
	@cd $(OS_NAME) && $(MAKE) debug
	
	
########################################################################
# Exécute le programme
########################################################################
.PHONY: run
run:
	@cd $(OS_NAME) && $(MAKE) run
	
	
########################################################################
# Exécute le programme avec gdb.
########################################################################
.PHONY: rungdb
rungdb:	
ifeq ($(OS_NAME),msw)
	@echo "Sorry, run gdb is not possible."
else
	@cd $(OS_NAME) && $(MAKE) rungdb
endif
	
	
########################################################################
# Génération de la doc.
########################################################################
.PHONY: doc
doc:
ifeq ($(OS_NAME), msw)
	@echo "Sorry, the build of documentation is not possible."
else
	@cd $(OS_NAME) && $(MAKE) doc
endif
	
########################################################################
# Supprime la doc générée.
########################################################################
.PHONY: cleandoc
cleandoc:
ifeq ($(OS_NAME),msw)
	@echo "Sorry, the cleaning of documentation is not possible."
else
	@cd $(OS_NAME) && $(MAKE) cleandoc
endif
	
	
########################################################################
# Nettoyage du projet.
########################################################################
.PHONY: clean
clean:
	@cd $(OS_NAME) && $(MAKE) clean
