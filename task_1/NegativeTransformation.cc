#include "NegativeTransformation.h"
#include <omp.h>

void NegativeTransformation::transform(Image &image)
{
  int i, j;

# pragma omp parallel for private(j)
  for (i = 0; i < image.get_surface()->w; ++i)
  {
    for (j = 0; j < image.get_surface()->h; ++j)
    {
      image.set_pixel(i, j, ~(image.get_pixel(i, j)));
    }
  }
}
