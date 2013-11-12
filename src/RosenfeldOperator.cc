#include "RosenfeldOperator.h"

RosenfeldOperator::RosenfeldOperator(int p)
  : P(p)
{
}

void RosenfeldOperator::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  int bpp = image.get_surface()->format->BitsPerPixel;

  Image filtered(image);

  int i, j;

# pragma omp parallel for private(i)  
  for (j = 0; j < h; ++j)
  {
    for (i = P; i < w - P; ++i)
    {
      // uint8_t mask[3][9];

      // int o = 0;

      // // getting values of all the neighbors
      // for (int l = j - 1; l < j + 2; ++l)
      // {
      //   for (int k = i - 1; k < i + 2; k++)
      //   {
      //     SDL_GetRGB(image.get_pixel(k, l), image.get_surface()->format,
      //                &mask[0][o], &mask[1][o], &mask[2][o]);
      //     ++o;
      //   }
      // }

      double pixel_value[3] = {0.0};
      
      for (int m = -P; m < P; ++m)
      {
        // printf("\t%d\n", m);
        uint8_t r, g, b;
        SDL_GetRGB(image.get_pixel(i + m, j), image.get_surface()->format,
                   &r, &g, &b);

        pixel_value[0] += r;
        pixel_value[1] += g;
        pixel_value[2] += b;
      }

      for (int n = 0; n < 3; ++n)
      {
        pixel_value[n] /= (double) P;
      }

      filtered.set_pixel(i, j, SDL_MapRGB(filtered.get_surface()->format,
                         trunc(pixel_value[0]),
                         trunc(pixel_value[1]),
                         trunc(pixel_value[2])));
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
