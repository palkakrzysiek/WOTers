#include "VerticalFlip.h"

void VerticalFlip::perform(Image &image)
{
  int i, j;

  // iterate through the columns of image
# pragma omp parallel for private(j)
  for (i = 0; i < image.get_surface()->w; ++i)
  {
    for (j = 0; j < image.get_surface()->h/2; ++j)
    {
      // assign the values of last pixels in the line of image
      // to the first pixel values of temp
      uint32_t temp = image.get_pixel(i, j);
      image.set_pixel(i, j, image.get_pixel(i, image.get_surface()->h - 1 - j));
      image.set_pixel(i, image.get_surface()->h - 1 - j, temp);
    }
  }
}
