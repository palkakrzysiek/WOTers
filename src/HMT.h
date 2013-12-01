#ifndef __HMT_H__
#define __HMT_H__

#include "Operation.h"

class HMT : public Operation
{
public:
  HMT(int mask);

  void perform(Image &image);

private:
  int mask;

};

#endif
