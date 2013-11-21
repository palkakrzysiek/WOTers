#ifndef __DILATION_H__
#define __DILATION_H__

#include "Operation.h"

class Dilation : public Operation
{
public:
  void perform(Image &image);
  
};

#endif