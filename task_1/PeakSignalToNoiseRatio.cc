#include "PeakSignalToNoiseRatio.h"
#include <cmath>
#include <iostream>

PeakSignalToNoiseRatio::PeakSignalToNoiseRatio(Image *f, double *r)
  : filtered(f), result(r)
{
}

void PeakSignalToNoiseRatio::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  int bpp = image.get_surface()->format->BytesPerPixel;

  if (filtered->get_surface()->w != w || filtered->get_surface()->h != h 
      || filtered->get_surface()->format->BytesPerPixel != bpp)
  {
    fprintf(stderr, "Images are not of the same size\n");
    exit(1);
  }

  int i, j;

  uint8_t max_r = 0, max_g = 0, max_b = 0;


  // finding maximum value for each channel
#pragma omp parallel for private(i) default(shared)
  for(j = 0; j < h; ++j)
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

#pragma omp parallel for private(i) reduction(+:r, g, b)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb1[3], rgb2[3];

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                  &rgb1[0], &rgb1[1], &rgb1[2]);
      SDL_GetRGB(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgb2[0], &rgb2[1], &rgb2[2]);

      r += pow(rgb1[0] - rgb2[0], 2);
      g += pow(rgb1[1] - rgb2[1], 2);
      b += pow(rgb1[2] - rgb2[2], 2);
    }
  }

  double res_r, res_g, res_b;

  res_r = 10.0 * log10(pow(max_r, 2) * w * h / r);
  res_g = 10.0 * log10(pow(max_g, 2) * w * h / g);
  res_b = 10.0 * log10(pow(max_b, 2) * w * h / b);

  *result = (res_r + res_g + res_b) / 3.0;
}
