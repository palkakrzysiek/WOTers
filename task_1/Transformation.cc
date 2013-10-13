#include "Transformation.h"

uint8_t Transformation::trunc(int value)
{
  if (value > 0xff)
    return 0xff;

  if (value < 0)
    return 0;

  return value;
}
