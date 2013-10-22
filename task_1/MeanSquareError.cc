#include "MeanSquareError.h"
#include <cstdio> // fprintf
#include <cstdlib> // exit

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

  double r = 0.0, g = 0.0, b = 0.0, a = 0.0;

  int i, j;

# pragma omp parallel for private(i) default(shared) reduction(+:r,g,b,a)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t rgba1[4],
              rgba2[4];

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &rgba1[0], &rgba1[1], &rgba1[2], &rgba1[3]);
      SDL_GetRGBA(filtered->get_pixel(i, j), filtered->get_surface()->format,
                  &rgba2[0], &rgba2[1], &rgba2[2], &rgba2[3]);

      r += (rgba1[0] - rgba2[0]) * (rgba1[0] - rgba2[0]);
      g += (rgba1[1] - rgba2[1]) * (rgba1[1] - rgba2[1]);
      b += (rgba1[2] - rgba2[2]) * (rgba1[2] - rgba2[2]);
      a += (rgba1[3] - rgba2[3]) * (rgba1[3] - rgba2[3]);
    }
  }

  r /= w * h;
  g /= w * h;
  b /= w * h;
  a /= w * h;

  *result = (r + g + b + a) / bpp;
}
