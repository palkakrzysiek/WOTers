#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include "Image.h"
#include <map>

class Histogram
{
public:
  Histogram(Image &image);

private:
  uint64_t pixels_r[256] = {0};
  uint64_t pixels_g[256] = {0};
  uint64_t pixels_b[256] = {0};
  uint64_t pixels_a[256] = {0};

};

#endif
