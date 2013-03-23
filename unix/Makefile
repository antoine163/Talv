########################################################################
#
#	Makfile for Linux.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	0.2
# - date 	:	10.03.2013
#
########################################################################

########################################################################
# Non de l'exécutable
########################################################################
EXEC_NAME=$(PROJECT_NAME)


########################################################################
# Flags de compilation pour les libs
########################################################################
# Flags pour wxWidgets
CXX_FLAGS+=`wx-config-2.9 --cflags`
# Flags libnotify (si utiliser)
ifeq ($(EMULATE_NOTIFICATION), no)
CXX_FLAGS+=`pkg-config --cflags libnotify`
endif


########################################################################
# Flags de linkage pour les libs
########################################################################
# Flags pour wxWidgets
LD_FLAGS+=`wx-config-2.9 --libs base,core,adv,net,propgrid`
# Flags pour la xlib
LD_FLAGS+=-lX11
# Flags pour libnotify (si utiliser)
ifeq ($(USE_LIBNOTIFY), yes)
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
SRC+=../src/menuIcon.cpp
SRC+=../src/shortcut.cpp
SRC+=../src/actionManager.cpp
SRC+=../src/action.cpp
#Action
ifeq ($(ACT_TRANSLATION), yes)
SRC+=../src/action/actTranslation.cpp
endif
#GUI
SRC+=../gui/guiDialogPreferences.cpp
SRC+=../src/dialogPreferences.cpp
SRC+=../gui/guiDialogShortcutPreferences.cpp
SRC+=../src/dialogShortcutPreferences.cpp


########################################################################
# Création de la liste des objets.
########################################################################
OBJS=$(patsubst ../%.cpp,$(OBJ_DIR)/%.o, $(SRC))


########################################################################
# Dossier a inclure.
########################################################################
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
build: $(OBJS)
	$(CXX) -o $(EXEC_NAME) $^ $(LD_FLAGS)


########################################################################
# Compilation des sources.
########################################################################
$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CXX) -o $@ -c $< $(INCLUDE_DIRS) $(CXX_FLAGS) $(DEFINES)
	
	
########################################################################
# Exécute le programme
########################################################################
.PHONY: run
run:
	@echo "run : $(EXEC_NAME)"
	@./$(EXEC_NAME)
	
	
########################################################################
# Exécute le programme avec gdb
########################################################################
.PHONY: rungdb
rungdb: debug
	@gdb $(EXEC_NAME)


########################################################################
# Génération de la doc
########################################################################
.PHONY: doc
doc:
	cd ../doc && doxygen
	
	
########################################################################
# Supprime la doc générée
########################################################################
.PHONY: cleandoc
cleandoc:
	@cd ../doc && rm -r html
	@echo "The doc is clean."


########################################################################
# Nettoyage du projet
########################################################################
.PHONY: clean
clean:
	@rm -r $(OBJ_DIR)
	@rm $(EXEC_NAME)
	@echo "The project is clean."
