CXX=g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -Wextra -pedantic -fopenmp
MAIN_CFLAGS=
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_image
BOOST_LDFLAGS=-lboost_program_options
OBJECTS=main.o Parser.o Image.o Transformation.o BrightnessTransformation.o ContrastTransformation.o DiagonalFlip.o VerticalFlip.o HorizontalFlip.o NegativeTransformation.o Resize.o AlphaTrimmedMeanFilter.o ContramorphicMeanFilter.o 
EXECUTABLE=program1

all: $(OBJECTS) $(EXECUTABLE)
	
speed_test: MAIN_CFLAGS+= -D_SPEED_TEST
speed_test: EXECUTABLE=program1_st
speed_test: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS) $(SDL_CFLAGS) $(LDFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)
	

main.o : main.cc
	$(CXX) $(CXXFLAGS) $(MAIN_CFLAGS) -c main.cc $(SDL_CFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

Parser.o : Parser.h Parser.cc
	$(CXX) $(CXXFLAGS) -c Parser.cc $(BOOST_LDFLAGS)

Image.o : Image.cc Image.h
	$(CXX) $(CXXFLAGS) -c Image.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Transformation.o : Transformation.cc Transformation.h Image.h
	$(CXX) $(CXXFLAGS) -c Transformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

BrightnessTransformation.o : BrightnessTransformation.cc BrightnessTransformation.h Image.h
	$(CXX) $(CXXFLAGS) -c BrightnessTransformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

NegativeTransformation.o : NegativeTransformation.cc NegativeTransformation.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c NegativeTransformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContrastTransformation.o : ContrastTransformation.cc ContrastTransformation.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c ContrastTransformation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

VerticalFlip.o : VerticalFlip.cc VerticalFlip.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c VerticalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

HorizontalFlip.o : HorizontalFlip.cc HorizontalFlip.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c HorizontalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

DiagonalFlip.o: DiagonalFlip.cc DiagonalFlip.h HorizontalFlip.h VerticalFlip.h Image.h
	$(CXX) $(CXXFLAGS) -c DiagonalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Resize.o : Resize.cc Resize.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c Resize.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContramorphicMeanFilter.o : ContramorphicMeanFilter.cc ContramorphicMeanFilter.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c ContramorphicMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

AlphaTrimmedMeanFilter.o : AlphaTrimmedMeanFilter.cc AlphaTrimmedMeanFilter.h Image.h Transformation.h
	$(CXX) $(CXXFLAGS) -c AlphaTrimmedMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

.PHONY : clean_compilation_type
clean_compilation_type :
	rm main.o
