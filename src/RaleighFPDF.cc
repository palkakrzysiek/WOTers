#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>

RaleighFPDF::RaleighFPDF(double a)
  : alpha(a)
{
}

void RaleighFPDF::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image improved(image);
  Histogram hist(image);

  uint64_t g_min[3] = {255};

  double sum_r, sum_g, sum_b;

  int i, j;

# pragma omp parallel for private(i) reduction(+:sum_r,sum_g,sum_b)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb[3], rgb2[3] = {0};
      sum_r = 0.0;
      sum_g = 0.0;
      sum_b = 0.0;

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &rgb[0], &rgb[1], &rgb[2]);

      // finding g_min
      if (rgb[0] < g_min[0])
        g_min[0] = rgb[0];

      if (rgb[1] < g_min[1])
        g_min[1] = rgb[1];

      if (rgb[2] < g_min[2])
        g_min[2] = rgb[2];

      for (int l = 0; l <= rgb[0]; ++l)
      {
        sum_r += hist.get_r()[l];
      }

      sum_r /= w * h;

      for (int l = 0; l <= rgb[1]; ++l)
      {
        sum_g += hist.get_g()[l];
      }

      sum_g /= w * h;

      for (int l = 0; l <= rgb[2]; ++l)
      {
        sum_b += hist.get_b()[l];
      }

      sum_b /= w * h;

      rgb2[0] = trunc(g_min[0] + sqrt(2 * alpha * alpha * pow(sum_r, -1)));
      rgb2[1] = trunc(g_min[1] + sqrt(2 * alpha * alpha * pow(sum_g, -1)));
      rgb2[2] = trunc(g_min[2] + sqrt(2 * alpha * alpha * pow(sum_b, -1)));

      improved.set_pixel(i, j, SDL_MapRGB(improved.get_surface()->format,
                         rgb[0], rgb[1], rgb[2]));
    }
  }

  image = std::move(improved);
}
