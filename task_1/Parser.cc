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
         "input file")
        ("brightness,b", po::value<double>(),
         "modify brightness (in percents) [-100:100]")
        ("contrast,c", po::value<double>(),
         "modify contrast (in percents) [-100:100]")
        ("negative,n", "invert values of colors")

        ("Hfilp", "temp_msg")
        ("Vflip", "temp_msg")
        ("Dflip", "temp_msg")
        ("shrink,s", po::value<double>(),
         "shrink by percent [-100:100]")
        ("enlarge,e", po::value<double>(),
         "enlarge by percent [-100:100]")

        ("alpha", "temp_msg")
        ("cmean", "temp_msg")
        ("mse", "temp_msg")
        ("pmse", "temp_msg")
        ("snr", "temp_msg")
        ("psnr", "temp_msg")
        ("md", "temp_msg");

    bool verbose = false;

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
    return vm["brightness"].as<double>();
}

bool Parser::setContrast()
{
    return vm.count("contrast");
}
double Parser::getContrastValue()
{
    return vm["contrast"].as<double>();
}

bool Parser::setNegative()
{
    return vm.count("negative");
}

bool Parser::setHflip()
{
    return vm.count("Hfilp");
}

bool Parser::setVflip()
{
    return vm.count("Vflip");
}

bool Parser::setDflip()
{
    return vm.count("Dflip");
}
