# Makefile

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

# Dossiers
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Fichiers source
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/latex/*.cpp)

# Noms des fichiers objets
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Nom de l'exécutable
EXECUTABLE = $(BINDIR)/main

# Règle de compilation
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Commentez ou supprimez cette règle pour éviter de créer les dossiers
#directories:
# 	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	del $(OBJDIR)\*.o
	del $(OBJDIR)\latex\*.o
