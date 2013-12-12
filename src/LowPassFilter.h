#ifndef __LOW_PASS_FILTER_H__
#define __LOW_PASS_FILTER_H__

#include "Operation.h"

class LowPassFilter : public Operation
{
public:
  virtual void perform(Image &image);

};

#endif
