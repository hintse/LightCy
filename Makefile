CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-deprecated-declarations -Wno-writable-strings
LDLIBS = -framework GLUT -framework OpenGL

GLUTMASTER_FILES = glutMaster.cc glutWindow.cc
GLUTMASTER_OBJS = glutMaster.o glutWindow.o 
LIGHTCY_FILES = main.cc LightCy.cc PlasmaFractal.cc Timer.cc Player.cc Camera.cc Terrain.cc Trail.cc Message.cc
LIGHTCY_OBJS = LightCy.o PlasmaFractal.o main.o Timer.o Player.o Camera.o Terrain.o Trail.o Message.o

OBJS = $(GLUTMASTER_OBJS) $(LIGHTCY_OBJS)
SRCS = $(GLUTMASTER_FILES) $(LIGHTCY_FILES)

all: LightCy

LightCy: $(OBJS)
	$(CXX) $(LDLIBS) -o LightCy $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS)

dist-clean: clean
	rm -f .depend

include .depend


	