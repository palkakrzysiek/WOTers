#ifndef __RESIZE_H__
#define __RESIZE_H__

#include "Transformation.h"

class Resize : public Transformation
{
public:
  Resize(double scale);
  Resize(int w, int h, bool kr = true);
  
  void transform(Image &image);

private:
  double scale_x;
  double scale_y;
  int width;
  int height;
  bool keep_ratio;

};

#endif