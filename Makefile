COMPILER=g++
CPPFLAGS=-w -Wall
LINKER=@g++
LINKERFLAGS=

INCPATH=-I ./lib
LIBPATH=-L ./lib
LIBS=-lm -ljpeg

ECHO=@echo
CLEAN=clean

SRCDIR=src
OUTPUTDIR=bin
EXE=ray-tracer

FILES=main.h Camera.h Renderer.h Scene.h

HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
OBJ=$(addprefix $(OUTPUTDIR)/,$(FILES:.h=.o))

.PHONY: $(CLEAN)
ALL: $(EXE)

# Ouput executable
$(OUTPUTDIR)/$(EXE): $(OBJ)
	$(ECHO) Linking $(EXE)...
	$(LINKER) $(LINKERFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$(EXE) $(OBJ) $(LIBS)

# Generic rule
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

# Explicit dependancies
#$(OUTPUTDIR)/dep.o: $(SRCDIR)/dep1.h $(SRCDIR)/dep2.h

run: $(OUTPUTDIR)/$(EXE)
	$(ECHO)
	@./bin/$(EXE)

$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core
