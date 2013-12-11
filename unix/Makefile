################################################################################
#
#	Makfile for Linux.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	0.16
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
WX_CONFIG = wx-config-3.0

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
#SRC+=../src/shortcut.cpp
#SRC+=../src/dataText.cpp
#SRC+=../src/fileText.cpp
#SRC+=../src/cache.cpp
#SRC+=../src/list.cpp

#Controls
SRC+=../src/control/ctrlDataList.cpp
SRC+=../src/control/ctrlAuthentication.cpp

#Dialogs
SRC+=../src/dialog/dlgPreferences.cpp

#wxJSON
SRC+=../src/wxJSON/jsonval.cpp
SRC+=../src/wxJSON/jsonreader.cpp

#Managers
SRC+=../src/manager.cpp	
SRC+=../src/manager/manGeneral.cpp
SRC+=../src/manager/manAction.cpp
SRC+=../src/manager/manList.cpp
SRC+=../src/manager/manNotification.cpp
SRC+=../src/manager/manTts.cpp
SRC+=../src/manager/manNetwork.cpp

#Actions
#SRC+=../src/action.cpp

#Translates
#SRC+=../src/translate.cpp

#Tts
#SRC+=../src/tts.cpp


#SRC+=../src/managerCache.cpp	
#SRC+=../src/shortcut.cpp
#SRC+=../src/managerAction.cpp
#SRC+=../src/action.cpp
#SRC+=../src/managerList.cpp
#SRC+=../src/listBase.cpp
#SRC+=../src/list.cpp
#SRC+=../src/cache.cpp
#SRC+=../src/dataText.cpp
#SRC+=../src/resource.cpp

#Notification
#SRC+=../src/notification.cpp
#ifeq ($(EMULATE_NOTIFICATION), yes)
#SRC+=../gui/guiFrameNotification.cpp
#endif
#Action
#SRC+=../src/action/actLearn.cpp
#SRC+=../gui/action/guiPanelActLearn.cpp
#SRC+=../src/action/actTranslation.cpp
#SRC+=../gui/action/guiPanelActTranslation.cpp
#SRC+=../src/action/actTranslationToList.cpp
#SRC+=../gui/action/guiPanelActTranslationToList.cpp
#GUI
#SRC+=../gui/guiPanelDataList.cpp
#SRC+=../src/panelDataList.cpp
#SRC+=../gui/guiDialogPreferences.cpp
#SRC+=../src/dialogPreferences.cpp
#SRC+=../gui/guiDialogActionPreferences.cpp
#SRC+=../src/dialogActionPreferences.cpp
#SRC+=../gui/guiDialogListAdd.cpp
#SRC+=../src/dialogListAdd.cpp


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
rungdb: debug
	@echo "run : $(EXEC_NAME)"
	@cd ../ && gdb $(EXEC_NAME)


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
