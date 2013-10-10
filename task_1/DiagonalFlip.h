#ifndef __DIAGONAL_FLIP_H__
#define __DIAGONAL_FLIP_H__

#include "HorizontalFlip.h"
#include "VerticalFlip.h"

class DiagonalFlip : public HorizontalFlip, public VerticalFlip
{
public:
  void transform(Image &image);
    
};

#endif