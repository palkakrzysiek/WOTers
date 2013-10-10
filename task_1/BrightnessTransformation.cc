#include "BrightnessTransformation.h"

BrightnessTransformation::BrightnessTransformation(double by)
  :
  by_percent(by)
{
}

void BrightnessTransformation::transform(Image *image)
{
  // birghtness can be changed from -255 to 255
  int by = by_percent * 0xff;

  uint8_t r, g, b;

  // change value of each individual pixel color
  // also check that color value is in range [0, 255]
  for (int i = 0; i < image->get_surface()->w; ++i)
  {
    for (int j = 0; j < image->get_surface()->h; ++j)
    {
      SDL_GetRGB(image->get_pixel(i, j), image->get_surface()->format, &r, &g, &b);

      if (r + by > 0xff)
      {
        r = 0xff;
      }
      else if (r + by < 0)
      {
        r = 0;
      }
      else
      {
        r += by;
      }

      if (g + by > 0xff)
      {
        g = 0xff;
      }
      else if (g + by < 0)
      {
        g = 0;
      }
      else
      {
        g += by;
      }

      if (b + by > 0xff)
      {
        b = 0xff;
      }
      else if (b + by < 0)
      {
        b = 0;
      }
      else
      {
        b += by;
      }

      // setting new pixel value
      image->set_pixel(i, j, SDL_MapRGB(image->get_surface()->format, r, g, b));
    }
  }
}
