#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "Image.h"

class Image;

class Operation
{
public:
  virtual void perform(Image &image) = 0;

  static uint8_t trunc(int value);

};

#endif
