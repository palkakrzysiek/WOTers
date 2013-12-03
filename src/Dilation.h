#ifndef __DILATION_H__
#define __DILATION_H__

#include "Operation.h"

class Dilation : public Operation
{
public:
  Dilation(int m);
  void perform(Image &image);
private:
  int mask;
};

#endif
