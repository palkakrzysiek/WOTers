#ifndef __VERTICAL_FLIP_H__
#define __VERTICAL_FLIP_H__

#include "Transformation.h"

class VerticalFlip : public Transformation
{
public:
  void transform(Image &image);
};

#endif