#ifndef __CONTRAMORPHIC_MEAN_FILTER_H__
#define __CONTRAMORPHIC_MEAN_FILTER_H__

#include "Transformation.h"

class ContramorphicMeanFilter : public Transformation
{
public:
  ContramorphicMeanFilter(double q);

  void transform(Image &image);

private:
  double order;

};

#endif