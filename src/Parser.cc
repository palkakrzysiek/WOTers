#include "Parser.h"
#include "boost/program_options.hpp" 


Parser::Parser(int &argc, char** argv)
    : desc("Options")
{
    // http://www.boost.org/doc/libs/1_54_0/doc/html/program_options/tutorial.html
    namespace po = boost::program_options;
    // po::options_description desc("Options"); 

    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", "rant and rave")
        ("file,f", po::value<std::string>()->required(),
         "input file")
        ("output,o", po::value<std::string>()->default_value("out.bmp"),
         "output file")
        ("brightness,b", po::value<double>(),
         "modify brightness (in percents) [-100:100]")
        ("contrast,c", po::value<double>(),
         "modify contrast (in percents) [-100:100]")
        ("negative,n", "invert values of colors")

        ("Hflip", "Horizontal Flip")
        ("Vflip", "Vertical Flip")
        ("Dflip", "Diagonal Flip")
        ("resize,r", po::value<double>(),
         "resize by percent of original image [greater then 0]")

        ("alpha", po::value<int>(), "Alpha Trimmed Mean Filter [0, 2, 4, 6, 8]")
        ("cmean", po::value<double>(), "contraharmonic mean filter [floating point value]")

        ("slowpass", "Low-pass filter")

        ("mse", po::value<std::string>(),
         "Mean square error")
        ("pmse", po::value<std::string>(),
        "Peak mean sqare error")
        ("snr", po::value<std::string>(),
         "Signal to noise ratio")
        ("psnr", po::value<std::string>(),
         "Peak signal to noise ratio")
        ("md", po::value<std::string>(),
         "Maximum difference");

    try 
    { 
        po::store(po::parse_command_line(argc, argv, desc),  vm); // can throw 

        /** --help option */ 
        if ( vm.count("help")  ) 
        { 
            std::cout << "Command Line Image processing tool" << std::endl 
                << desc << std::endl; 
            exit(0);
        } 

        if ( !vm.count("file")  ) 
        { 
            std::cout << "Name of the file must be given\n\
Command Line Image processing tool" << std::endl 
                << desc << std::endl; 
            exit(0);
        } 

        if ( vm.count("resize") && vm["resize"].as<double>() <= 0) 
        { 
            std::cout << "Value of resize argument must by positive! \n\
Command Line Image processing tool" << std::endl 
                << desc << std::endl; 
            exit(0);
        } 
        po::notify(vm); // throws on error, so do after help in case 
        // there are any problems 
    } 
    catch(po::error& e) 
    { 
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
        std::cerr << desc << std::endl; 
        exit(1);
    } 


}

std::string Parser::getFilename()
{
    return vm["file"].as<std::string>();
}

std::string Parser::getOutFilename()
{
    return vm["output"].as<std::string>();
}

bool Parser::setBrightness()
{
    return vm.count("brightness");
}
double Parser::getBrightnessValue()
{
    if (vm.count("verbose") && (vm["brightness"].as<double>() > 100 ||
                                vm["brightness"].as<double>() < -100)) {
        std::cout << "Brightness value is very close to or exceeds margin val.\n";
    }
    return (vm["brightness"].as<double>() / 100.0);
}

bool Parser::setContrast()
{
    return vm.count("contrast");
}
double Parser::getContrastValue()
{
    if (vm.count("verbose") && (vm["contrast"].as<double>() > 100 ||
                                vm["contrast"].as<double>() < -100)) {
        std::cout << "Contrast value is very close to or exceeds margin val.\n";
    }
    return vm["contrast"].as<double>() / 100.0;;
}

bool Parser::setNegative()
{
    return vm.count("negative");
}

bool Parser::setHflip()
{
    return vm.count("Hflip");
}

bool Parser::setVflip()
{
    return vm.count("Vflip");
}

bool Parser::setDflip()
{
    return vm.count("Dflip");
}

bool Parser::setResize()
{
    return vm.count("resize");
}
double Parser::getResizeValue()
{
    return vm["resize"].as<double>() / 100.0;
}


bool Parser::setAlpha()
{
    return vm.count("alpha");
}

int Parser::getAlphaValue()
{
    int tempVal = vm["alpha"].as<int>();
    if (tempVal < 0 || tempVal > 8 || tempVal % 2 != 0){
        std::cerr << "Value of Alpha Trimmed Mean Filter must be \
0, 2, 4, 6 or 8. Exiting..." << std::endl;
        exit(1);
    }
    return tempVal;
}

bool Parser::setCmean()
{
    return vm.count("cmean");
}

double Parser::getCmeanValue(){
    return vm["cmean"].as<double>();
}

bool Parser::setLowPass()
{
    return vm.count("slowpass");
}

bool Parser::setMse()
{
    return vm.count("mse");
}

std::string Parser::getMseFilename()
{
    return vm["mse"].as<std::string>();
}

bool Parser::setPmse()
{
    return vm.count("pmse");
}

std::string Parser::getPmseFilename()
{
    return vm["pmse"].as<std::string>();
}

bool Parser::setSnr()
{
    return vm.count("snr");
}

std::string Parser::getSnrFilename()
{
    return vm["snr"].as<std::string>();
}

bool Parser::setPsnr()
{
    return vm.count("psnr");
}

std::string Parser::getPsnrFilename()
{
    return vm["psnr"].as<std::string>();
}

bool Parser::setMd()
{
    return vm.count("md");
}

std::string Parser::getMdFilename()
{
    return vm["md"].as<std::string>();
}
