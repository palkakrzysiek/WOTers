#include "Image.h"
#include "Parser.h"
#include "Operations.h"
#include "Histogram.h"
#include <iostream>
#include <string>
#include <cassert>

#ifdef _SPEED_TEST
#include <sys/time.h>
#include <cstdint>
#include <iomanip>
static uint64_t now() {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    abort();

  return tv.tv_sec * 1000000ULL + tv.tv_usec;
}
#endif

using namespace std;

int main(int argc, char** argv)
{

  bool imageChanged = true;

  using namespace std;

  Parser p(argc, argv);

  Image img(p.getFilename());
  Histogram hist(img);
  Histogram::Channel channel = Histogram::Channel::ALL;

  Operation *o = nullptr;

  if (p.setChannel())
  {
    channel = (Histogram::Channel) p.getChannel();
  }
  else
  {
    channel = Histogram::Channel::ALL;
  }

  if (img.get_surface()->format->BitsPerPixel == 8)
  {
    channel = Histogram::Channel::R;
  }

  if (p.setBrightness())
  {
    o = new BrightnessAdjustment(p.getBrightnessValue());
  }

  if (p.setResize())
  {
    o = new Resize(p.getResizeValue());
  }

  if (p.setContrast())
  {
    o = new ContrastAdjustment(p.getContrastValue());
  }

  if (p.setNegative())
  {
    o = new Negative();
  }

  if (p.setHflip())
  {
    o = new HorizontalFlip();
  }

  if (p.setVflip())
  {
    o = new VerticalFlip();
  }

  if (p.setDflip())
  {
    o = new DiagonalFlip();
  }

  if (p.setCmean())
  {
    o = new ContraharmonicMeanFilter(p.getCmeanValue());
  }

  if (p.setAlpha())
  {
    o = new AlphaTrimmedMeanFilter(p.getAlphaValue());
  }

  if (p.setCmean())
  {
    o = new ContraharmonicMeanFilter(p.getCmeanValue());
  }

  if (p.setLowPass())
  {
    o = new LowPassFilter();
  }

  if (p.setRosenfeld())
  {
    o = new RosenfeldOperator(p.getRosenfeldP());
  }

  if (p.setRaleigh())
  {
    // if (channel == Histogram::Channel::ALL && img.get_surface()->format->BitsPerPixel != 8)
    // {
    //   std::cerr << "You must specify channel (--channel)" << std::endl;
    //   exit(1);
    // }
    // else if (img.get_surface()->format->BitsPerPixel == 8)
    // {
    //   channel = Histogram::Channel::R;
    // }

    o = new RaleighFPDF(channel, p.getRaleighAlpha());
  }

  double result = 0.0;

  if (p.setMse())
  {
    imageChanged = false;
    Image filtered(p.getMseFilename());
    img.perform_operation(new MeanSquareError(&filtered, &result));
    cout << result << endl;
  }

  if (p.setPmse())
  {
    imageChanged = false;
    Image filtered(p.getPmseFilename());
    img.perform_operation(new PeakMeanSquareError(&filtered, &result));
    cout << result << endl;
  }

  if (p.setSnr())
  {
    imageChanged = false;
    Image filtered(p.getSnrFilename());
    img.perform_operation(new SignalToNoiseRatio(&filtered, &result));
    cout << result << endl;
  }
  if (p.setPsnr())
  {
    imageChanged = false;
    Image filtered(p.getPsnrFilename());
    img.perform_operation(new PeakSignalToNoiseRatio(&filtered, &result));
    cout << result << endl;
  }

  if (p.setMd())
  {
    imageChanged = false;
    Image filtered(p.getMdFilename());
    img.perform_operation(new MaxDifference(&filtered, &result));
    cout << result << endl;
  }

  if (p.setCmeanh())
  {
    imageChanged = false;
    cout << hist.cmean(channel) << endl;
  }

  if (p.setCvariance())
  {
    imageChanged = false;
    cout << hist.cvariance(channel) << endl;
  }

  if (p.setCstdev())
  {
    imageChanged = false;
    cout << hist.cstdev(channel) << endl;
  }

  if (p.setCvarcoii())
  {
    imageChanged = false;
    cout << hist.cvarcoii(channel) << endl;
  }

  if (p.setCvarcoi())
  {
    imageChanged = false;
    cout << hist.cvarcoi(channel) << endl;
  }

  if (p.setCasyco())
  {
    imageChanged = false;
    cout << hist.casyco(channel) << endl;
  }

  if (p.setCflatco())
  {
    imageChanged = false;
    cout << hist.cflatco(channel) << endl;
  }

  if (p.setCentropy())
  {
    imageChanged = false;
    cout << hist.centropy(channel) << endl;
  }

  if (p.setHistogram())
  {
    // if (channel == Histogram::Channel::ALL && img.get_surface()->format->BitsPerPixel != 8)
    // {
    //   std::cerr << "You must specify channel (--channel)" << std::endl;
    //   exit(1);
    // }
    if (img.get_surface()->format->BitsPerPixel == 8)
    {
      channel = Histogram::Channel::R;
    }

    imageChanged = false;
    hist.save_as_image(channel, p.getHistogramFilename());
  }

  if (imageChanged) {
    assert(o != nullptr);
  }

#ifdef _SPEED_TEST
  uint64_t timer = now();
#endif
  if (imageChanged) {
    img.perform_operation(new Binarize());
  }

#ifdef _SPEED_TEST
  timer = now() - timer;
  printf("%gs\n", (double)timer/1e6);
#endif

#ifndef _SPEED_TEST // saving the file during speed test is just the waste of time
  if (imageChanged) {
    img.save(p.getOutFilename());
  }
#endif
      
  return 0;
}
