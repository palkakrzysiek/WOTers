#include "NegativeTransformation.h"

void NegativeTransformation::transform(Image &image)
{
  for (int i = 0; i < image.get_surface()->w; ++i)
  {
    for (int j = 0; j < image.get_surface()->h; ++j)
    {
      image.set_pixel(i, j, ~image.get_pixel(i, j));
    }
  }
}
