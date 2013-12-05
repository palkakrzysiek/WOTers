#include "PeakMeanSquareError.h"
#include <cstdio> // fprintf
#include <cstdlib> // exit

PeakMeanSquareError::PeakMeanSquareError(Image *f, double *r)
  : filtered(f), result(r)
{
}

void PeakMeanSquareError::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  int bpp = image.get_surface()->format->BytesPerPixel;

  if (filtered->get_surface()->w != w || filtered->get_surface()->h != h
      || filtered->get_surface()->format->BytesPerPixel != bpp)
  {
    fprintf(stderr, "Images are not of the same size or format\n");
    exit(1);
  }

  uint8_t max_r = 0, max_g = 0, max_b = 0;

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b;

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                  &r, &g, &b);

      if (r > max_r)
        max_r = r;

      if (g > max_g)
        max_g = g;

      if (b > max_b)
        max_b = b;
    }
  }

  double r = 0.0, g = 0.0, b = 0.0;

# pragma omp parallel for private(i) default(shared) reduction(+:r,g,b)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgba1[3],
              rgba2[3];

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                  &rgba1[0], &rgba1[1], &rgba1[2]);
      SDL_GetRGB(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgba2[0], &rgba2[1], &rgba2[2]);

      r += (rgba1[0] - rgba2[0]) * (rgba1[0] - rgba2[0]);
      g += (rgba1[1] - rgba2[1]) * (rgba1[1] - rgba2[1]);
      b += (rgba1[2] - rgba2[2]) * (rgba1[2] - rgba2[2]);
    }
  }

  r /= max_r * max_r;
  g /= max_g * max_g;
  b /= max_b * max_b;

  r /= w * h;
  g /= w * h;
  b /= w * h;

  *result = (r + g + b) / 3.0;
}
