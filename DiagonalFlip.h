#ifndef __DIAGONAL_FLIP_H__
#define __DIAGONAL_FLIP_H__

#include "HorizontalFlip.h"
#include "VerticalFlip.h"

class DiagonalFlip : public Operation
{
public:
  void perform(Image &image);
    
};

#endif