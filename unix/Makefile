################################################################################
#
#	Makfile for Linux.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	0.17
# - date 	:	10.03.2013
#
################################################################################

################################################################################
# Nom de l'exécutable.
################################################################################
#EXEC_NAME=$(PROJECT_NAME)
EXEC_NAME=talv

################################################################################
# Nom du script de configuration de WxWidgets.
################################################################################
WX_CONFIG = wx-config

################################################################################
# Flags de compilation pour les libs.
################################################################################
# Flags pour wxWidgets
CXX_FLAGS+=`$(WX_CONFIG) --cxxflags`
# Flags libnotify
CXX_FLAGS+=`pkg-config --cflags libnotify`


################################################################################
# Flags de linkage pour les libs.
################################################################################
# Flags pour wxWidgets
LD_FLAGS+=`$(WX_CONFIG) --libs base,core,adv,net`
# Flags pour la xlib
LD_FLAGS+=-lX11
# Flags pour libnotify
LD_FLAGS+=`pkg-config --libs libnotify`


################################################################################
# Dossier pour les binaires.
################################################################################
OBJ_DIR = obj


################################################################################
# Liste des fichiers source C++.
################################################################################
SRC=../src/main.cpp	

#Divers
SRC+=../src/taskIcon.cpp
SRC+=../src/utils.cpp
SRC+=../src/staticBox.cpp
SRC+=../src/proxyInfo.cpp
SRC+=../src/shortcut.cpp
SRC+=../src/dataText.cpp
SRC+=../src/fileText.cpp
SRC+=../src/cache.cpp
SRC+=../src/list.cpp

#wxJSON
SRC+=../src/wxJSON/jsonval.cpp
SRC+=../src/wxJSON/jsonreader.cpp

#Controls
SRC+=../src/control/ctrlDataList.cpp
SRC+=../src/control/ctrlProxyInfo.cpp
SRC+=../src/control/ctrlAuthentication.cpp
SRC+=../src/control/ctrlPickShortcutKey.cpp
SRC+=../src/control/ctrlPickLanguages.cpp

#Dialogs
SRC+=../src/dialogInlay.cpp
SRC+=../src/dialog/dlgPreferences.cpp
SRC+=../src/dialog/dlgPreferencesAction.cpp
SRC+=../src/dialog/dlgPickShortcutKey.cpp
SRC+=../src/dialog/dlgNewList.cpp

#Managers
SRC+=../src/manager.cpp	
SRC+=../src/manager/manGeneral.cpp
SRC+=../src/manager/manAction.cpp
SRC+=../src/manager/manList.cpp
SRC+=../src/manager/manNotification.cpp
SRC+=../src/manager/manTts.cpp
SRC+=../src/manager/manNetwork.cpp
SRC+=../src/manager/manCache.cpp
SRC+=../src/manager/manTranslator.cpp

#Actions
SRC+=../src/action.cpp
SRC+=../src/action/actTranslationToNotification.cpp
SRC+=../src/action/actTranslationToList.cpp
SRC+=../src/action/actLauncher.cpp

#Translators
SRC+=../src/translator.cpp
SRC+=../src/translator/trlCache.cpp
SRC+=../src/translator/trlGoogle.cpp

#Tts
#SRC+=../src/tts.cpp


################################################################################
# Création de la liste des objets.
################################################################################
OBJS=$(patsubst ../%.cpp,$(OBJ_DIR)/%.o, $(SRC))


################################################################################
# Dossier a inclure.
################################################################################
DIR = ../include
DIR += ../include/wxJSON
INCLUDE_DIRS = $(patsubst %,-I%, $(DIR))


################################################################################
# Par défaut la compilation release est active.
################################################################################
all:release


################################################################################
# Compilation en release.
################################################################################
.PHONY: release
release: CXX_FLAGS+=$(CXX_FLAGS_RELESE)
release: build


################################################################################
# Compilation en debug.
################################################################################
.PHONY: debug
debug: CXX_FLAGS+=$(CXX_FLAGS_DEBUG)
debug: build
	

################################################################################
# Linkage des sources.
################################################################################
build: $(OBJS)
	$(CXX) -o ../$(EXEC_NAME) $^ $(LD_FLAGS)


################################################################################
# Compilation des sources.
################################################################################
$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CXX) -o $@ -c $< $(INCLUDE_DIRS) $(CXX_FLAGS) $(DEFINES)
	
	
################################################################################
# Exécute le programme.
################################################################################
.PHONY: run
run:
	@echo "run : $(EXEC_NAME)"
	@cd ../ && ./$(EXEC_NAME)
	
	
################################################################################
# Exécute le programme avec gdb.
################################################################################
.PHONY: rungdb
rungdb:
	@echo "run : $(EXEC_NAME)"
	@cd ../ && gdb $(EXEC_NAME)
	
################################################################################
# Exécute le programme avec nemiver (gui pour gdb).
################################################################################
.PHONY: runnemiver
runnemiver:
	@echo "run : $(EXEC_NAME)"
	@cd ../ && nemiver $(EXEC_NAME)


################################################################################
# Génération de la doc.
################################################################################
.PHONY: doc
doc:
	cd ../doc && doxygen
	
	
################################################################################
# Supprime la doc générée.
################################################################################
.PHONY: cleandoc
cleandoc:
	@cd ../doc && rm -r html
	@echo "The doc is clean."


################################################################################
# Nettoyage du projet.
################################################################################
.PHONY: clean
clean:
	@rm -r $(OBJ_DIR)
	@rm ../$(EXEC_NAME)
	@echo "The project is clean."
