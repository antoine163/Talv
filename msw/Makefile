################################################################################
#
#	Makfile for Windows.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
# - version	:	0.1
# - date 	:	10.03.2013
#
################################################################################

########################################################################
# Non de l'exécutable
########################################################################
EXEC_NAME=$(PROJECT_NAME).exe


########################################################################
# Flags de compilation pour les libs
########################################################################
# Flags pour wxWidgets
CXX_FLAGS+=-mthreads
CXX_FLAGS+=-IC:\wxWidgets-2.9.4\include\
CXX_FLAGS+=-IC:\wxWidgets-2.9.4\lib\gcc_dll\mswu\
CXX_FLAGS+=-D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE\


########################################################################
# Flags de linkage pour les libs
########################################################################
# Flags pour wxWidgets
LD_FLAGS+=mthreads -LC:\wxWidgets-2.9.4\lib\gcc_dll\
LD_FLAGS+=-lwxbase29u -lwxmsw29u_core -lwxmsw29u_adv -lwxbase29u_net
LD_FLAGS+=-lwxmsw29u_propgrid


########################################################################
# Define à ajouter.
########################################################################
# Non du projet
DEFINE=PROJECT_NAME=\"$(PROJECT_NAME)\"
# Numéro de version
DEFINE+=PROJECT_VERSION=\"$(PROJECT_VERSION)\"


########################################################################
# Dossier pour les binaires.
########################################################################
OBJ_DIR = obj


########################################################################
# Liste des fichiers source C++.
########################################################################
SRC=../src/main.cpp	
SRC+=../src/menuIcon.cpp


########################################################################
# Création de la liste des objets.
########################################################################
OBJS=$(patsubst ../%.cpp,$(OBJ_DIR)/%.o, $(SRC))


########################################################################
# Dossier a inclure.
########################################################################
DIR = ../include
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
# Exécute le programme
########################################################################
.PHONY: run
run:
	@echo "run : $(EXEC_NAME)"
	@$(EXEC_NAME)

########################################################################
# Nettoyage du projet
########################################################################
.PHONY: clean
clean:
	@-if exist $(OBJDIR) rd $(OBJDIR) /s /q
	@-if exist $(EXEC_NAME) del $(EXEC_NAME)
	@-if exist resource.o del resource.o
	@echo "The project is clean."
