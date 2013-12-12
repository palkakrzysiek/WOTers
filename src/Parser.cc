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
    //("histogram", po::value<std::string>(), "Save histogram to file");
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
    ("orosenfeld", po::value<int>(), "Rosenfeld operator [1, 2, 4, 8, 16, ..]")

    ("mse", po::value<std::string>(),
     "Mean square error")
    ("pmse", po::value<std::string>(),
     "Peak mean sqare error")
    ("snr", po::value<std::string>(),
     "Signal to noise ratio")
    ("psnr", po::value<std::string>(),
     "Peak signal to noise ratio")
    ("md", po::value<std::string>(),
     "Maximum difference")

    ("hraleigh", po::value<std::vector<int>>()->multitoken(), "Raleigh [min max]")

    ("channel", po::value<std::string>(), "Channel [R, G, B]")

    ("cmeanh", "Mean")
    ("cvariance", "Variance")
    ("cstdev", "Standard deviation")
    ("cvarcoi", "Variation coefficient I")
    ("cvarcoii", "Variation coefficient II")
    ("casyco", "Asymmetry coefficient")
    ("cflatco", "Flattening coefficient")
    ("centropy", "Information source entropy")

    ("histogram", po::value<std::string>(), "save histogram to a file")


    ("erosion", "Erosion Transformation")
    ("dilation", "Dilation Transformation")
    ("opening", "Opening Transformation")
    ("closing", "Closing Transformation")
    ("hmt", "Hit-or-Miss Transformation")
    ("mask", po::value<int>(), "Mask for morphological transformation")
    ("thinning", "Thinning operation - get the skeleton")
    ("pruning", po::value<int>(), "Remove parasitic component from skeleton")
    ("rgrow", po::value<int>(), "Region growing, seed as parameter")
    ("threshold", po::value<int>(), "Border of threshold");


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
  return vm["contrast"].as<double>() / 100.0;
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

bool Parser::setRosenfeld()
{
  return vm.count("orosenfeld");
}

int Parser::getRosenfeldP()
{
  int temp = vm["orosenfeld"].as<int>();
  if (temp != 0 && (temp & (temp - 1)) != 0) {
    std::cerr << "Argument of ==orosenfeld must be 1, 2, 4, 8, 16...\n";
    exit(1);
  }
  return vm["orosenfeld"].as<int>();
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

bool Parser::setRaleigh()
{
  return vm.count("hraleigh");
}

std::pair<int, int> Parser::getRaleighMinMax()
{
  auto vect = vm["hraleigh"].as<std::vector<int>>();

  if (vect.size() != 2 /* && 0 <= value <= 255 */)
  {
    std::cerr << "You must specify min and max" << std::endl;
    exit(1);
  }

  return std::make_pair(vect[0], vect[1]);
}

bool Parser::setChannel()
{
  return vm.count("channel");
}

int Parser::getChannel()
{
  std::string channel = vm["channel"].as<std::string>();

  if (channel == "R")
    return 0;
  else if (channel == "G")
    return 1;
  else if (channel == "B")
    return 2;
  else if (channel == "A")
    return 3;
  else
  {
    std::cerr << "Invalid channel specified" << std::endl;
    exit(1);
  }

  return 4;
}

bool Parser::setCmeanh()
{
  return vm.count("cmeanh");
}

bool Parser::setCvariance()
{
  return vm.count("cvariance");
}

bool Parser::setCstdev()
{
  return vm.count("cstdev");
}

bool Parser::setCvarcoi()
{
  return vm.count("cvarcoi");
}

bool Parser::setCvarcoii()
{
  return vm.count("cvarcoii");
}

bool Parser::setCasyco()
{
  return vm.count("casyco");
}

bool Parser::setCflatco()
{
  return vm.count("cflatco");
}

bool Parser::setCentropy()
{
  return vm.count("centropy");
}

bool Parser::setHistogram()
{
  return vm.count("histogram");
}

std::string Parser::getHistogramFilename()
{
  return vm["histogram"].as<std::string>();
}

bool Parser::setErosion()
{
  return vm.count("erosion");
}

bool Parser::setDilation()
{
  return vm.count("dilation");
}

bool Parser::setOpening()
{
  return vm.count("opening");
}

bool Parser::setClosing()
{
  return vm.count("closing");
}

bool Parser::setHMT()
{
  return vm.count("hmt");
}

bool Parser::setThinning()
{
  return vm.count("thinning");
}

bool Parser::setPruning()
{
  return vm.count("pruning");
}

int Parser::getPruningValue()
{
  int val = vm["pruning"].as<int>();
  if (val < 1) {
    std::cerr << "Minimum length to prune is 1";
    exit(1);
  }
  return val;
}

bool Parser::setRegionGrowing() {
  return vm.count("rgrow");
}
int Parser::getRegionValue(){
  int val = vm["rgrow"].as<int>();
  if (val > 255 || val < 0) {
    std::cerr << "Value of seeds must be in range [0:255]";
    exit(1);
  }
  return val;
}
bool Parser::setThreshold() {
   return vm.count("threshold");
}
int Parser::getTrescholdValue() {
  int val = vm["threshold"].as<int>();
  if (val > 255 || val < 0) {
    std::cerr << "Value of threshold must be in range [0:255]";
    exit(1);
  }
  return val;
}

int Parser::getMask()
{
  int val;
  if (!vm.count("mask")) {
    std::cerr << "Possible masks are numbered from 1 to 28, setting 9\n";
    val = 9 - 1; // masks are counted form 0, not from 1
  } else {
    val = vm["mask"].as<int>() - 1;
    if (val < 0 || val > 27) {
      std::cerr << "Possible masks are numbered from 1 to 28\n";
      exit(1);
    }
  }
  return val;
}
