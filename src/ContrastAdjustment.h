#ifndef __CONTRAST_ADJUSTMENT_H__
#define __CONTRAST_ADJUSTMENT_H__

#include "Operation.h"

class ContrastAdjustment : public Operation
{
public:
  ContrastAdjustment(double by);

  void perform(Image &image);

private:
  double by_percent;

};

#endif