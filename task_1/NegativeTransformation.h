#ifndef __NEGATIVE_TRANSFORMATION_H__
#define __NEGATIVE_TRANSFORMATION_H__

#include "Transformation.h"

class NegativeTransformation : public Transformation
{
public:
  void transform(Image &image);
};

#endif