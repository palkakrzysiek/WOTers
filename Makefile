CXX?=g++
CXXFLAGS=-g -O2 -march=native -std=c++11 -Wall -Wextra -pedantic -fopenmp
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image
BOOST_LDFLAGS=-lboost_program_options
SOURCES=src/main.cc \
	src/Parser.cc \
	src/Histogram.cc \
	src/Image.cc \
	src/Operation.cc \
	src/BrightnessAdjustment.cc \
	src/ContrastAdjustment.cc \
	src/DiagonalFlip.cc \
	src/VerticalFlip.cc \
	src/HorizontalFlip.cc \
	src/Negative.cc \
	src/Resize.cc \
	src/AlphaTrimmedMeanFilter.cc \
	src/ContraharmonicMeanFilter.cc \
	src/MeanSquareError.cc \
	src/PeakMeanSquareError.cc \
	src/SignalToNoiseRatio.cc \
	src/PeakSignalToNoiseRatio.cc \
	src/MaxDifference.cc \
	src/RaleighFPDF.cc \
	src/RosenfeldOperator.cc \
	src/LowPassFilter.cc \
	src/ConvertToGrayscale.cc \
	src/Binarize.cc \
	src/Erosion.cc \
	src/Dilation.cc \
	src/Opening.cc \
	src/Closing.cc \
	src/HMT.cc \
	src/Thinning.cc \
	src/RegionGrowing.cc \
	src/Pruning.cc \
	src/ComplexImage.cc \
	src/DFT.cc \
	src/FFT.cc \
	src/FFT1D.cc \
	src/FreqDomain.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=imgproc

.PHONY: all
all: $(EXECUTABLE)

speed_test: MAIN_CFLAGS+= -D_SPEED_TEST
speed_test: EXECUTABLE=program2_st
speed_test: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS) -o $(EXECUTABLE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: clean_compilation_type
clean_compilation_type:
	rm -f main.o

# vim: set tw=0:
