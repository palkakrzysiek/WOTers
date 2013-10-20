#ifndef __HORIZONTAL_FLIP_H__
#define __HORIZONTAL_FLIP_H__

#include "Operation.h"

class HorizontalFlip : public Operation
{
public:
  void perform(Image &image);
};

#endif