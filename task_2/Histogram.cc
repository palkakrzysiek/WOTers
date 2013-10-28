#include "Histogram.h"
#include <cstring>
#include <cassert>

Histogram::Histogram(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &r, &g, &b, &a);

      ++pixels_r[r];
      ++pixels_g[g];
      ++pixels_b[b];
      ++pixels_a[a];
    }
  }
}
