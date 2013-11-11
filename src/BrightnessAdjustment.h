#ifndef __BRIGHTNESS_ADJUSTMENT_H__
#define __BRIGHTNESS_ADJUSTMENT_H__

#include "Operation.h"
#include "Image.h"

class BrightnessAdjustment : public Operation
{
public:
  BrightnessAdjustment(double by);

  void perform(Image &image);

private:
  double by_percent;

};

#endif
