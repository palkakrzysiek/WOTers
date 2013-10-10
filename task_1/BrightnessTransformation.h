#ifndef __BRIGHTNESS_TRANSFORMATION_H__
#define __BRIGHTNESS_TRANSFORMATION_H__

#include "Transformation.h"
#include "Image.h"

class BrightnessTransformation : public Transformation
{
public:
  BrightnessTransformation(double by);

  virtual void transform(Image *image);

private:
  double by_percent;

};

#endif
