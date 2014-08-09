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
FILES=main.h image_output.h
FILES+=geometry/Cube.h geometry/Intersection.h geometry/Object.h geometry/Plane.h geometry/Sphere.h
FILES+=materials/Material.h
FILES+=lights/AmbientLight.h lights/Light.h lights/PunctualLight.h
FILES+=renderer/Camera.h renderer/Image.h renderer/Ray.h renderer/Renderer.h
FILES+=scenes/CoordinatesTestScene.h scenes/Scene.h scenes/ShadowsTestScene.h scenes/TestScene.h

# Headers that most classes depend on
COMMONS=$(SRCDIR)/types.h $(SRCDIR)/renderer/Color.h

HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
OBJ=$(addprefix $(OUTPUTDIR)/,$(FILES:.h=.o))
# Subdirectories that output .o will be written to
SRCDIRS=$(shell (cd src; ls -d */))
OBJDIRS=$(addprefix $(OUTPUTDIR)/,$(SRCDIRS))

.PHONY: $(CLEAN) before all
all: before $(OUTPUTDIR)/$(EXE)

# Make sure that all directories we'll write to are created
before:
	@mkdir -p $(OBJDIRS)

# Ouput executable
$(OUTPUTDIR)/$(EXE): $(OBJ) $(COMMONS)
	$(ECHO) Linking $(EXE)...
	$(LINKER) $(LINKERFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$(EXE) $(OBJ) $(LIBS)

# Generic rule
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

# Explicit dependancies
$(OUTPUTDIR)/main.o: $(SRCDIR)/image_output.h $(SRCDIR)/renderer/Renderer.h $(SRCDIR)/renderer/Camera.h $(SRCDIR)/scenes/Scene.h
$(OUTPUTDIR)/Renderer.o: $(SRCDIR)/renderer/Ray.h $(SRCDIR)/renderer/Image.h
$(OUTPUTDIR)/image_output.o: $(SRCDIR)/renderer/Image.h

$(OUTPUTDIR)/geometry/Object.o: $(SRCDIR)/materials/Material.h
$(OUTPUTDIR)/geometry/Sphere.o: $(SRCDIR)/Geometry/Object.h
$(OUTPUTDIR)/geometry/Cube.o: $(SRCDIR)/Geometry/Object.h
$(OUTPUTDIR)/geometry/Plane.o: $(SRCDIR)/Geometry/Object.h

run: all
	$(ECHO)
	@./bin/$(EXE)

$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core
