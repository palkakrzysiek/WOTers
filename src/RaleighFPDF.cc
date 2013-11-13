#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>

RaleighFPDF::RaleighFPDF(Histogram::Channel c, double a)
  : channel(c),
    alpha(a)
{
}

void RaleighFPDF::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image improved(image);
  Histogram hist(image);

  uint16_t g_min_r = 255, g_min_g = 255, g_min_b = 255;

  double sum_r, sum_g, sum_b;

  int i, j;

# pragma omp parallel for private(i) shared(g_min_r,g_min_g,g_min_b) reduction(+:sum_r,sum_g,sum_b)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb[3], rgb2[3] = {0};
      sum_r = 0.0;
      sum_g = 0.0;
      sum_b = 0.0;
      // double sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &rgb[0], &rgb[1], &rgb[2]);

// #     pragma omp critical
      {
      // finding g_min
      if (rgb[0] < g_min_r)
        g_min_r = rgb[0];

      if (rgb[1] < g_min_g)
        g_min_g = rgb[1];

      if (rgb[2] < g_min_b)
        g_min_b = rgb[2];
      }


      rgb2[0] = rgb[0];
      rgb2[1] = rgb[1];
      rgb2[2] = rgb[2];

      if (channel == Histogram::Channel::R)
      {
        for (int l = 0; l <= rgb[0]; ++l)
        {
          sum_r += hist.get_r()[l];
        }
        sum_r /= w * h;
        rgb2[0] = trunc(g_min_r + sqrt(-2.0 * alpha * alpha * log(sum_r)));
      }
      else if (channel == Histogram::Channel::G)
      {
        for (int l = 0; l <= rgb[1]; ++l)
        {
          sum_g += hist.get_g()[l];
        }
        sum_g /= w * h;
        rgb2[1] = trunc(g_min_g + sqrt(-2.0 * alpha * alpha * log(sum_g)));
      }
      else if (channel == Histogram::Channel::B)
      {
        for (int l = 0; l <= rgb[2]; ++l)
        {
          sum_b += hist.get_b()[l];
        }
        sum_b /= w * h;
        rgb2[2] = trunc(g_min_b + sqrt(-2.0 * alpha * alpha * log(sum_b)));
      }
      else if (channel == Histogram::Channel::ALL)
      {
        for (int l = 0; l <= rgb[0]; ++l)
        {
          sum_r += hist.get_r()[l];
        }
        sum_r /= w * h;
        rgb2[0] = trunc(g_min_r + sqrt(-2.0 * alpha * alpha * log(sum_r)));

        for (int l = 0; l <= rgb[1]; ++l)
        {
          sum_g += hist.get_g()[l];
        }
        sum_g /= w * h;
        rgb2[1] = trunc(g_min_g + sqrt(-2.0 * alpha * alpha * log(sum_g)));

        for (int l = 0; l <= rgb[2]; ++l)
        {
          sum_b += hist.get_b()[l];
        }
        sum_b /= w * h;
        rgb2[2] = trunc(g_min_b + sqrt(-2.0 * alpha * alpha * log(sum_b)));
      }

      improved.set_pixel(i, j, SDL_MapRGB(improved.get_surface()->format,
                         rgb2[0], rgb2[1], rgb2[2]));
    }
  }

  image = std::move(improved);
}
