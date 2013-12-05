#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <array>

RaleighFPDF::RaleighFPDF(Histogram::Channel c, const std::pair<int, int> &minmax)
  : channel(c),
    g_min(minmax.first),
    g_max(minmax.second)
{
}

void RaleighFPDF::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image improved(image);
  Histogram hist(image);

  int i, j;

  std::array<double, 256> rs, gs, bs;

  for (i = 0; i <= 255; ++i)
  {
    for (j = 0; j <= i; ++j)
    {
#     pragma omp parallel sections
      {
#       pragma omp section
        {rs[i] += hist.get_r()[i];}
#       pragma omp section
        {gs[i] += hist.get_g()[i];}
#       pragma omp section
        {bs[i] += hist.get_b()[i];}
      }
    }

#   pragma omp parallel sections
    {
#     pragma omp section
      {
        double alpha = 0;
        uint64_t H_0;

        if (hist.get_r()[0] == 0)
          H_0 = 1;
        else
          H_0 = hist.get_r()[0];

        alpha = (double) g_max - g_min;
        alpha = std::pow(alpha, 2);
        alpha /= 2.0 * std::log((double) w * h / H_0);

        rs[i] = g_min + sqrt(-2.0 * alpha * alpha * log(rs[i]));
      }

#     pragma omp section
      {
        double alpha = 0;
        uint64_t H_0;

        if (hist.get_g()[0] == 0)
          H_0 = 1;
        else
          H_0 = hist.get_g()[0];

        alpha = (double) g_max - g_min;
        alpha = pow(alpha, 2);
        alpha /= 2.0 * log((double) w * h / H_0);

        gs[i] = g_min + sqrt(-2.0 * alpha * alpha * log(gs[i]));
      }

#     pragma omp section
      {
        double alpha = 0;
        uint64_t H_0;

        if (hist.get_b()[0] == 0)
          H_0 = 1;
        else
          H_0 = hist.get_b()[0];

        alpha = (double) g_max - g_min;
        alpha = pow(alpha, 2);
        alpha /= 2.0 * log((double) w * h / H_0);

        bs[i] = g_min + sqrt(-2.0 * alpha * alpha * log(bs[i]));
      }
    }
  }

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb[3] = {0};

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &rgb[0], &rgb[1], &rgb[2]);

      if (channel == Histogram::Channel::R || channel == Histogram::Channel::ALL)
      {
        rgb[0] = trunc(rs[rgb[0]]);
      }

      if (channel == Histogram::Channel::G || channel == Histogram::Channel::ALL)
      {
        rgb[1] = trunc(gs[rgb[1]]);
      }

      if (channel == Histogram::Channel::B || channel == Histogram::Channel::ALL)
      {
        rgb[2] = trunc(bs[rgb[2]]);
      }

      improved.set_pixel(i, j, SDL_MapRGB(improved.get_surface()->format,
                         rgb[0], rgb[1], rgb[2]));
    }
  }

  image = std::move(improved);
}
