#ifndef __HORIZONTAL_FLIP_H__
#define __HORIZONTAL_FLIP_H__

#include "Transformation.h"

class HorizontalFlip : public Transformation
{
public:
  void transform(Image &image);
};

#endif