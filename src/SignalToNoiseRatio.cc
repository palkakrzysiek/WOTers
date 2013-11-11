#include "SignalToNoiseRatio.h"
#include "MeanSquareError.h"
#include <cmath> // log10

SignalToNoiseRatio::SignalToNoiseRatio(Image *f, double *r)
  : filtered(f), result(r)
{
}

void SignalToNoiseRatio::perform(Image &image)
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

  double r1 = 0.0, g1 = 0.0, b1 = 0.0,
         r2 = 0.0, g2 = 0.0, b2 = 0.0;

# pragma omp parallel for private(i) default(shared) reduction(+:r1,g1,b1,r2,g2,b2)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgb1[3],
              rgb2[3];

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                  &rgb1[0], &rgb1[1], &rgb1[2]);
      SDL_GetRGB(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgb2[0], &rgb2[1], &rgb2[2]);

      r1 += rgb1[0] * rgb1[0];
      g1 += rgb1[1] * rgb1[1];
      b1 += rgb1[2] * rgb1[2];

      r2 += (rgb1[0] - rgb2[0]) * (rgb1[0] - rgb2[0]);
      g2 += (rgb1[1] - rgb2[1]) * (rgb1[1] - rgb2[1]);
      b2 += (rgb1[2] - rgb2[2]) * (rgb1[2] - rgb2[2]);
    }
  }

  r1 = 10 * log10(r1 / r2);
  g1 = 10 * log10(g1 / g2);
  b1 = 10 * log10(b1 / b2);

  *result = (r1 + g1 + b1) / 3.0;
}
