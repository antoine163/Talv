########################################################################
#
#	Makfile for Windows.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	0.2
# - date 	:	10.03.2013
#
########################################################################

########################################################################
# Non de l'exécutable.
########################################################################
EXEC_NAME=$(PROJECT_NAME).exe


########################################################################
# Flags de compilation pour les libs.
########################################################################
# Flags pour wxWidgets
CXX_FLAGS+=-mthreads
CXX_FLAGS+=-IC:\wxWidgets-2.9.4\include
CXX_FLAGS+=-IC:\wxWidgets-2.9.4\lib\gcc_dll\mswu
CXX_FLAGS+=-D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE


########################################################################
# Flags de linkage pour les libs.
########################################################################
# Flags pour wxWidgets
LD_FLAGS+=-mthreads -LC:\wxWidgets-2.9.4\lib\gcc_dll
LD_FLAGS+=-lwxbase29u -lwxmsw29u_core -lwxmsw29u_adv -lwxbase29u_net


########################################################################
# Dossier pour les binaires.
########################################################################
OBJ_DIR = obj


########################################################################
# Liste des fichiers source C++.
########################################################################
SRC=../src/main.cpp	
SRC+=../src/menuIcon.cpp
SRC+=../src/shortcut.cpp
SRC+=../src/actionManager.cpp
SRC+=../src/action.cpp
SRC+=../src/listManager.cpp
SRC+=../src/list.cpp
SRC+=../src/resource.cpp
#Notification
SRC+=../src/notification.cpp
ifeq ($(EMULATE_NOTIFICATION), yes)
SRC+=../gui/guiDialogNotification.cpp
endif
#Action
SRC+=../src/action/actLearn.cpp
SRC+=../gui/action/guiPanelActLearn.cpp
SRC+=../src/action/actTranslation.cpp
SRC+=../gui/action/guiPanelActTranslation.cpp
SRC+=../src/action/actSay.cpp
SRC+=../gui/action/guiPanelActSay.cpp
SRC+=../src/action/actTranslationToList.cpp
SRC+=../gui/action/guiPanelActTranslationToList.cpp
#GUI
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
DIR = ../include
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
release: CXX_FLAGS+=$(CXX_FLAGS_DEBUG)
release: build


########################################################################
# Linkage des sources.
########################################################################
build: resource.o $(OBJS)
	$(CXX) -o $(EXEC_NAME) $^ $(LD_FLAGS)
	
	
########################################################################
# Compilation des sources.
########################################################################
$(OBJ_DIR)/%.o: ../%.cpp
	@-if not exist $(@D) md "$(@D)"
	$(CXX) -o $@ -c $< $(INCLUDE_DIRS) $(CXX_FLAGS) $(DEFINES)
	
	
########################################################################
# Compilation des ressources.
########################################################################
resource.o:resource.rc
	windres -IC:\wxWidgets-2.9.4\include -o $@ -i $<


########################################################################
# Exécute le programme.
########################################################################
.PHONY: run
run:
	@echo "run : $(EXEC_NAME)"
	@$(EXEC_NAME)

########################################################################
# Nettoyage du projet.
########################################################################
.PHONY: clean
clean:
	@-if exist $(OBJ_DIR) rd $(OBJ_DIR) /s /q
	@-if exist $(EXEC_NAME) del $(EXEC_NAME)
	@-if exist resource.o del resource.o
	@echo "The project is clean."
