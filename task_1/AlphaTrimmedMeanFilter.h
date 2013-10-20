#ifndef __ALPHA_TRIMMED_MEAN_FILTER_H__
#define __ALPHA_TRIMMED_MEAN_FILTER_H__

#include "Operation.h"

class AlphaTrimmedMeanFilter : public Operation
{
public:
  AlphaTrimmedMeanFilter(uint8_t a);
  void perform(Image &image);

private:
  uint8_t alpha;

};

#endif
