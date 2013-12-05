#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include "Image.h"
#include <map>

class Histogram
{
public:
  Histogram(Image &image);

  enum Channel { R = 0, G = 1, B = 2, A = 3, ALL = 4};

  void print_channel(Channel c);

  double cmean(Channel c = ALL);
  double cvariance(Channel c = ALL);
  double cstdev(Channel c = ALL);
  double cvarcoi(Channel c = ALL);
  double casyco(Channel c = ALL);
  double cflatco(Channel c = ALL);
  double cvarcoii(Channel c = ALL);
  double centropy(Channel c = ALL);

  void save_as_image(Channel c, const std::string &filename);

  const uint32_t* get_r();
  const uint32_t* get_g();
  const uint32_t* get_b();
  const uint32_t* get_a();

private:
  uint32_t pixels_r[256] = {0};
  uint32_t pixels_g[256] = {0};
  uint32_t pixels_b[256] = {0};
  uint32_t pixels_a[256] = {0};

  uint32_t n_pixels;
  bool grayscale;

};

#endif
