
# CSE170 glutapp makefile v2.1 - M. Kallmann 2009

SOURCES := $(shell echo $(./)*.cpp)
DEPENDS = $(SOURCES:.cpp=.d)
OBJECTS = $(SOURCES:.cpp=.o)
OS = $(shell uname) # For Mac OS detection (by Rolando Yanez, Raymond Harris)
PROGRAM = raytrace

#######################################################################

# OPTFLAGS = -g  # for debug
OPTFLAGS =  -O3
CC       = g++
CFLAGS   = -Wall -Wno-format $(OPTFLAGS)

ifeq ($(strip $(OS)),Darwin)
	LDFLAGS = -framework GLUT -framework OpenGL
else
	LDFLAGS = -lGLU -lglut
endif

#######################################################################

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	$(RM) $(PROGRAM)
	$(RM) *~

#######################################################################

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< > $@

#######################################################################

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

#######################################################################
