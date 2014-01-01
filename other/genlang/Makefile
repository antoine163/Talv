################################################################################
#
#	Makfile pour compiler genlang.
#
# - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
# - version	:	0.1
# - date 	:	01.01.2014
#
################################################################################

#Compilateur
CXX=g++
OBJDUMP	= objdump
#option de compilation
CXXFLAGSO=-W -Wall -Wextra -std=gnu++11
#Option de linkage
LDFLAGS=
#Non de l'exécutable.
EXEC_NAME=genlang

#Endroit où stoker les fichiers binaire.
OBJDIR = obj

#flage en plus pour la compilation en release.
CXXFLAGSR=-s -O2
#flage en plus pour la compilation en debug.
CXXFLAGSD=-g

#Liste des fichiers source C++
SRC=genlang.cpp
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o, $(SRC))

#Dossier à inclure
UINCDIRS =
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
	

#Nettoyage du projet
.PHONY: clean
clean:
	@rm $(OBJDIR) -R
	@rm $(EXEC_NAME)

