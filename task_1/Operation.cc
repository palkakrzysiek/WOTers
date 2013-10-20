#include "Operation.h"

uint8_t Operation::trunc(int value)
{
  if (value > 0xff)
    return 0xff;

  if (value < 0)
    return 0;

  return value;
}
