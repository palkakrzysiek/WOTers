#ifndef __OPENING_H__
#define __OPENING_H__

#include "Operation.h"
#include "Erosion.h"
#include "Dilation.h"

class Opening : public Operation
{
public:
  Opening(int m);
  void perform(Image &image);
private:
  int mask;
};

#endif
