#ifndef __NEGATIVE_H__
#define __NEGATIVE_H__

#include "Operation.h"

class Negative : public Operation
{
public:
  void perform(Image &image);
};

#endif