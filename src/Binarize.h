#ifndef __BINARIZE_H__
#define __BINARIZE_H__

#include "Operation.h"

class Binarize : public Operation
{
public:
  void perform(Image &image);

};

#endif