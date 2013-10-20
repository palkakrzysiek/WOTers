#ifndef __RESIZE_H__
#define __RESIZE_H__

#include "Operation.h"

class Resize : public Operation
{
public:
  Resize(double scale);
  Resize(int w, int h, bool kr = true);
  
  void perform(Image &image);

private:
  double scale_x;
  double scale_y;
  int width;
  int height;
  bool keep_ratio;

};

#endif