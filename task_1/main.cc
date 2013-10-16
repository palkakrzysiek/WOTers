#include "Image.h"
#include "Parser.h"
#include "Transformations.h"
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
    Transformation *t = nullptr;

    if (p.setBrightness())
    {
        t = new BrightnessTransformation(p.getBrightnessValue());
    }

    if (p.setResize())
    {
        t = new Resize(p.getResizeValue());
    }

    if (p.setContrast())
    {
        t = new ContrastTransformation(p.getContrastValue());
    }

    if (p.setNegative())
    {
        t = new NegativeTransformation();
    }

    if (p.setHflip())
    {
        t = new HorizontalFlip();
    }

    if (p.setVflip())
    {
        t = new VerticalFlip();
    }

    if (p.setDflip())
    {
        t = new DiagonalFlip();
    }

    assert(t != nullptr);

#ifdef _SPEED_TEST
    uint64_t timer = now();
#endif

    img.apply_transformation(t);

#ifdef _SPEED_TEST
    timer = now() - timer;
    printf("%gs\n", (double)timer/1e6);
#endif
  
#ifndef _SPEED_TEST // saving the file during speed test is just the waste of time
    img.save(p.getOutFilename());
#endif
        
    return 0;
}
