#ifndef __EROSION_H__
#define __EROSION_H__

#include "Operation.h"

class Erosion : public Operation
{
public:
  Erosion(int m);
  void perform(Image &image);
private:
  int mask;
};

#endif
