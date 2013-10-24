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

  if (filtered->get_surface()->w != w && filtered->get_surface()->h != h 
      && filtered->get_surface()->format->BytesPerPixel != bpp)
  {
    fprintf(stderr, "Images are not of the same size\n");
    exit(1);
  }

  int i, j;

  double r1 = 0.0, g1 = 0.0, b1 = 0.0, a1 = 0.0,
         r2 = 0.0, g2 = 0.0, b2 = 0.0, a2 = 0.0;

# pragma omp parallel for private(i) default(shared) reduction(+:r1,g1,b1,a1,r2,g2,b2,a2)
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

      r1 += rgba1[0] * rgba1[0];
      g1 += rgba1[1] * rgba1[1];
      b1 += rgba1[2] * rgba1[2];
      // a1 += rgba1[3] * rgba1[3];

      r2 += (rgba1[0] - rgba2[0]) * (rgba1[0] - rgba2[0]);
      g2 += (rgba1[1] - rgba2[1]) * (rgba1[1] - rgba2[1]);
      b2 += (rgba1[2] - rgba2[2]) * (rgba1[2] - rgba2[2]);
      // a2 += (rgba1[3] - rgba2[3]) * (rgba1[3] - rgba2[3]);
    }
  }

  r1 = 10 * log10(r1 / r2);
  g1 = 10 * log10(g1 / g2);
  b1 = 10 * log10(b1 / b2);
  // a1 = 10 * log10(a1 / a2);

  *result = (r1 + g1 + b1) / 3.0;
}
