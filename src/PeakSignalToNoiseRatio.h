#ifndef __PEAK_SIGNAL_TO_NOISE_RATIO_H__
#define __PEAK_SIGNAL_TO_NOISE_RATIO_H__

#include "Operation.h"

class PeakSignalToNoiseRatio : public Operation
{
public:
  PeakSignalToNoiseRatio(Image *f, double *r);
  
  void perform(Image &image);

private:
  Image *filtered;
  double *result;

};

#endif
