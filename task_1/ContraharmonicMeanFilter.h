#ifndef __CONTRAHARMONIC_MEAN_FILTER_H__
#define __CONTRAHARMONIC_MEAN_FILTER_H__

#include "Transformation.h"

class ContraharmonicMeanFilter : public Transformation
{
public:
  ContraharmonicMeanFilter(double q);

  void transform(Image &image);

private:
  double order;

};

#endif