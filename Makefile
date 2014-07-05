COMPILER=g++
CPPFLAGS=-w -Wall
LINKER=g++
LINKERFLAGS=

INCPATH=-I ./lib
LIBPATH=-L ./lib
LIBS=-lm -ljpeg

ECHO=@echo
CLEAN=clean

SRCDIR=src
OUTPUTDIR=bin
EXE=ray-tracer


# Header files that have an implementation to be compiled
FILES=main.h Camera.h image_output.h Ray.h Renderer.h
FILES+=geometry/Cube.h geometry/Object.h
FILES+=materials/Material.h
FILES+=lights/Light.h lights/AmbientLight.h
FILES+=scenes/Scene.h scenes/TestScene.h

# Headers that most classes depend on
COMMONS=$(SRCDIR)/types.h $(SRCDIR)/Color.h

HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
OBJ=$(addprefix $(OUTPUTDIR)/,$(FILES:.h=.o))
# Subdirectories that output .o will be written to
SRCDIRS=$(shell (cd src; ls -d */))
OBJDIRS=$(addprefix $(OUTPUTDIR)/,$(SRCDIRS))

.PHONY: $(CLEAN) before all
all: before $(OUTPUTDIR)/$(EXE)

# Make sure that all directories we'll write to are created
before:
	mkdir -p $(OBJDIRS)

# Ouput executable
$(OUTPUTDIR)/$(EXE): $(OBJ) $(COMMONS)
	$(ECHO) Linking $(EXE)...
	$(LINKER) $(LINKERFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$(EXE) $(OBJ) $(LIBS)

# Generic rule
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

# Explicit dependancies
$(OUTPUTDIR)/main.o: $(SRCDIR)/image_output.h
$(OUTPUTDIR)/geometry/Cube.o: $(SRCDIR)/Geometry/Object.h

run: all
	$(ECHO)
	@./bin/$(EXE)

$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core
