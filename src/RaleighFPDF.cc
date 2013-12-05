#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cassert>

RaleighFPDF::RaleighFPDF(Histogram::Channel c, const std::pair<int, int> &minmax)
  : channel(c),
    g_min(minmax.first),
    g_max(minmax.second)
{
}

void RaleighFPDF::perform(Image &image)
{
  assert(g_min < g_max);

  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  // Image improved(image);
  Histogram hist(image);

  int i, j;

  double rs[256], gs[256], bs[256];

  rs[0] = hist.get_r()[0];
  gs[0] = hist.get_g()[0];
  bs[0] = hist.get_b()[0];

// no parallel
  for (i = 1; i <= 255; ++i)
  {
    rs[i] = rs[i-1] + hist.get_r()[i];
    gs[i] = gs[i-1] + hist.get_g()[i];
    bs[i] = bs[i-1] + hist.get_b()[i];
  }

  double alpha[3] = {0.0};
  uint32_t H_0;

  if (channel == Histogram::Channel::R || channel == Histogram::Channel::ALL)
  {
    // alpha for red
    if (hist.get_r()[0] == 0)
      H_0 = 1;
    else
      H_0 = hist.get_r()[0];

    alpha[0] = std::pow(g_max - g_min, 2);
    alpha[0] /= -2.0 * std::log((double) H_0 / (w * h));
    alpha[0] = sqrt(alpha[0]);
  }

  if (channel == Histogram::Channel::G || channel == Histogram::Channel::ALL)
  {
    // alpha for green
    if (hist.get_g()[0] == 0)
      H_0 = 1;
    else
      H_0 = hist.get_g()[0];

    alpha[1] = std::pow(g_max - g_min, 2);
    alpha[1] /= -2.0 * std::log((double) H_0 / (w * h));
    alpha[1] = sqrt(alpha[1]);
  }

  if (channel == Histogram::Channel::B || channel == Histogram::Channel::ALL)
  {
    // alpha for blue
    if (hist.get_b()[0] == 0)
      H_0 = 1;
    else
      H_0 = hist.get_b()[0];

    alpha[2] = std::pow(g_max - g_min, 2);
    alpha[2] /= -2.0 * std::log((double) H_0 / (w * h));
    alpha[2] = sqrt(alpha[2]);
  }

# pragma omp parallel for
  for (i = 0; i <= 255; ++i)
  {
    rs[i] = g_min + sqrt(-2.0 * alpha[0] * alpha[0] * log((double) rs[i] / (w * h)));
    gs[i] = g_min + sqrt(-2.0 * alpha[1] * alpha[1] * log((double) gs[i] / (w * h)));
    bs[i] = g_min + sqrt(-2.0 * alpha[2] * alpha[2] * log((double) bs[i] / (w * h)));
  }

  printf("g_min: %i\n", g_min);
  printf("g_max: %i\n", g_max);
  printf("alpha_r: %f\n", alpha[0]);
  printf("alpha_g: %f\n", alpha[1]);
  printf("alpha_b: %f\n", alpha[2]);

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb[3] = {0};

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &rgb[0], &rgb[1], &rgb[2]);

      if (channel == Histogram::Channel::R)
      {
        rgb[0] = rs[rgb[0]];
        rgb[1] = rgb[2] = rgb[0];
      }
      else if (channel == Histogram::Channel::G)
      {
        rgb[1] = gs[rgb[1]];
        rgb[0] = rgb[2] = rgb[1];
      }
      else if (channel == Histogram::Channel::B)
      {
        rgb[2] = bs[rgb[2]];
        rgb[0] = rgb[1] = rgb[2];
      }
      else if (channel == Histogram::Channel::ALL)
      {
        rgb[0] = rs[rgb[0]];
        rgb[1] = gs[rgb[1]];
        rgb[2] = bs[rgb[2]];
      }

      image.set_pixel(i, j, SDL_MapRGB(image.get_surface()->format,
                         rgb[0], rgb[1], rgb[2]));
    }
  }

  // image = std::move(improved);
}
