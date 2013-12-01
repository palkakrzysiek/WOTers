#ifndef __CLOSING_H__
#define __CLOSING_H__

#include "Operation.h"
#include "Erosion.h"
#include "Dilation.h"

class Closing : public Operation
{
public:
  void perform(Image &image);

};

#endif
