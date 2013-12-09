################################################################################
#
#	Makfile.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	1.7
# - date 	:	24/11/2012
#
################################################################################


################################################################################
# Paramètre généraux.
################################################################################
#Non du projet
PROJECT_NAME=Talv
#Numéro de version
PROJECT_VERSION=0.3


################################################################################
# Détection de l'os (Pas de détection pour le moment, mais un simple
# passage d'augment permer de compiler pour les différence os supporter.
# ex pour windows: make release OS_NAME=msw).
################################################################################
OS_NAME=unix


################################################################################
# Compilateur et flags C++.
################################################################################
#Compilateur
CXX=g++
#Option de compilation généraux
CXX_FLAGS=-W -Wall -Wextra -std=gnu++11
CXX_FLAGS+=-Wno-unused-local-typedefs
#Flage en plus pour la compilation en release.
CXX_FLAGS_RELESE=-s -O2
#Flage en plus pour la compilation en debug.
CXX_FLAGS_DEBUG=-g

################################################################################
# Define à propos de l'application.
################################################################################
# Non du projet
DEFINE=PROJECT_NAME=\"$(PROJECT_NAME)\"
# Numéro de version
DEFINE+=PROJECT_VERSION=\"$(PROJECT_VERSION)\"

################################################################################
# Define pour faciliter le développement
################################################################################
# Vous pouvez passer DEV_RUN_START_PREFERENCES à DEV_DEFINE avec comme valeur le
# non du Window (qui édit un manager). Se qui aura pour éfer d'afficher ce
# Window au d'émarger de l'application.
# ex: make DEV_DEFINE=DEV_RUN_START_PREFERENCES=\\\"Network\\\"
DEV_DEFINE=
DEFINE+=$(DEV_DEFINE)
# Ajout du -D
DEFINES = $(patsubst %,-D%, $(DEFINE))

################################################################################
# Exportation de tout les variables dans les makefiles enfants.
################################################################################
export


################################################################################
# Par défaut la compilation release est active.
################################################################################
all:release


################################################################################
# Compilation en release.
################################################################################
release:
	@cd $(OS_NAME) && $(MAKE) release
	
	
################################################################################
# Compilation en debug.
################################################################################
debug:
	@cd $(OS_NAME) && $(MAKE) debug
	
	
################################################################################
# Exécute le programme
################################################################################
.PHONY: run
run:
	@cd $(OS_NAME) && $(MAKE) run
	
	
################################################################################
# Exécute le programme avec gdb.
################################################################################
.PHONY: rungdb
rungdb:	
ifeq ($(OS_NAME),msw)
	@echo "Sorry, run gdb is not possible."
else
	@cd $(OS_NAME) && $(MAKE) rungdb
endif
	
	
################################################################################
# Génération de la doc.
################################################################################
.PHONY: doc
doc:
ifeq ($(OS_NAME), msw)
	@echo "Sorry, the build of documentation is not possible."
else
	@cd $(OS_NAME) && $(MAKE) doc
endif
	
################################################################################
# Supprime la doc générée.
################################################################################
.PHONY: cleandoc
cleandoc:
ifeq ($(OS_NAME),msw)
	@echo "Sorry, the cleaning of documentation is not possible."
else
	@cd $(OS_NAME) && $(MAKE) cleandoc
endif
	
	
################################################################################
# Nettoyage du projet.
################################################################################
.PHONY: clean
clean:
	@cd $(OS_NAME) && $(MAKE) clean
