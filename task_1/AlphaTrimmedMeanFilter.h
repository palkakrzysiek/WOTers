#ifndef __ALPHA_TRIMMED_MEAN_FILTER_H__
#define __ALPHA_TRIMMED_MEAN_FILTER_H__

#include "Transformation.h"

class AlphaTrimmedMeanFilter : public Transformation
{
public:
  AlphaTrimmedMeanFilter(uint8_t alpha);
  void transform(Image &image);

private:
  uint8_t alpha;

};

#endif
