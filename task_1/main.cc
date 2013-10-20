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
        o = new AlphaTrimmedMeanFilter(p.getAlphaValue());
    }
    assert(o != nullptr);

#ifdef _SPEED_TEST
    uint64_t timer = now();
#endif

    img.perform_operation(o);

#ifdef _SPEED_TEST
    timer = now() - timer;
    printf("%gs\n", (double)timer/1e6);
#endif
  
#ifndef _SPEED_TEST // saving the file during speed test is just the waste of time
    img.save(p.getOutFilename());
#endif
        
    return 0;
}
