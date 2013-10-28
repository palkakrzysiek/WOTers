CXX=g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -Wextra -pedantic -fopenmp -I../libimage/
MAIN_CFLAGS=
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_image
BOOST_LDFLAGS=-lboost_program_options
OBJECTS=main.o Histogram.o Image.o Operation.o
EXECUTABLE=program2

all: $(OBJECTS) $(EXECUTABLE)
	
speed_test: MAIN_CFLAGS+= -D_SPEED_TEST
speed_test: EXECUTABLE=program2_st
speed_test: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS) $(SDL_CFLAGS) $(LDFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

main.o : main.cc
	$(CXX) $(CXXFLAGS) $(MAIN_CFLAGS) -c main.cc $(SDL_CFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

# Parser.o : Parser.h Parser.cc
# 	$(CXX) $(CXXFLAGS) -c Parser.cc $(BOOST_LDFLAGS)

Histogram.o: Histogram.cc Histogram.h
	$(CXX) $(CXXFLAGS) -c Histogram.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Image.o : ../libimage/Image.cc ../libimage/Image.h
	$(CXX) $(CXXFLAGS) -c ../libimage/Image.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Operation.o : ../libimage/Operation.cc ../libimage/Operation.h
	$(CXX) $(CXXFLAGS) -c ../libimage/Operation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

.PHONY : clean_compilation_type
clean_compilation_type :
	rm main.o
