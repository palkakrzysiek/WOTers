#ifndef __DFT_H__
#define __DFT_H__

#include "Operation.h"

class DFT : public Operation
{
public:
  void perform(Image &image);
};

#endif