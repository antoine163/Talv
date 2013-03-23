########################################################################
#
#	Makfile.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	1.1
# - date 	:	24/11/2012
#
########################################################################


########################################################################
# Param�tre g�n�raux.
########################################################################
#Non du projet
PROJECT_NAME=flydocs
#Num�ro de version
PROJECT_VERSION=1.0


########################################################################
# D�tection de l'os (Pas de d�tection pour le moment, mais un simple
# passage d'augment permer de compiler pour les diff�rence os supporter.
# ex pour windows: make release OS_NAME=msw).
########################################################################
OS_NAME=unix


########################################################################
# Actions � compiler.
########################################################################
#Traduction du mot/phrase
ACT_TRANSLATION=yes
#Sovgarde de la raduction du mot/phrase
ACT_SAVE_TRANSLATION=no
#Dire le mot/phrase
ACT_SAY=no


########################################################################
# �muler les notifications. Par d�faut sous msw elles sont �mul�.
# Par d�faut sous unix elle ne sons pas �muler et libnotify sera utiliser
########################################################################
ifeq ($(OS_NAME), unix)
EMULATE_NOTIFICATION=no
endif
ifeq ($(OS_NAME), msw)
EMULATE_NOTIFICATION=yes
endif


########################################################################
# Compilateur et flags C++.
########################################################################
#Compilateur
CXX=g++
#Option de compilation g�n�raux
CXX_FLAGS=-W -Wall -Wextra -std=gnu++11
#Flage en plus pour la compilation en release.
CXX_FLAGS_RELESE=-s -O2
#Flage en plus pour la compilation en debug.
CXX_FLAGS_DEBUG=-g

########################################################################
# Define � ajouter.
########################################################################
# Non du projet
DEFINE=PROJECT_NAME=\"$(PROJECT_NAME)\"
# Num�ro de version
DEFINE+=PROJECT_VERSION=\"$(PROJECT_VERSION)\"
######## Les Actions > ######## 
#Traduction du mot/phrase
ifeq ($(ACT_TRANSLATION), yes)
DEFINE+=USE_ACT_TRANSLATION
endif
#Sovgarde de la raduction du mot/phrase
ifeq ($(ACT_SAVE_TRANSLATION), yes)
DEFINE+=USE_ACT_SAVE_TRANSLATION
endif
#Dire le mot/phrase
ifeq ($(ACT_SAY), yes)
DEFINE+=USE_ACT_SAY
endif
######## Les Actions < ########
#�muler les notifications.
ifeq ($(EMULATE_NOTIFICATION), yes)
DEFINE+=USE_EMULATE_NOTIFICATION
endif
# Ajout du -D
DEFINES = $(patsubst %,-D%, $(DEFINE))


########################################################################
# Exportation de tout les variables dans les makefiles enfants.
########################################################################
export


########################################################################
# Par d�faut la compilation release est active.
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
# Ex�cute le programme
########################################################################
.PHONY: run
run:
	@cd $(OS_NAME) && $(MAKE) run
	
	
########################################################################
# Ex�cute le programme avec gdb.
########################################################################
.PHONY: rungdb
rungdb:	
ifeq ($(OS_NAME),msw)
	@echo "Sorry, run gdb is not possible."
else
	@cd $(OS_NAME) && $(MAKE) rungdb
endif
	
	
########################################################################
# G�n�ration de la doc.
########################################################################
.PHONY: doc
doc:
ifeq ($(OS_NAME), msw)
	@echo "Sorry, the build of documentation is not possible."
else
	@cd $(OS_NAME) && $(MAKE) doc
endif
	
########################################################################
# Supprime la doc g�n�r�e.
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
