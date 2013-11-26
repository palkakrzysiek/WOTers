#ifndef __CONVERT_TO_GRAYSCALE_H__
#define __CONVERT_TO_GRAYSCALE_H__

#include "Operation.h"

class ConvertToGrayscale : public Operation
{
public:
  void perform(Image &image);

};

#endif