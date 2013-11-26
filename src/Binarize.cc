#include "Binarize.h"
#include <cmath>
#include <algorithm>

void Binarize::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image bin(image);

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b;

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &r, &g, &b);

      double rd = r, gd = g, bd = b;

      double dfw = sqrt(pow(rd - 0xff, 2) + pow(gd - 0xff, 2) + pow(bd - 0xff, 2));
      double dfb = sqrt(pow(rd, 2) + pow(gd, 2) + pow(bd, 2));

      uint8_t value = 0.0;

      if ((dfb - dfw) > 12.0)
        value = 0xff;

      bin.set_pixel(i, j, SDL_MapRGB(bin.get_surface()->format,
                     value, value, value));
    }
  }

  image = std::move(bin);
}
