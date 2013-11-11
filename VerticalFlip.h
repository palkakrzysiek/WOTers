#ifndef __VERTICAL_FLIP_H__
#define __VERTICAL_FLIP_H__

#include "Operation.h"

class VerticalFlip : public Operation
{
public:
  void perform(Image &image);
};

#endif

