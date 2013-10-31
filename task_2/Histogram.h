#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include "Image.h"
#include <map>

class Histogram
{
public:
  Histogram(Image &image);

  enum Channel { R, G, B, A };

  void print_channel(Channel c);

  double cmean(Channel c);
  double cvariance(Channel c);
  double cstdev(Channel c);
  double cvarcoi(Channel c);
  double casyco(Channel c);
  double cflato(Channel c);
  double cvarcoii(Channel c);
  double centropy(Channel c);

  void save_as_image(Channel c, const std::string &filename);

private:
  uint64_t pixels_r[256] = {0};
  uint64_t pixels_g[256] = {0};
  uint64_t pixels_b[256] = {0};
  uint64_t pixels_a[256] = {0};

  uint64_t n_pixels;

};

#endif
