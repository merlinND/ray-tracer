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
FILES=main.h
FILES+=geometry/Cube.h geometry/Intersection.h geometry/Object.h geometry/Parallelepipoid.h geometry/Plane.h geometry/Sphere.h
FILES+=materials/Material.h
FILES+=lights/AmbientLight.h lights/AreaLight.h lights/Light.h lights/PunctualLight.h
FILES+=renderer/Camera.h renderer/Image.h renderer/Ray.h renderer/Renderer.h
FILES+=scenes/CoordinatesTestScene.h scenes/LightingTestScene.h scenes/RefractionTestScene.h scenes/Scene.h scenes/ShadowsTestScene.h scenes/TestScene.h scenes/TexturesTestScene.h
FILES+=textures/ColorTexture.h textures/GridTexture.h textures/ImageTexture.h textures/Texture.h
FILES+=util/image_input.h util/image_output.h util/mersenneTwister.h

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
$(OUTPUTDIR)/main.o: $(SRCDIR)/util/image_output.h $(SRCDIR)/renderer/Renderer.h $(SRCDIR)/renderer/Camera.h $(SRCDIR)/scenes/Scene.h
$(OUTPUTDIR)/util/image_output.o: $(SRCDIR)/renderer/Image.h

$(OUTPUTDIR)/renderer/Renderer.o: $(SRCDIR)/renderer/Ray.h $(SRCDIR)/renderer/Image.h
$(OUTPUTDIR)/renderer/Camera.o: $(SRCDIR)/renderer/Ray.h

$(OUTPUTDIR)/geometry/Object.o: $(SRCDIR)/materials/Material.h
$(OUTPUTDIR)/geometry/Sphere.o: $(SRCDIR)/geometry/Object.h
$(OUTPUTDIR)/geometry/Parallelepipoid.o: $(SRCDIR)/geometry/Object.h
$(OUTPUTDIR)/geometry/Cube.o: $(SRCDIR)/geometry/Parallelepipoid.h
$(OUTPUTDIR)/geometry/Plane.o: $(SRCDIR)/geometry/Object.h

$(OUTPUTDIR)/lights/Light.o: $(SRCDIR)/renderer/Ray.h $(SRCDIR)/renderer/Color.h
$(OUTPUTDIR)/lights/AmbientLight.o: $(SRCDIR)/lights/Light.h
$(OUTPUTDIR)/lights/AreaLight.o: $(SRCDIR)/renderer/Ray.h $(SRCDIR)/lights/PunctualLight.h $(SRCDIR)/scenes/Scene.h
$(OUTPUTDIR)/lights/PunctualLight.o: $(SRCDIR)/lights/Light.h

$(OUTPUTDIR)/scenes/Scene.o: $(SRCDIR)/renderer/Ray.h $(SRCDIR)/geometry/Intersection.h


run: all
	$(ECHO)
	@./bin/$(EXE)

$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core
