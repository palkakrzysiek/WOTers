CXX=g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -Wextra -pedantic -fopenmp -I../libimage/
MAIN_CFLAGS=
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_image
BOOST_LDFLAGS=-lboost_program_options
OBJECTS=main.o Parser.o Image.o Operation.o BrightnessAdjustment.o ContrastAdjustment.o DiagonalFlip.o VerticalFlip.o HorizontalFlip.o Negative.o Resize.o AlphaTrimmedMeanFilter.o ContraharmonicMeanFilter.o MeanSquareError.o PeakMeanSquareError.o SignalToNoiseRatio.o PeakSignalToNoiseRatio.o MaxDifference.o
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

Image.o :
	$(CXX) $(CXXFLAGS) -c ../libimage/Image.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Operation.o :
	$(CXX) $(CXXFLAGS) -c ../libimage/Operation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

BrightnessAdjustment.o :
	$(CXX) $(CXXFLAGS) -c BrightnessAdjustment.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Negative.o :
	$(CXX) $(CXXFLAGS) -c Negative.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContrastAdjustment.o :
	$(CXX) $(CXXFLAGS) -c ContrastAdjustment.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

VerticalFlip.o :
	$(CXX) $(CXXFLAGS) -c VerticalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

HorizontalFlip.o :
	$(CXX) $(CXXFLAGS) -c HorizontalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

DiagonalFlip.o:
	$(CXX) $(CXXFLAGS) -c DiagonalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Resize.o :
	$(CXX) $(CXXFLAGS) -c Resize.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContraharmonicMeanFilter.o :
	$(CXX) $(CXXFLAGS) -c ContraharmonicMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

AlphaTrimmedMeanFilter.o :
	$(CXX) $(CXXFLAGS) -c AlphaTrimmedMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

MeanSquareError.o :
	$(CXX) $(CXXFLAGS) -c MeanSquareError.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)	

PeakMeanSquareError.o :
	$(CXX) $(CXXFLAGS) -c PeakMeanSquareError.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)	

SignalToNoiseRatio.o :
	$(CXX) $(CXXFLAGS) -c SignalToNoiseRatio.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)	

PeakSignalToNoiseRatio.o :
	$(CXX) $(CXXFLAGS) -c PeakSignalToNoiseRatio.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

MaxDifference.o :
	$(CXX) $(CXXFLAGS) -c MaxDifference.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)	

.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

.PHONY : clean_compilation_type
clean_compilation_type :
	rm main.o
