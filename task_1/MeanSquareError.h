#ifndef __MEAN_SQUARE_ERROR_H__
#define __MEAN_SQUARE_ERROR_H__

#include "Operation.h"

class MeanSquareError : public Operation
{
public:
  MeanSquareError(Image *f, double *r);

  void perform(Image &image);

private:
  Image *filtered;
  double *result;

};

#endif
