#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "Image.h"

class Image;

class Transformation
{
public:
  virtual void transform(Image &image) = 0;

};

#endif
