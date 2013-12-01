#ifndef __M5__
#define __M5__

#include "Operation.h"
#include "HMT.h"

class M5 : public Operation {
  public:
    void perform(Image &image);
};

#endif
