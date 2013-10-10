#include "ContrastTransformation.h"

ContrastTransformation::ContrastTransformation(double by)
  :
  by_percent(by)
{
}

void ContrastTransformation::transform(Image &image)
{
    // contrast change varies from -255 to 255
  // thus c must be in range [-1.0, 1.0]
  double c = by_percent * 255;

  // calculate contrast factor
  double f = ((259.0 * (c + 255.0)) / (255.0 * (259.0 - c)));

  uint8_t r, g, b;

  // change contrast of each individual pixel color
  // also check that color value is in range [0, 255]
  for (int i = 0; i < image.get_surface()->w; ++i)
  {
    for (int j = 0; j < image.get_surface()->h; ++j)
    {
      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format, &r, &g, &b);

      if (((r - 0x80) * f) + 0x80 > 0xff)
      {
        r = 0xff;
      }
      else if (((r - 0x80) * f) + 0x80 < 0)
      {
        r = 0;
      }
      else
      {
        r = ((r - 0x80) * f) + 0x80;
      }

      if (((g - 0x80) * f) + 0x80 > 0xff)
      {
        g = 0xff;
      }
      else if (((g - 0x80) * f) + 0x80 < 0)
      {
        g = 0;
      }
      else
      {
        g = ((g - 0x80) * f) + 0x80;
      }

      if (((b - 0x80) * f) + 0x80 > 0xff)
      {
        b = 0xff;
      }
      else if (((b - 0x80) * f) + 0x80 < 0)
      {
        b = 0;
      }
      else
      {
        b = ((b - 0x80) * f) + 0x80;
      }

      // setting new pixel value
      image.set_pixel(i, j, SDL_MapRGB(image.get_surface()->format, r, g, b));
    }
  }

}
