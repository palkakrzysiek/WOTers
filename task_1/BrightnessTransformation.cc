#include "BrightnessTransformation.h"

BrightnessTransformation::BrightnessTransformation(double by)
  :
  by_percent(by)
{
}

void BrightnessTransformation::transform(Image &image)
{
  // birghtness can be changed from -255 to 255
  int by = by_percent * 0xff;

  int i, j;

  // change value of each individual pixel color
  // also check that color value is in range [0, 255]
# pragma omp parallel for private(i)
  for (j = 0; j < image.get_surface()->h; ++j)
  {
    for (i = 0; i < image.get_surface()->w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format, &r, &g, &b, &a);

      r = trunc(r + by);
      g = trunc(g + by);
      b = trunc(b + by);
      a = trunc(a + by);

      // setting new pixel value
      image.set_pixel(i, j, SDL_MapRGBA(image.get_surface()->format, r, g, b, a));
    }
  }
}
