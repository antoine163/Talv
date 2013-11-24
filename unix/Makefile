########################################################################
#
#	Makfile for Linux.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	0.13
# - date 	:	10.03.2013
#
########################################################################

########################################################################
# Non de l'exécutable.
########################################################################
EXEC_NAME=$(PROJECT_NAME)


########################################################################
# Flags de compilation pour les libs.
########################################################################
# Flags pour wxWidgets
CXX_FLAGS+=`wx-config-3.0 --cxxflags`
# Flags libnotify (si utiliser)
ifeq ($(EMULATE_NOTIFICATION), no)
CXX_FLAGS+=`pkg-config --cflags libnotify`
endif


########################################################################
# Flags de linkage pour les libs.
########################################################################
# Flags pour wxWidgets
LD_FLAGS+=`wx-config-3.0 --libs base,core,adv,net`
# Flags pour la xlib
LD_FLAGS+=-lX11
# Flags pour libnotify (si utiliser)
ifeq ($(EMULATE_NOTIFICATION), no)
LD_FLAGS+=`pkg-config --libs libnotify`
endif


########################################################################
# Dossier pour les binaires.
########################################################################
OBJ_DIR = obj


########################################################################
# Liste des fichiers source C++.
########################################################################
SRC=../src/main.cpp	
SRC+=../src/taskIcon.cpp
SRC+=../src/editableByPanel.cpp
SRC+=../src/shortcut.cpp
SRC+=../src/managerAction.cpp
SRC+=../src/action.cpp
#SRC+=../src/managerList.cpp
SRC+=../src/list.cpp
SRC+=../src/resource.cpp
#wxJSON
SRC+=../src/wxJSON/jsonval.cpp
SRC+=../src/wxJSON/jsonreader.cpp
#Notification
SRC+=../src/notification.cpp
ifeq ($(EMULATE_NOTIFICATION), yes)
SRC+=../gui/guiFrameNotification.cpp
endif
#Action
#SRC+=../src/action/actLearn.cpp
#SRC+=../gui/action/guiPanelActLearn.cpp
SRC+=../src/action/actTranslation.cpp
SRC+=../gui/action/guiPanelActTranslation.cpp
#SRC+=../src/action/actTranslationToList.cpp
#SRC+=../gui/action/guiPanelActTranslationToList.cpp
#GUI
SRC+=../gui/guiPanelDataList.cpp
SRC+=../src/panelDataList.cpp
SRC+=../gui/guiDialogPreferences.cpp
SRC+=../src/dialogPreferences.cpp
SRC+=../gui/guiDialogActionPreferences.cpp
SRC+=../src/dialogActionPreferences.cpp
SRC+=../gui/guiDialogListAdd.cpp
SRC+=../src/dialogListAdd.cpp


########################################################################
# Création de la liste des objets.
########################################################################
OBJS=$(patsubst ../%.cpp,$(OBJ_DIR)/%.o, $(SRC))


########################################################################
# Dossier a inclure.
########################################################################
DIR = ../include
DIR += ../include/wxJSON
DIR += ../gui
INCLUDE_DIRS = $(patsubst %,-I%, $(DIR))


########################################################################
# Par défaut la compilation release est active.
########################################################################
all:release


########################################################################
# Compilation en release.
########################################################################
.PHONY: release
release: CXX_FLAGS+=$(CXX_FLAGS_RELESE)
release: build


########################################################################
# Compilation en debug.
########################################################################
.PHONY: debug
debug: CXX_FLAGS+=$(CXX_FLAGS_DEBUG)
debug: build
	

########################################################################
# Linkage des sources.
########################################################################
build: $(OBJS)
	$(CXX) -o $(EXEC_NAME) $^ $(LD_FLAGS)


########################################################################
# Compilation des sources.
########################################################################
$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CXX) -o $@ -c $< $(INCLUDE_DIRS) $(CXX_FLAGS) $(DEFINES)
	
	
########################################################################
# Exécute le programme.
########################################################################
.PHONY: run
run:
	@echo "run : $(EXEC_NAME)"
	@./$(EXEC_NAME)
	
	
########################################################################
# Exécute le programme avec gdb.
########################################################################
.PHONY: rungdb
rungdb: debug
	@gdb $(EXEC_NAME)


########################################################################
# Génération de la doc.
########################################################################
.PHONY: doc
doc:
	cd ../doc && doxygen
	
	
########################################################################
# Supprime la doc générée.
########################################################################
.PHONY: cleandoc
cleandoc:
	@cd ../doc && rm -r html
	@echo "The doc is clean."


########################################################################
# Nettoyage du projet.
########################################################################
.PHONY: clean
clean:
	@rm -r $(OBJ_DIR)
	@rm $(EXEC_NAME)
	@echo "The project is clean."
