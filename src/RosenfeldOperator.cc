#include "RosenfeldOperator.h"

RosenfeldOperator::RosenfeldOperator(int p)
  : P(p)
{
}

void RosenfeldOperator::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image filtered(image);

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
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

      int P2 = P;

      for (int m = -P; m < P; ++m)
      {
        if (i + m < 0 || i + m > w)
        {
          continue;
          --P2;
        }

        uint8_t r, g, b;
        SDL_GetRGB(image.get_pixel(i + m, j), image.get_surface()->format,
                   &r, &g, &b);

        if (m >= 0)
        {
          pixel_value[0] += r;
          pixel_value[1] += g;
          pixel_value[2] += b;
        }
        else
        {
          pixel_value[0] -= r;
          pixel_value[1] -= g;
          pixel_value[2] -= b;
        }
      }

      pixel_value[0] /= P2;
      pixel_value[1] /= P2;
      pixel_value[2] /= P2;


      filtered.set_pixel(i, j, SDL_MapRGB(filtered.get_surface()->format,
                         trunc(pixel_value[0]),
                         trunc(pixel_value[1]),
                         trunc(pixel_value[2])));
    }
  }

// # pragma omp parallel for
//   for (i = 0; i < w; ++i)
//   {
//     filtered.set_pixel(i, 0, filtered.get_pixel(i, 1));
//     filtered.set_pixel(i, h - 1, filtered.get_pixel(i, h - 2));
//   }

// # pragma omp parallel for
//   for (j = 0; j < h; ++j)
//   {
//     filtered.set_pixel(0, j, filtered.get_pixel(1, j));
//     filtered.set_pixel(w - 1, j, filtered.get_pixel(w - 2, j));
//   }

  // replacing previous image with the filtered one
  image = std::move(filtered);
}
