#include "AlphaTrimmedMeanFilter.h"

AlphaTrimmedMeanFilter::AlphaTrimmedMeanFilter(uint8_t a)
  : alpha(a)
{
}

// TODO
// deal with the borders
void AlphaTrimmedMeanFilter::transform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  // calculate the indexes of considered neighbors
  int begin = alpha / 2;
  int end = 9 - (alpha / 2);

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
      memset(sum, 0, 4 * sizeof(uint32_t));

      uint32_t avg[4];
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

      // sorting color values
      std::sort(mask[0], mask[0] + 9);
      std::sort(mask[1], mask[1] + 9);
      std::sort(mask[2], mask[2] + 9);
      std::sort(mask[3], mask[3] + 9);

      // summing color values
      for (int k = 0; k < 4; ++k)
        for (int l = begin; l < end; ++l)
          avg[k] += mask[k][l];

      // calculating average color values
      for (int k = 0; k < 4; ++k)
        avg[k] /= (9 - alpha);

      // putting the new pixel value to the image
      filtered.set_pixel(i, j, SDL_MapRGBA(filtered.get_surface()->format,
                         avg[0], avg[1], avg[2], avg[3]));
    }
  }

  // replacing previous image with the filtered one
  image = std::move(filtered);
}

