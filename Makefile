################################################################################
#
#	Makfile.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	0.2
# - date 	:	24/11/2012
#
################################################################################

#Compilateur
CXX=g++
OBJDUMP	= objdump
#option de compilation
CXXFLAGSO=-W -Wall -Wextra -std=gnu++11 `wx-config-2.9 --cflags` `pkg-config --cflags libnotify gstreamer-1.0`
#Option de linkage
LDFLAGS=`wx-config-2.9 --libs` `pkg-config --libs libnotify gstreamer-1.0` -lX11
#Non de l'exécutable.
EXEC_NAME=flydocs

#Endroit où stoker les fichiers binaire.
OBJDIR = obj

#flage en plus pour la compilation en release.
CXXFLAGSR=-s -O2
#flage en plus pour la compilation en debug.
CXXFLAGSD=-g

#Liste des fichiers source C++
SRC=	src/shortcut.cpp\
		src/tts.cpp\
		src/word.cpp\
		src/menuIcon.cpp\
		src/main.cpp		
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o, $(SRC))

#Dossier à inclure
UINCDIRS =	src		\
			gui
UINCDIR = $(patsubst %,-I%, $(UINCDIRS))


#Construire le projet en release
all:release

#Construire les options du projet pour la compilation en release
.PHONY: release
release:CXXFLAGS=$(CXXFLAGSO) $(CXXFLAGSR)
release:build

#Construire les options du projet pour la compilation en debug
.PHONY: debug
debug:CXXFLAGS=$(CXXFLAGSO) $(CXXFLAGSD)
debug:build

#Construction du projet
build: $(OBJS)
	$(CXX) -o $(EXEC_NAME) $^ $(LDFLAGS)
#$(OBJDUMP) -h -S $(EXEC_NAME) > $(EXEC_NAME).lss

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CXX) -o $@ -c $<  $(UINCDIR) $(CXXFLAGS)
	
	
#Exécute le programme
.PHONY: run
run: release
	@echo "run : $(EXEC_NAME)"
	@./$(EXEC_NAME)
	
#Exécute le programme avec gdb
.PHONY: rungdb
rungdb: debug
	@gdb $(EXEC_NAME)

#Génération de la doc
.PHONY: doc
doc:
	cd doc && doxygen
	
#Supprime la doc générée
.PHONY: cleandoc
cleandoc:
	@cd doc && rm html -R

#Nettoyage du projet
.PHONY: clean
clean:
	@rm $(OBJDIR) -R
	@rm $(EXEC_NAME)
