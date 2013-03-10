################################################################################
#
#	Makfile.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	0.4
# - date 	:	24/11/2012
#
################################################################################

#Compilateur
CXX=g++
OBJDUMP	= objdump
#option de compilation
CXXFLAGSO=-W -Wall -Wextra -std=gnu++11 `wx-config-2.9 --cflags` `pkg-config --cflags libnotify `\
			-DPROJECT_NAME=\"flydocs\" -DPROJECT_VERSION=\"1.0\"
#Option de linkage
LDFLAGSO=`wx-config-2.9 --libs base,core,adv,net,propgrid` `pkg-config --libs libnotify` -lX11
#Non de l'exécutable.
EXEC_NAME=flydocs

#Endroit où stoker les fichiers binaire.
OBJDIR = obj

#flage en plus pour la compilation en release.
CXXFLAGSR=-s -O2 `wx-config-2.9 --debug=no`
#flage en plus pour la compilation en debug.
CXXFLAGSD=-g

#Compilation avec tts (yes par défaut)
TTS=yes
ifeq ($(TTS),yes)
CXXFLAGTTS=-D__USE_TTS__
SRCTTS=src/tts.cpp
CXXFLAGSTTS=`pkg-config --cflags gstreamer-1.0`
LDFLAGSTTS=`pkg-config --libs gstreamer-1.0`
endif

#Liste des fichiers source C++
SRCO=	src/shortcut.cpp\
		src/action.cpp\
		src/word.cpp\
		src/menuIcon.cpp\
		src/gui/guiDialogPreferences.cpp\
		src/dialogPreferences.cpp\
		src/main.cpp	
SRC=$(SRCO) $(SRCTTS)	
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o, $(SRC))

#Dossier à inclure
UINCDIRS = src
UINCDIR = $(patsubst %,-I%, $(UINCDIRS))

#Construire le projet en release
all:release

#Construire les options du projet pour la compilation en release
.PHONY: release
release:CXXFLAGS=$(CXXFLAGSO) $(CXXFLAGTTS) $(CXXFLAGSR) $(CXXFLAGSTTS)
release:LDFLAGS=$(LDFLAGSO) $(LDFLAGSTTS)
release:build

#Construire les options du projet pour la compilation en debug
.PHONY: debug
debug:CXXFLAGS=$(CXXFLAGSO) $(CXXFLAGTTS) $(CXXFLAGSD) $(CXXFLAGSTTS)
debug:LDFLAGS=$(LDFLAGSO) $(LDFLAGSTTS)
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
run:
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
