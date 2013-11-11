#ifndef __CONTRAHARMONIC_MEAN_FILTER_H__
#define __CONTRAHARMONIC_MEAN_FILTER_H__

#include "Operation.h"

class ContraharmonicMeanFilter : public Operation
{
public:
  ContraharmonicMeanFilter(double q);

  void perform(Image &image);

private:
  double order;

};

#endif
