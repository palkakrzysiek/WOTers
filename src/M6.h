#ifndef SRC_M6_H_
#define SRC_M6_H_

#include "Operation.h"
#include "HMT.h"
#include "Binarize.h"
#include "StructuralElements.h"
#include "Negative.h"

class M6 : public Operation {
  public:
    void perform(Image &image);
};


#endif  // SRC_M6_H_
