#ifndef __EROSION_H__
#define __EROSION_H__

#include "Operation.h"

class Erosion : public Operation
{
public:
  void perform(Image &image);

};

#endif
