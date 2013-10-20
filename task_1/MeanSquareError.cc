#include "MeanSquareError.h"
#include <cstdio> // fprintf
#include <cstdlib> // exit
#include <cmath> // std::pow
#include <cstring> // memset

MeanSquareError::MeanSquareError(Image *f, double *r)
  : filtered(f), result(r)
{
}

void MeanSquareError::perform(Image &image)
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

  double rgba[4];
  memset(rgba, 0.0, 4 * sizeof(double));

  for (int j = 0; j < h; ++j)
  {
    for (int i = 0; i < w; ++i)
    {
      uint8_t rgba1[4],
              rgba2[4];

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &rgba1[0], &rgba1[1], &rgba1[2], &rgba1[3]);
      SDL_GetRGBA(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgba2[0], &rgba2[1], &rgba2[2], &rgba2[3]);

      for (int k = 0; k < 4; ++k)
      {
        rgba[k] += std::pow(rgba1[k] - rgba2[k], 2);
      }
    }
  }

  for (int i = 0; i < 4; ++i)
  {
    rgba[i] /= w * h;
  }

  *result = (rgba[0] + rgba[1] + rgba[2] + rgba[3]) / bpp;
}
