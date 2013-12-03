#ifndef __PRUNING_H__
#define __PRUNING_H__

#include "Operation.h"
#include "HMT.h"
#include "Binarize.h"
#include "StructuralElements.h"
#include "Dilation.h"

class Pruning : public Operation {
  public:
    Pruning(int l);
    void perform(Image &image);
  private:
    int length;
};

#endif
