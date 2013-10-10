#include "DiagonalFlip.h"

void DiagonalFlip::transform(Image &image)
{
  HorizontalFlip::transform(image);
  VerticalFlip::transform(image);
}
