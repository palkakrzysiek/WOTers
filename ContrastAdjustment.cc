#include "ContrastAdjustment.h"

ContrastAdjustment::ContrastAdjustment(double by)
  :
  by_percent(by)
{
}

void ContrastAdjustment::perform(Image &image)
{
  // contrast change varies from -255 to 255
  // thus c must be in range [-1.0, 1.0]
  double c = by_percent * 255;

  // calculate contrast factor
  double f = ((259.0 * (c + 255.0)) / (255.0 * (259.0 - c)));

  int i, j;

  // change contrast of each individual pixel color
  // also check that color value is in range [0, 255]
# pragma omp parallel for private(i)
  for (j = 0; j < image.get_surface()->h; ++j)
  {
    for (i = 0; i < image.get_surface()->w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format, &r, &g, &b, &a);

      r = trunc(((r - 0x80) * f) + 0x80);
      g = trunc(((g - 0x80) * f) + 0x80);
      b = trunc(((b - 0x80) * f) + 0x80);
      a = trunc(((a - 0x80) * f) + 0x80);

      // setting new pixel value
      image.set_pixel(i, j, SDL_MapRGBA(image.get_surface()->format, r, g, b, a));
    }
  }

}
