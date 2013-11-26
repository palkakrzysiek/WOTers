#ifndef __HMT_H__
#define __HMT_H__

#include "Operation.h"

class HMT : public Operation
{
public:
  void perform(Image &image);

};

#endif