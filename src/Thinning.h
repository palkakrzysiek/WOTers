#ifndef __THINNING_H__
#define __THINNING_H__

#include "Operation.h"
#include "HMT.h"
#include "Binarize.h"

class Thinning : public Operation {
  public:
    void perform(Image &image);
};

#endif
