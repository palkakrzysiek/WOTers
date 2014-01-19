#ifndef __DFT_H__
#define __DFT_H__

#include "Operation.h"
#include "ComplexImage.h"

class DFT {
public:
  ComplexImage DFT(Image &image, bool inverse = false);
};

#endif
