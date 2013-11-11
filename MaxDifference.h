#ifndef _MAX_DIFFERENCE_H__
#define _MAX_DIFFERENCE_H__

#include "Operation.h"

class MaxDifference : public Operation
{
public:
  MaxDifference(Image *f, double *r);

  void perform(Image &image);

private:
  Image *filtered;
  double *result;

};

#endif