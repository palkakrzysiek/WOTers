#ifndef __OPENING_H__
#define __OPENING_H__

#include "Operation.h"

class Opening : public Operation
{
public:
  void perform(Image &image);
  
};

#endif