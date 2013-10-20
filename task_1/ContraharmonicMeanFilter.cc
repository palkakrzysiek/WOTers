#include "ContraharmonicMeanFilter.h"
#include <algorithm> // std::sort
#include <cmath> // std::pow

ContraharmonicMeanFilter::ContraharmonicMeanFilter(double q)
  : order(q)
{
}

void ContraharmonicMeanFilter::perform(Image &image)
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
      uint8_t mask[4][9];
      double sum1[4];
      double sum2[4];
      memset(sum1, 0.0, 4 * sizeof(uint32_t));
      memset(sum2, 0.0, 4 * sizeof(uint32_t));
      uint32_t mean[4];
      int o = 0;

      // getting values of all the neighbors
      for (int l = j - 1; l < j + 2; ++l)
      {
        for (int k = i - 1; k < i + 2; k++)
        {
          SDL_GetRGBA(image.get_pixel(k, l), image.get_surface()->format,
                     &mask[0][o], &mask[1][o], &mask[2][o], &mask[3][o]);
          ++o;
        }
      }

      // summing color values
      for (int k = 0; k < 4; ++k)
        for (int l = 0; l < 9 ; ++l)
        {
          sum1[k] += std::pow(mask[k][l], order + 1.0);
          sum2[k] += std::pow(mask[k][l], order);
        }


      for (int k = 0; k < 4; ++k)
      {
        sum1[k] /= 9.0;
        sum2[k] /= 9.0;
      }

      // calculating average color values
      for (int k = 0; k < 4; ++k)
      {
        mean[k] = sum1[k] / sum2[k];
        // printf("%u\n", mean[k]);
      }

      // putting the new pixel value to the image
      filtered.set_pixel(i, j, SDL_MapRGBA(filtered.get_surface()->format,
                         mean[0], mean[1], mean[2], mean[3]));
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
