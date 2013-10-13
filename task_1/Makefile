CXX=g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -Wextra -pedantic -fopenmp
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_image
BOOST_LDFLAGS=-lboost_program_options
OBJECTS=main.o Parser.o Image.o Transformation.o BrightnessTransformation.o
EXECUTABLE=program1

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS) $(SDL_CFLAGS) $(LDFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)
	

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c main.cc $(SDL_CFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

Parser.o : Parser.h Parser.cc
	$(CXX) $(CXXFLAGS) -c Parser.cc $(BOOST_LDFLAGS)

Image.o : Image.cc Image.h
	$(CXX) $(CXXFLAGS) -c Image.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Transformation.o : Transformation.cc Transformation.h Image.h
	$(CXX) $(CXXFLAGS) -c Transformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

BrightnessTransformation.o : BrightnessTransformation.cc BrightnessTransformation.h Image.h
	$(CXX) $(CXXFLAGS) -c BrightnessTransformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)



.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)
