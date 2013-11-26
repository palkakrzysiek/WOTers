#include "ConvertToGrayscale.h"
#include <algorithm>

void ConvertToGrayscale::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image gray(image);

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b;

      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                 &r, &g, &b);

      uint16_t n = (r + g + b) / 3;

      gray.set_pixel(i, j, SDL_MapRGB(gray.get_surface()->format,
                     n, n, n));
    }
  }

  image = std::move(gray);
}
