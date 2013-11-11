#ifndef __PEAK_MEAN_SQUARE_ERROR_H__
#define __PEAK_MEAN_SQUARE_ERROR_H__

#include "Operation.h"

class PeakMeanSquareError : public Operation
{
public:
  PeakMeanSquareError(Image *f, double *r);

  void perform(Image &image);

private:
  Image *filtered;
  double *result;

};

#endif
