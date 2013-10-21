#include "PeakMeanSquareError.h"
#include <cstdio> // fprintf
#include <cstdlib> // exit
#include <cmath> // std::pow
#include <cstring> // memset

PeakMeanSquareError::PeakMeanSquareError(Image *f, double *r)
  : filtered(f), result(r)
{
}

void PeakMeanSquareError::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  int bpp = image.get_surface()->format->BytesPerPixel;

  if (filtered->get_surface()->w != w && filtered->get_surface()->h != h 
      && filtered->get_surface()->format->BytesPerPixel != bpp)
  {
    fprintf(stderr, "Images are not of the same size or format\n");
    exit(1);
  }

  uint8_t max_r, max_g, max_b, max_a;

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &r, &g, &b, &a);

      if (r > max_r)
        max_r = r;

      if (g > max_g)
        max_g = g;

      if (b > max_b)
        max_b = b;

      if (a > max_a)
        max_a = a;
    }
  }

  double r = 0.0, g = 0.0, b = 0.0, a = 0.0;

# pragma omp parallel for private(i) default(shared) reduction(+:r,g,b,a)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgba1[4],
              rgba2[4];

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &rgba1[0], &rgba1[1], &rgba1[2], &rgba1[3]);
      SDL_GetRGBA(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgba2[0], &rgba2[1], &rgba2[2], &rgba2[3]);

#     pragma omp flush(r)
      r += std::pow(rgba1[0] - rgba2[0], 2);

#     pragma omp flush(g)
      g += std::pow(rgba1[1] - rgba2[1], 2);

#     pragma omp flush(b)
      b += std::pow(rgba1[2] - rgba2[2], 2);

#     pragma omp flush(a)
      a += std::pow(rgba1[3] - rgba2[3], 2);

    }
  }

  r /= std::pow(max_r, 2);
  g /= std::pow(max_g, 2);
  b /= std::pow(max_b, 2);
  a /= std::pow(max_a, 2);

  r /= w * h;
  g /= w * h;
  b /= w * h;
  a /= w * h;

  *result = (r + g + b + a) / bpp;
}
