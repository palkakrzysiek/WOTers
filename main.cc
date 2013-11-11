#include "Image.h"
#include "Parser.h"
#include "Operations.h"
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
    Operation *o = nullptr;

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
        o = new RosenfeldOperator(p.getAlphaValue());
    }

    if (p.setCmean())
    {
        o = new ContraharmonicMeanFilter(p.getCmeanValue());
    }

    if (p.setLowPass())
    {
        o = new LowPassFilter();
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


    if (imageChanged) {
        assert(o != nullptr);
    }

#ifdef _SPEED_TEST
    uint64_t timer = now();
#endif
    if (imageChanged) {
        img.perform_operation(o);
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
