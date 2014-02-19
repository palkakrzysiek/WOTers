#ifndef __RESIZE_H__
#define __RESIZE_H__

#include <tuple>
#include "Operation.h"

class Resize : public Operation
{
public:
  Resize(const std::tuple<double, int, int> &value);

  void perform(Image &image);

private:
  double scale_x;
  double scale_y;
  int width;
  int height;
  bool keep_ratio;

};

#endif