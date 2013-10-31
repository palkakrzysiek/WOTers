#include "MaxDifference.h"
#include <cmath>

MaxDifference::MaxDifference(Image *f, double *r)
  : filtered(f), result(r)
{
}

void MaxDifference::perform(Image &image)
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

  double max_r = 0.0, max_g = 0.0, max_b = 0.0;

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r1, g1, b1, a1,
              r2, g2, b2, a2;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &r1, &g1, &b1, &a1);
      SDL_GetRGBA(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &r2, &g2, &b2, &a2);

      if (fabs(r1 - r2) > max_r)
        max_r = fabs(r1 - r2);

      if (fabs(g1 - g2) > max_g)
        max_g = fabs(g1 - g2);

      if (fabs(b1 - b2) > max_b)
        max_b = fabs(b1 - b2);

      // if (a > max_a)
      //   max_a = a;
    }
  }

  *result = (double) (max_r + max_b + max_g) / 3.0;
}
