#include "LowPassFilter.h"
#include <algorithm>

void LowPassFilter::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  // create a copy of the image
  Image filtered(image);

  int i, j;

# pragma omp parallel for private(i)  
  for (j = 1; j < h - 1; ++j)
  {
    for (i = 1; i < w - 1; ++i)
    {
      // 3x3 mask containing 4 color values
      uint8_t mask[3][9];
      int r = 0, g = 0, b = 0;
    
      int o = 0;

      // getting values of all the neighbors
      for (int l = j - 1; l < j + 2; ++l)
      {
        for (int k = i - 1; k < i + 2; k++)
        {
          SDL_GetRGB(image.get_pixel(k, l), image.get_surface()->format,
                     &mask[0][o], &mask[1][o], &mask[2][o]);

          // 1
          // r += mask[0][o] / 9;
          // g += mask[1][o] / 9;
          // b += mask[2][o] / 9;

          // 2
          // if (k == i && l == j)
          // {
          //   r += mask[0][o] / 5;
          //   g += mask[1][o] / 5;
          //   b += mask[2][o] / 5;
          // }
          // else
          // {
          //   r += mask[0][o] / 10;
          //   g += mask[1][o] / 10;
          //   b += mask[2][o] / 10;
          // }

          // 3
          if (k == i && l == j)
          {
            r += mask[0][o] / 4;
            g += mask[1][o] / 4;
            b += mask[2][o] / 4;
          }
          else if (k == i || l == j)
          {
            r += mask[0][o] / 8;
            g += mask[1][o] / 8;
            b += mask[2][o] / 8;
          }
          else
          {
            r += mask[0][o] / 16;
            g += mask[1][o] / 16;
            b += mask[2][o] / 16;
          }

          ++o;
        }
      }

      // putting the new pixel value to the image
      filtered.set_pixel(i, j, SDL_MapRGB(filtered.get_surface()->format,
                         trunc(r), trunc(g), trunc(b)));
    }
  }

# pragma omp parallel for
  for (i = 0; i < w; ++i)
  {
    filtered.set_pixel(i, 0, filtered.get_pixel(i, 1));
    filtered.set_pixel(i, h - 1, filtered.get_pixel(i, h - 2));
  }

# pragma omp parallel for
  for (j = 0; j < h; ++j)
  {
    filtered.set_pixel(0, j, filtered.get_pixel(1, j));
    filtered.set_pixel(w - 1, j, filtered.get_pixel(w - 2, j));
  }

  // replacing previous image with the filtered one
  image = std::move(filtered);
}

