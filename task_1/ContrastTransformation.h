#ifndef __CONTRAST_TRANSFORMATION_H__
#define __CONTRAST_TRANSFORMATION_H__

#include "Transformation.h"

class ContrastTransformation : public Transformation
{
public:
  ContrastTransformation(double by);

  void transform(Image &image);

private:
  double by_percent;

};

#endif