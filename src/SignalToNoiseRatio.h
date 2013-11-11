#ifndef __SIGNAL_TO_NOISE_RATIO_H__
#define __SIGNAL_TO_NOISE_RATIO_H__

#include "Operation.h"

class SignalToNoiseRatio : public Operation
{
public:
  SignalToNoiseRatio(Image *f, double *r);
  
  void perform(Image &image);

private:
  Image *filtered;
  double *result;

};

#endif
