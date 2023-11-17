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
all: directories $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour créer les dossiers
directories:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	if not exist $(BINDIR) mkdir $(BINDIR)
	if not exist $(OBJDIR)\latex mkdir $(OBJDIR)\latex
else
	mkdir -p $(OBJDIR) $(BINDIR) $(OBJDIR)/latex
endif

clean:
ifeq ($(OS),Windows_NT)
	del $(OBJDIR)\*.o
	del $(OBJDIR)\latex\*.o
else
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/latex/*.o
endif
