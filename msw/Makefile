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
#option de compilation
CXXFLAGSO=-W -Wall -Wextra -std=gnu++11 -mthreads\
	-IC:\wxWidgets-2.9.4\include\
	-IC:\wxWidgets-2.9.4\lib\gcc_dll\mswu\
	-D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE\
	-DPROJECT_NAME=\"flydocs\" -DPROJECT_VERSION=\"0.1\"
#Option de linkage
LDFLAGSO= -mthreads -LC:\wxWidgets-2.9.4\lib\gcc_dll\
-lwxbase29u -lwxmsw29u_core -lwxmsw29u_adv -lwxbase29u_net -lwxmsw29u_propgrid

#Non de l'exécutable.
EXEC_NAME=..\flydocs.exe

#Endroit où stoker les fichiers binaire.
OBJDIR=obj

#flage en plus pour la compilation en release.
CXXFLAGSR=-O2
#flage en plus pour la compilation en debug.
CXXFLAGSD=-g

#Compilation avec tts (yes par défaut)
TTS=yes
ifeq ($(TTS),yes)
CXXFLAGTTS=-D__USE_TTS__
SRCTTS=../src/tts.cpp
CXXFLAGSTTS=
LDFLAGSTTS=
endif

#Liste des fichiers source C++
SRCO=	../src/shortcut.cpp\
		../src/action.cpp\
		../src/word.cpp\
		../src/menuIcon.cpp\
		../src/gui/guiDialogPreferences.cpp\
		../src/dialogPreferences.cpp\
		../src/main.cpp
SRC=$(SRCO) $(SRCTTS)
OBJS=$(patsubst ../%.cpp,$(OBJDIR)/%.o, $(SRC))

#Dossier à inclure
UINCDIRS = ../src
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
build: resource.o $(OBJS) 
	$(CXX) -o $(EXEC_NAME) $^ $(LDFLAGS)
	
$(OBJDIR)/%.o: ../%.cpp	
	@-if not exist $(@D) md "$(@D)"
	$(CXX) -o $@ -c $<  $(UINCDIR) $(CXXFLAGS)
	
resource.o:resource.rc
	windres -IC:\wxWidgets-2.9.4\include -o $@ -i $<

#Exécute le programme
.PHONY: run
run:
	@cd .. && msw\$(EXEC_NAME)

#Nettoyage du projet
.PHONY: clean
clean:
	@-if exist $(OBJDIR) rd $(OBJDIR) /s /q
	@-if exist $(EXEC_NAME) del $(EXEC_NAME)
	@-if exist resource.o del resource.o
