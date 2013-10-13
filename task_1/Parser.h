#ifndef __PARSER_H
#define __PARSER_H

#include "boost/program_options.hpp" 

namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
} // namespace 

namespace po = boost::program_options;

class Parser{
    public:
        Parser(int &argc, char** argv);

    private:
        po::options_description desc;
        po::variables_map vm; 
        bool verbose;

    public:

        std::string getFilename();
        std::string getOutFilename();
        bool setBrightness();
        double getBrightnessValue();
        bool setContrast();
        double getContrastValue();
        bool setNegative();

        bool setHflip();
        bool setVflip();
        bool setDflip();
        bool setShrink();
        double getShrinkValue();
        bool setEnlarge();
        double getEnlargeValue();

        bool setAlpha();
        bool setCmean();

        bool setMse();
        bool setPmse();
        bool setSnr();
        bool setPsnr();
        bool setMd();

        bool setBinarize();
};

#endif
